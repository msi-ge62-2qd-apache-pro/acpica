/******************************************************************************
 *
 * Module Name: dtcompilerfunction.h - header for data table functions
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2017, Intel Corp.
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
 *****************************************************************************
 *
 * Alternatively, you may choose to be licensed under the terms of the
 * following license:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement for further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Alternatively, you may choose to be licensed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 *****************************************************************************/

#define __DTCOMPILERFUNCTIONS_H__

#ifndef _DTCOMPILERFUNCTIONS
#define _DTCOMPILERFUNCTIONS

/*
 * Structure used for each individual field within an ACPI table
 */
typedef struct dt_field
{
    char                    *Name;       /* Field name (from name : value) */
    char                    *Value;      /* Field value (from name : value) */
    UINT32                  StringLength;/* Length of Value */
    struct dt_field         *Next;       /* Next field */
    struct dt_field         *NextLabel;  /* If field is a label, next label */
    UINT32                  Line;        /* Line number for this field */
    UINT32                  ByteOffset;  /* Offset in source file for field */
    UINT32                  NameColumn;  /* Start column for field name */
    UINT32                  Column;      /* Start column for field value */
    UINT32                  TableOffset; /* Binary offset within ACPI table */
    UINT8                   Flags;

} DT_FIELD;


/* dttable - individual table compilation */

ACPI_STATUS
DtCompileFacs (
    DT_FIELD                **PFieldList);

ACPI_STATUS
DtCompileRsdp (
    DT_FIELD                **PFieldList);

ACPI_STATUS
DtCompileAsf (
    void                    **PFieldList);

ACPI_STATUS
DtCompileCpep (
    void                    **PFieldList);

ACPI_STATUS
DtCompileCsrt (
    void                    **PFieldList);

ACPI_STATUS
DtCompileDbg2 (
    void                    **PFieldList);

ACPI_STATUS
DtCompileDmar (
    void                    **PFieldList);

ACPI_STATUS
DtCompileDrtm (
    void                    **PFieldList);

ACPI_STATUS
DtCompileEinj (
    void                    **PFieldList);

ACPI_STATUS
DtCompileErst (
    void                    **PFieldList);

ACPI_STATUS
DtCompileFadt (
    void                    **PFieldList);

ACPI_STATUS
DtCompileFpdt (
    void                    **PFieldList);

ACPI_STATUS
DtCompileGtdt (
    void                    **PFieldList);

ACPI_STATUS
DtCompileHest (
    void                    **PFieldList);

ACPI_STATUS
DtCompileHmat (
    void                    **PFieldList);

ACPI_STATUS
DtCompileIort (
    void                    **PFieldList);

ACPI_STATUS
DtCompileIvrs (
    void                    **PFieldList);

ACPI_STATUS
DtCompileLpit (
    void                    **PFieldList);

ACPI_STATUS
DtCompileMadt (
    void                    **PFieldList);

ACPI_STATUS
DtCompileMcfg (
    void                    **PFieldList);

ACPI_STATUS
DtCompileMpst (
    void                    **PFieldList);

ACPI_STATUS
DtCompileMsct (
    void                    **PFieldList);

ACPI_STATUS
DtCompileMtmr (
    void                    **PFieldList);

ACPI_STATUS
DtCompileNfit (
    void                    **PFieldList);

ACPI_STATUS
DtCompilePcct (
    void                    **PFieldList);

ACPI_STATUS
DtCompilePdtt (
    void                    **PFieldList);

ACPI_STATUS
DtCompilePmtt (
    void                    **PFieldList);

ACPI_STATUS
DtCompilePptt (
    void                    **PFieldList);

ACPI_STATUS
DtCompileRsdt (
    void                    **PFieldList);

ACPI_STATUS
DtCompileS3pt (
    DT_FIELD                **PFieldList);

ACPI_STATUS
DtCompileSdev (
    void                    **PFieldList);

ACPI_STATUS
DtCompileSlic (
    void                    **PFieldList);

