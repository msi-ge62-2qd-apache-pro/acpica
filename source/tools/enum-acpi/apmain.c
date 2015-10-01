/******************************************************************************
 *
 * Module Name: apmain - Main module for the enum-acpi utility
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2015, Intel Corp.
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

#define _DECLARE_GLOBALS
#include "enum-acpi.h"
#include "acapps.h"


/*
 * enum-acpi -- a QNX enum-devices enumerator for ACPI device dables
 */


/* Local prototypes */

#define AP_UTILITY_NAME             "ACPI QNX Device Enumerator"



/* Local utility functions */

/* Print a prefix with a counter suffix for second and subsequent calls */
static void fprint_counted_id(const char* prefix, int* counter) {
    if (*counter > 0) {
        fprintf(stdout, " %s%d=",prefix,*counter);
    } else {
        fprintf(stdout, " %s=",prefix);
    };
    ++*counter;
};

/* Print a pascal-style string */
static void PrintFixedString(UINT32 Length, char* String) {
    for ( ; (Length != 0) && (*String != 0); --Length, ++String ) {
        fputc(*String,stdout);
    };
};

/* Return true if the string is a bus-class PNP ID */
static int IsBus(char* String) {
    return strncmp(String,"PNP0A",5) == 0;
};



/* Print a tag for the specified resource */

