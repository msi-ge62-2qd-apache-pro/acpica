/******************************************************************************
 *
 * Module Name: osmacosxtbl - Mac OS X OSL for obtaining ACPI tables
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2013, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights. You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code. No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision. In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change. Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee. Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution. In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
 * Intel shall be used in advertising or otherwise to promote the sale, use or
 * other dealings in products derived from or relating to the Covered Code
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED
 * HERE. ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES. INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS. INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government. In the
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/

#include "acpi.h"

#include <stdio.h>
#include <stdlib.h>

#define _COMPONENT          ACPI_OS_SERVICES
        ACPI_MODULE_NAME    ("osmacosxtbl")

#include <IOKit/IOKitLib.h>                           // (IOMasterPort, ...)

static Boolean scan(char *Signature, io_registry_entry_t service);
static int find(char *Signature, io_registry_entry_t service);
static int KeyCompare(const void *left, const void *right);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define assertion(e, message) ((void) (__builtin_expect(!(e), 0) ? fprintf(stderr, "acpidump: error: %s.\n", message), exit(1) : 0))

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetTableByAddress
 *
 * PARAMETERS:  Address         - Physical address of the ACPI table
 *              Table           - Where a pointer to the table is returned
 *
 * RETURN:      Status; Table buffer is returned if AE_OK.
 *              AE_NOT_FOUND: A valid table was not found at the address
 *
 * DESCRIPTION: Get an ACPI table via a physical memory address.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsGetTableByAddress (
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_TABLE_HEADER       **Table)
{

    fprintf (stderr, "Get table by address is not supported on Mac OS X\n");
    return (AE_SUPPORT);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetTableByIndex
 *
 * PARAMETERS:  Index           - Which table to get
 *              Table           - Where a pointer to the table is returned
 *              Address         - Where the table physical address is returned
 *
 * RETURN:      Status; Table buffer and physical address returned if AE_OK.
 *              AE_LIMIT: Index is beyond valid limit
 *
 * DESCRIPTION: Get an ACPI table via an index value (0 through n). Returns
 *              AE_LIMIT when an invalid index is reached. Index is not
 *              necessarily an index into the RSDT/XSDT.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsGetTableByIndex (
    UINT32                  Index,
    ACPI_TABLE_HEADER       **Table,
    ACPI_PHYSICAL_ADDRESS   *Address)
{

    fprintf (stderr, "Get table by address is not supported on Mac OS X\n");
    return (AE_SUPPORT);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsMapMemory
 *
 * PARAMETERS:  Where               - Physical address of memory to be mapped
 *              Length              - How much memory to map
 *
 * RETURN:      Pointer to mapped memory. Null on error.
 *
 * DESCRIPTION: Map physical memory into local address space.
 *
 *****************************************************************************/