ACPI_STATUS
DtCompileSlit (
    void                    **PFieldList);

ACPI_STATUS
DtCompileSrat (
    void                    **PFieldList);

ACPI_STATUS
DtCompileStao (
    void                    **PFieldList);

ACPI_STATUS
DtCompileTcpa (
    void                    **PFieldList);

ACPI_STATUS
DtCompileTpm2 (
    void                    **PFieldList);

ACPI_STATUS
DtCompileUefi (
    void                    **PFieldList);

ACPI_STATUS
DtCompileVrtc (
    void                    **PFieldList);

ACPI_STATUS
DtCompileWdat (
    void                    **PFieldList);

ACPI_STATUS
DtCompileWpbt (
    void                    **PFieldList);

ACPI_STATUS
DtCompileXsdt (
    void                    **PFieldList);

ACPI_STATUS
DtCompileGeneric (
    void                    **PFieldList,
    char                    *TermFieldName,
    UINT32                  *PFieldLength);

ACPI_DMTABLE_INFO *
DtGetGenericTableInfo (
    char                    *Name);


/* ACPI Table templates */

extern const unsigned char  TemplateAsf[];
extern const unsigned char  TemplateBoot[];
extern const unsigned char  TemplateBert[];
extern const unsigned char  TemplateBgrt[];
extern const unsigned char  TemplateCpep[];
extern const unsigned char  TemplateCsrt[];
extern const unsigned char  TemplateDbg2[];
extern const unsigned char  TemplateDbgp[];
extern const unsigned char  TemplateDmar[];
extern const unsigned char  TemplateDrtm[];
extern const unsigned char  TemplateEcdt[];
extern const unsigned char  TemplateEinj[];
extern const unsigned char  TemplateErst[];
extern const unsigned char  TemplateFadt[];
extern const unsigned char  TemplateFpdt[];
extern const unsigned char  TemplateGtdt[];
extern const unsigned char  TemplateHest[];
extern const unsigned char  TemplateHmat[];
extern const unsigned char  TemplateHpet[];
extern const unsigned char  TemplateIort[];
extern const unsigned char  TemplateIvrs[];
extern const unsigned char  TemplateLpit[];
extern const unsigned char  TemplateMadt[];
extern const unsigned char  TemplateMcfg[];
extern const unsigned char  TemplateMchi[];
extern const unsigned char  TemplateMpst[];
extern const unsigned char  TemplateMsct[];
extern const unsigned char  TemplateMsdm[];
extern const unsigned char  TemplateMtmr[];
extern const unsigned char  TemplateNfit[];
extern const unsigned char  TemplatePcct[];
extern const unsigned char  TemplatePdtt[];
extern const unsigned char  TemplatePmtt[];
extern const unsigned char  TemplatePptt[];
extern const unsigned char  TemplateRasf[];
extern const unsigned char  TemplateRsdt[];
extern const unsigned char  TemplateS3pt[];
extern const unsigned char  TemplateSbst[];
extern const unsigned char  TemplateSdei[];
extern const unsigned char  TemplateSdev[];
extern const unsigned char  TemplateSlic[];
extern const unsigned char  TemplateSlit[];
extern const unsigned char  TemplateSpcr[];
extern const unsigned char  TemplateSpmi[];
extern const unsigned char  TemplateSrat[];
extern const unsigned char  TemplateStao[];
extern const unsigned char  TemplateTcpa[];
extern const unsigned char  TemplateTpm2[];
extern const unsigned char  TemplateUefi[];
extern const unsigned char  TemplateVrtc[];
extern const unsigned char  TemplateWaet[];
extern const unsigned char  TemplateWdat[];
extern const unsigned char  TemplateWddt[];
extern const unsigned char  TemplateWdrt[];
extern const unsigned char  TemplateWpbt[];
extern const unsigned char  TemplateWsmt[];
extern const unsigned char  TemplateXenv[];
extern const unsigned char  TemplateXsdt[];


#endif