static ACPI_STATUS
PrintResourceInfo (
    ACPI_RESOURCE*  Resource,
    void*           Context)
{
    int* counter_array = (int*) Context;

    switch (Resource->Type) {
        case ACPI_RESOURCE_TYPE_IRQ:
/*
            fprintf(stdout,"IRQ - Triggering: %d  Polarity: %d  Sharable: %d   WakeCapable: %d   Count: %d   Value: %d\n",
                Resource->Data.Irq.Triggering,
                Resource->Data.Irq.Polarity,
                Resource->Data.Irq.Sharable,
                Resource->Data.Irq.WakeCapable,
                Resource->Data.Irq.InterruptCount,
                Resource->Data.Irq.Interrupts[0]
            );
*/
            {
                int i;
                for(i = 0; i < Resource->Data.Irq.InterruptCount; ++i) {
                    fprint_counted_id("irq",&counter_array[Resource->Type]);
                    fprintf(stdout,"%d",Resource->Data.Irq.Interrupts[i]);
                };
            };
            break;

        case ACPI_RESOURCE_TYPE_DMA:
            {
                int i;
                for(i = 0; i < Resource->Data.Dma.ChannelCount; ++i) {
                    fprint_counted_id("dma",&counter_array[Resource->Type]);
                    fprintf(stdout,"%d",Resource->Data.Dma.Channels[i]);
                };
            };
/*
            fprintf(stdout,"DMA - Type: %d   BusMaster: %d    Transfer: %d    ChannelCount: %d\n",
                Resource->Data.Dma.Type,
                Resource->Data.Dma.BusMaster,
                Resource->Data.Dma.Transfer,
                Resource->Data.Dma.ChannelCount
            );
*/
            break;

        case ACPI_RESOURCE_TYPE_START_DEPENDENT:
        case ACPI_RESOURCE_TYPE_END_DEPENDENT:
            //fprintf(stdout,"Dependent - type %d\n",Resource->Type);
            break;

        case ACPI_RESOURCE_TYPE_IO:
/*
            fprintf(stdout,"IO - IODecode: %d   Alignment: %d    AddressLength: %d    Minimum: %04X   Maximum: %04X\n",
                Resource->Data.Io.IoDecode,
                Resource->Data.Io.Alignment,
                Resource->Data.Io.AddressLength,
                Resource->Data.Io.Minimum,
                Resource->Data.Io.Maximum
            );
*/
            fprint_counted_id("ioport",&counter_array[Resource->Type]);
            fprintf(stdout,"%x",Resource->Data.Io.Minimum);

            break;

        case ACPI_RESOURCE_TYPE_FIXED_IO:
/*
            fprintf(stdout,"Fixed IO - Address: %04X   Length: %d\n",
                Resource->Data.FixedIo.Address,
                Resource->Data.FixedIo.AddressLength
            );
*/
            fprint_counted_id("ioport",&counter_array[ACPI_RESOURCE_TYPE_IO]);
            fprintf(stdout,"%x",Resource->Data.FixedIo.Address);
            break;

        case ACPI_RESOURCE_TYPE_MEMORY24:
/*
            fprintf(stdout,"Memory24 - WriteProtect: %d   Alignment: %d    AddressLength: %d    Minimum: %08X   Maximum: %08X\n",
                Resource->Data.Memory24.WriteProtect,
                Resource->Data.Memory24.Alignment,
                Resource->Data.Memory24.AddressLength,
                Resource->Data.Memory24.Minimum,
                Resource->Data.Memory24.Maximum
            );
*/
            fprint_counted_id("mem",&counter_array[ACPI_RESOURCE_TYPE_MEMORY32]);
            fprintf(stdout,"%x",Resource->Data.Memory24.Minimum);

            break;

        case ACPI_RESOURCE_TYPE_MEMORY32:
/*
            fprintf(stdout,"Memory32 - WriteProtect: %d   Alignment: %d    AddressLength: %d    Minimum: %08X   Maximum: %08X\n",
                Resource->Data.Memory32.WriteProtect,
                Resource->Data.Memory32.Alignment,
                Resource->Data.Memory32.AddressLength,
                Resource->Data.Memory32.Minimum,
                Resource->Data.Memory32.Maximum
            );
*/
            fprint_counted_id("mem",&counter_array[ACPI_RESOURCE_TYPE_MEMORY32]);
            fprintf(stdout,"%x",Resource->Data.Memory32.Minimum);
            break;

        case ACPI_RESOURCE_TYPE_FIXED_MEMORY32:
/*
            fprintf(stdout,"FixedMemory32 - WriteProtect: %d   Address: %08X    AddressLength: %d\n",
                Resource->Data.FixedMemory32.WriteProtect,
                Resource->Data.FixedMemory32.Address,
                Resource->Data.FixedMemory32.AddressLength
            );
*/
            fprint_counted_id("mem",&counter_array[ACPI_RESOURCE_TYPE_MEMORY32]);
            fprintf(stdout,"%x",Resource->Data.FixedMemory32.Address);

            break;

        case ACPI_RESOURCE_TYPE_ADDRESS16:
/*
            fprintf(stdout,"Address16 - Granularity: %d   Minimum: %04X   Maximum: %04X   TranslationOffset: %04X   AddressLength: %d \n",
                Resource->Data.Address16.Address.Granularity,
                Resource->Data.Address16.Address.Minimum,
                Resource->Data.Address16.Address.Maximum,
                Resource->Data.Address16.Address.TranslationOffset,
                Resource->Data.Address16.Address.AddressLength
            );
*/
            break;


        case ACPI_RESOURCE_TYPE_ADDRESS32:
/*
            fprintf(stdout,"Address32 - Granularity: %d   Minimum: %08X   Maximum: %08X   TranslationOffset: %08X   AddressLength: %d \n",
                Resource->Data.Address32.Address.Granularity,
                Resource->Data.Address32.Address.Minimum,
                Resource->Data.Address32.Address.Maximum,
                Resource->Data.Address32.Address.TranslationOffset,
                Resource->Data.Address32.Address.AddressLength
            );
*/
            break;

        case ACPI_RESOURCE_TYPE_END_TAG:
            break;

        case ACPI_RESOURCE_TYPE_ADDRESS64:
        case ACPI_RESOURCE_TYPE_VENDOR:
        case ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64:
        case ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
        case ACPI_RESOURCE_TYPE_GENERIC_REGISTER:
        case ACPI_RESOURCE_TYPE_GPIO:
        case ACPI_RESOURCE_TYPE_FIXED_DMA:
        case ACPI_RESOURCE_TYPE_SERIAL_BUS:
            break;

        default:
            fprintf(stderr,"Unknown resource type %d length %d\n",Resource->Type,Resource->Length);
            break;
    };

    return AE_OK;
};