void *
AcpiOsMapMemory (
    ACPI_PHYSICAL_ADDRESS   Where,
    ACPI_SIZE               Length)
{

    fprintf (stderr, "AcpiOsMapMemory is not supported on Mac OS X\n");
    return 0;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsUnmapMemory
 *
 * PARAMETERS:  Where               - Logical address of memory to be unmapped
 *              Length              - How much memory to unmap
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a previously created mapping. Where and Length must
 *              correspond to a previous mapping exactly.
 *
 *****************************************************************************/

void
AcpiOsUnmapMemory (
    void                    *Where,
    ACPI_SIZE               Length)
{

    fprintf (stderr, "AcpiOsUnmapMemory is not supported on Mac OS X\n");
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetTableByName
 *
 * PARAMETERS:  Signature       - ACPI Signature for desired table. Must be
 *                                a null terminated 4-character string.
 *              Instance        - For SSDTs (0...n)
 *              Table           - Where a pointer to the table is returned
 *              Address         - Where the table physical address is returned
 *
 * RETURN:      Status; Table buffer and physical address returned if AE_OK.
 *
 * RETURN:      Status; Table buffer and physical address returned if AE_OK.
 *              AE_LIMIT: Instance is beyond valid limit
 *              AE_NOT_FOUND: A table with the signature was not found
 *
 * NOTE:        Assumes the input signature is uppercase.
 *
 *****************************************************************************/

int KeyCompare(const void *left, const void *right)
    // Comparison callback for sorting an array of CFDictionary keys.
{
    CFStringRef     leftString;
    CFStringRef     rightString;

    assertion(left != NULL, "");
    assertion(right != NULL, "");

    leftString  = *(CFStringRef *) left;
    rightString = *(CFStringRef *) right;

    assertion(leftString != NULL, "");
    assertion(rightString != NULL, "");

    return (int) CFStringCompare(leftString, rightString, 0);
}

Boolean scan(char *Signature, io_registry_entry_t service)
{
    CFMutableDictionaryRef properties = 0; // (needs release)
    kern_return_t          status     = KERN_SUCCESS;
    Boolean                result     = FALSE;
    CFDictionaryRef        dict = NULL; // (needs release)
    CFIndex                 dictCount;
    CFIndex                 dictIndex;
    CFStringRef *         keys;
    CFDataRef *           values;
    const UInt8 * bytes;
    CFIndex       index;
    CFIndex       length;
    CFStringRef   signature;
    CFComparisonResult check;

    signature = CFStringCreateWithCString(kCFAllocatorDefault,
                                          Signature,
                                          kCFStringEncodingMacRoman);

    // Obtain the service's properties.

    status = IORegistryEntryCreateCFProperties( service,
                                                &properties,
                                                kCFAllocatorDefault,
                                                kNilOptions );
    if (status != KERN_SUCCESS) {
        fprintf (stderr, "scan: IORegistryEntryCreateCFProperties fail!\n");
    } else {
        if (CFDictionaryContainsKey(properties, CFSTR("ACPI Tables")) == TRUE) {
            result = TRUE;

            if (CFDictionaryGetValueIfPresent(properties, CFSTR("ACPI Tables"), (const void **)&dict) == TRUE) {
                dictCount = CFDictionaryGetCount(dict);

                keys = malloc(dictCount * sizeof(CFStringRef));
                assertion(keys != NULL, "");
                values = malloc(dictCount * sizeof(CFDataRef));
                assertion(values != NULL, "");

                CFDictionaryGetKeysAndValues(dict, (const void **) keys, (const void **) values);

                // Sort the keys so that we get consistent results for the benefit of the
                // test script.

                qsort(keys, dictCount, sizeof(*keys), KeyCompare);

                fprintf (stdout, "what we want is: %s\n", Signature);
                for (dictIndex = 0; dictIndex < dictCount; dictIndex++) {
                    const char * c = CFStringGetCStringPtr(keys[dictIndex], kCFStringEncodingMacRoman);
                    length = CFDataGetLength(values[dictIndex]);
                    bytes  = CFDataGetBytePtr(values[dictIndex]);

                    check = CFStringCompareWithOptions(keys[dictIndex], signature, CFRangeMake(0,CFStringGetLength(keys[dictIndex])), kCFCompareCaseInsensitive);
                    if (check == kCFCompareEqualTo) {
                        fprintf (stdout, "found it! please save it\n");

                        //dummy code...
                        index = 0;
                        if (bytes[index] == 0) {
                            //save bytes somewhere
                        }

                        break;
                    }
                    fprintf (stdout, "key=: %s, data length=%ld\n", c, length);
                }
                if (check != kCFCompareEqualTo)
                    fprintf (stdout, "not found it!\n");

                free(keys);
                free(values);
            }

            CFRelease(dict);
        }
    }

    // Release resources.

    CFRelease(properties);
    CFRelease(signature);

    return result;
}

int find(char *Signature, io_registry_entry_t service)
{
    int result = -1;
    int tmp;

    io_registry_entry_t child       = 0; // (needs release)
    io_registry_entry_t childUpNext = 0; // (don't release)
    io_iterator_t       children    = 0; // (needs release)
    kern_return_t       status      = KERN_SUCCESS;

    if (scan(Signature, service) == TRUE) {
        return (int)service;
    }

    // Obtain the service's children.

    status = IORegistryEntryGetChildIterator(service, kIOServicePlane, &children);
    if (status != KERN_SUCCESS) {
        fprintf (stderr, "find: IORegistryEntryGetChildIterator fail!\n");
    } else {
        childUpNext = IOIteratorNext(children);

        while (childUpNext)
        {
            child       = childUpNext;
            childUpNext = IOIteratorNext(children);

            tmp = (int)find(Signature, child);
            if (tmp != -1) {
                result = tmp;
                break;
            }

            IOObjectRelease(child);
        }

        IOObjectRelease(children);
    }

    return result;
}

ACPI_STATUS
AcpiOsGetTableByName (
    char                    *Signature,
    UINT32                  Instance,
    ACPI_TABLE_HEADER       **Table,
    ACPI_PHYSICAL_ADDRESS   *Address)
{
    io_registry_entry_t service  = 0; // (needs release)
    kern_return_t          status     = KERN_SUCCESS;
    int result = -1;
    CFStringRef str;

    str = CFStringCreateWithCString(NULL, Signature, kCFStringEncodingMacRoman);

    // Obtain the I/O Kit root service.
    
    service = IORegistryGetRootEntry(kIOMasterPortDefault);
    if (status != KERN_SUCCESS) {
        fprintf (stderr, "find: IORegistryGetRootEntry fail!\n");
    } else {
        result = find(Signature, service);
        if (result != -1) {
            fprintf (stdout, "%d, got it!\n", result);

        }

        // Release resources.

        IOObjectRelease(service);
    }

    CFRelease(str);

    return (AE_SUPPORT);
}
