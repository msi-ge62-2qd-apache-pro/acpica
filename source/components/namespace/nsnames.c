/*******************************************************************************
 *
 * Module Name: nsnames - Name manipulation and search
 *
 ******************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2016, Intel Corp.
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
#include "accommon.h"
#include "amlcode.h"
#include "acnamesp.h"


#define _COMPONENT          ACPI_NAMESPACE
        ACPI_MODULE_NAME    ("nsnames")


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsGetExternalPathname
 *
 * PARAMETERS:  Node            - Namespace node whose pathname is needed
 *
 * RETURN:      Pointer to storage containing the fully qualified name of
 *              the node, In external format (name segments separated by path
 *              separators.)
 *
 * DESCRIPTION: Used to obtain the full pathname to a namespace node, usually
 *              for error and debug statements.
 *
 ******************************************************************************/

char *
AcpiNsGetExternalPathname (
    ACPI_NAMESPACE_NODE     *Node)
{
    char                    *NameBuffer;


    ACPI_FUNCTION_TRACE_PTR (NsGetExternalPathname, Node);


    NameBuffer = AcpiNsGetNormalizedPathname (Node, FALSE);
    return_PTR (NameBuffer);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsGetPathnameLength
 *
 * PARAMETERS:  Node        - Namespace node
 *
 * RETURN:      Length of path, including prefix
 *
 * DESCRIPTION: Get the length of the pathname string for this node
 *
 ******************************************************************************/

ACPI_SIZE
AcpiNsGetPathnameLength (
    ACPI_NAMESPACE_NODE     *Node)
{
    ACPI_SIZE               Size;


    ACPI_FUNCTION_ENTRY ();


    Size = AcpiNsBuildNormalizedPath (Node, NULL, 0, FALSE);
    return (Size);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsHandleToPathname
 *
 * PARAMETERS:  TargetHandle            - Handle of named object whose name is
 *                                        to be found
 *              Buffer                  - Where the pathname is returned
 *              NoTrailing              - Remove trailing '_' for each name
 *                                        segment
 *
 * RETURN:      Status, Buffer is filled with pathname if status is AE_OK
 *
 * DESCRIPTION: Build and return a full namespace pathname
 *
 ******************************************************************************/

ACPI_STATUS
AcpiNsHandleToPathname (
    ACPI_HANDLE             TargetHandle,
    ACPI_BUFFER             *Buffer,
    BOOLEAN                 NoTrailing)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_SIZE               RequiredSize;


    ACPI_FUNCTION_TRACE_PTR (NsHandleToPathname, TargetHandle);


    Node = AcpiNsValidateHandle (TargetHandle);
    if (!Node)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Determine size required for the caller buffer */

    RequiredSize = AcpiNsBuildNormalizedPath (Node, NULL, 0, NoTrailing);
    if (!RequiredSize)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Validate/Allocate/Clear caller buffer */

    Status = AcpiUtInitializeBuffer (Buffer, RequiredSize);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Build the path in the caller buffer */

    (void) AcpiNsBuildNormalizedPath (Node, Buffer->Pointer,
        RequiredSize, NoTrailing);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "%s [%X]\n",
        (char *) Buffer->Pointer, (UINT32) RequiredSize));
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsBuildNormalizedPath
 *
 * PARAMETERS:  Node        - Namespace node
 *              FullPath    - Where the path name is returned
 *              PathSize    - Size of returned path name buffer
 *              NoTrailing  - Remove trailing '_' from each name segment
 *
 * RETURN:      Return 1 if the AML path is empty, otherwise returning (length
 *              of pathname + 1) which means the 'FullPath' contains a trailing
 *              null.
 *
 * DESCRIPTION: Build and return a full namespace pathname.
 *              Note that if the size of 'FullPath' isn't large enough to
 *              contain the namespace node's path name, the actual required
 *              buffer length is returned, and it should be greater than
 *              'PathSize'. So callers are able to check the returning value
 *              to determine the buffer size of 'FullPath'.
 *
 ******************************************************************************/