/* Print a line for this device, if it has a hardware name */
static ACPI_STATUS
PrintDeviceInfo (
    ACPI_HANDLE Object,
    UINT32      NestingLevel,
    void        *Context,
    void        **ReturnValue)
{
    ACPI_STATUS status = AE_OK;
    ACPI_DEVICE_INFO* DeviceInfo = NULL;
    ACPI_BUFFER Resources;
    int i;

    status = AcpiGetObjectInfo(Object, &DeviceInfo);
    //fprintf(stdout, "AcpiGetObjectInfo: %d\n",status);

    if (DeviceInfo && (DeviceInfo->HardwareId.Length > 0)) {
        fprintf(stdout,"%c%d bus=acpi devid=",IsBus(DeviceInfo->HardwareId.String) ? 'B' : 'D', getpid());
        PrintFixedString(DeviceInfo->HardwareId.Length, DeviceInfo->HardwareId.String);

        if (DeviceInfo->UniqueId.Length > 0) {
            fprintf(stdout," index=");
            PrintFixedString(DeviceInfo->UniqueId.Length, DeviceInfo->UniqueId.String);
        };

        if (DeviceInfo->SubsystemId.Length) {
            fprintf(stdout," subsys=");
            PrintFixedString(DeviceInfo->SubsystemId.Length, DeviceInfo->SubsystemId.String);
        };

        if (DeviceInfo->ClassCode.Length) {
            fprintf(stdout," class=");
            PrintFixedString(DeviceInfo->ClassCode.Length, DeviceInfo->ClassCode.String);
        };

        for (i = 0; i < DeviceInfo->CompatibleIdList.Count; ) {
            fprint_counted_id("cid",&i); // includes increment
            PrintFixedString(DeviceInfo->CompatibleIdList.Ids[i-1].Length, DeviceInfo->CompatibleIdList.Ids[i-1].String);
        };


        memset(&Resources,0,sizeof(Resources));
        Resources.Length = ACPI_ALLOCATE_BUFFER;

        /* Get resources for this device */
        status = AcpiGetCurrentResources(Object, &Resources);
        //fprintf(stdout, "AcpiGetCurrentResources: %d\n",status);

        if (status == AE_OK) {
            int print_count[ACPI_RESOURCE_TYPE_SERIAL_BUS];
            memset(print_count,0,sizeof(print_count));

            status = AcpiWalkResourceBuffer( &Resources,
                &PrintResourceInfo,
                print_count);
            //fprintf(stdout, "AcpiWalkResourceBuffer: %d\n",status);
        };

        fprintf(stdout,"\n");
    };

    return AE_OK;
};



/******************************************************************************
 *
 * FUNCTION:    main
 *
 * PARAMETERS:  argc/argv           - Standard argc/argv
 *
 * RETURN:      Status
 *
 * DESCRIPTION: C main function for acpidump utility
 *
 ******************************************************************************/

#ifndef _GNU_EFI
int ACPI_SYSTEM_XFACE
main (
    int                     argc,
    char                    *argv[])
#else
int ACPI_SYSTEM_XFACE
acpi_main (
    int                     argc,
    char                    *argv[])
#endif
{
    int                     Status = 0;
    void* ReturnValue = NULL;

    /* Ensure output is line buffered - prevent partial writes */
    /* enum-devices expects each read() to return a whole line */
    setvbuf(stdout,NULL,_IOLBF,0);

    // print args
    fprintf(stdout,"#%d %s\n",getpid(),argv[0]);

    ThreadCtl(_NTO_TCTL_IO, 0);

    ACPI_DEBUG_INITIALIZE (); /* For debug version only */
    AcpiOsInitialize ();
    Status = AcpiInitializeSubsystem ();

    // Install default handlers
    AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT, 0, ACPI_DEFAULT_HANDLER, ACPI_DEFAULT_HANDLER, 0);
    AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT, 1, ACPI_DEFAULT_HANDLER, ACPI_DEFAULT_HANDLER, 0);
    AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT, 2, ACPI_DEFAULT_HANDLER, ACPI_DEFAULT_HANDLER, 0);

    AcpiDbgLevel = 0;

    AcpiInitializeTables(NULL,32,TRUE);
    AcpiLoadTables();

    Status = AcpiGetDevices(NULL,
        &PrintDeviceInfo,
        NULL,
        &ReturnValue);

    fprintf(stdout,"F%d\n",getpid());

    return (Status);
}