#define ACPI_PATH_PUT8(Path, Size, Byte, Length)    \
    do {                                            \
        if ((Length) < (Size))                      \
        {                                           \
            (Path)[(Length)] = (Byte);              \
        }                                           \
        (Length)++;                                 \
    } while (0)

UINT32
AcpiNsBuildNormalizedPath (
    ACPI_NAMESPACE_NODE     *Node,
    char                    *FullPath,
    UINT32                  PathSize,
    BOOLEAN                 NoTrailing)
{
    UINT32                  Length = 0, i;
    char                    Name[ACPI_NAME_SIZE];
    BOOLEAN                 DoNoTrailing;
    char                    c;
    char                    *Left;
    char                    *Right;
    ACPI_NAMESPACE_NODE     *NextNode;


    ACPI_FUNCTION_TRACE_PTR (NsBuildNormalizedPath, Node);


    /*
     * Make sure the PathSize is correct, so that we don't need to
     * validate both FullPath and PathSize.
     */
    if (!FullPath)
    {
        PathSize = 0;
    }

    if (!Node)
    {
        goto BuildTrailingNull;
    }

    NextNode = Node;
    while (NextNode && NextNode != AcpiGbl_RootNode)
    {
        if (NextNode != Node)
        {
            ACPI_PATH_PUT8(FullPath, PathSize, AML_DUAL_NAME_PREFIX, Length);
        }

        ACPI_MOVE_32_TO_32 (Name, &NextNode->Name);
        DoNoTrailing = NoTrailing;
        for (i = 0; i < 4; i++)
        {
            c = Name[4-i-1];
            if (DoNoTrailing && c != '_')
            {
                DoNoTrailing = FALSE;
            }
            if (!DoNoTrailing)
            {
                ACPI_PATH_PUT8(FullPath, PathSize, c, Length);
            }
        }

        NextNode = NextNode->Parent;
    }

    ACPI_PATH_PUT8(FullPath, PathSize, AML_ROOT_PREFIX, Length);

    /* Reverse the path string */

    if (Length <= PathSize)
    {
        Left = FullPath;
        Right = FullPath+Length - 1;

        while (Left < Right)
        {
            c = *Left;
            *Left++ = *Right;
            *Right-- = c;
        }
    }

    /* Append the trailing null */

BuildTrailingNull:
    ACPI_PATH_PUT8 (FullPath, PathSize, '\0', Length);

//undef ACPI_PATH_PUT8

    ACPI_DEBUG_PRINT ((ACPI_DB_NAMES, "Node [%4.4s], Path: %s\n",
        Node->Name.Ascii, FullPath));

    return_UINT32 (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsGetNormalizedPathname
 *
 * PARAMETERS:  Node            - Namespace node whose pathname is needed
 *              NoTrailing      - Remove trailing '_' from each name segment
 *
 * RETURN:      Pointer to storage containing the fully qualified name of
 *              the node, In external format (name segments separated by path
 *              separators.)
 *
 * DESCRIPTION: Used to obtain the full pathname to a namespace node, usually
 *              for error and debug statements. All trailing '_' will be
 *              removed from the full pathname if 'NoTrailing' is specified..
 *
 ******************************************************************************/

char *
AcpiNsGetNormalizedPathname (
    ACPI_NAMESPACE_NODE     *Node,
    BOOLEAN                 NoTrailing)
{
    char                    *NameBuffer;
    ACPI_SIZE               Size;


    ACPI_FUNCTION_TRACE_PTR (NsGetNormalizedPathname, Node);


    /* Calculate required buffer size based on depth below root */

    Size = AcpiNsBuildNormalizedPath (Node, NULL, 0, NoTrailing);
    if (!Size)
    {
        return_PTR (NULL);
    }

    /* Allocate a buffer to be returned to caller */

    NameBuffer = ACPI_ALLOCATE_ZEROED (Size);
    if (!NameBuffer)
    {
        ACPI_ERROR ((AE_INFO,
            "Could not allocate %u bytes", (UINT32) Size));
        return_PTR (NULL);
    }

    /* Build the path in the allocated buffer */

    (void) AcpiNsBuildNormalizedPath (Node, NameBuffer, Size, NoTrailing);

    return_PTR (NameBuffer);
}
