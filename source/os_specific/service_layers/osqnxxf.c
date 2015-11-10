

#include "acpi.h"
#include "accommon.h"
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <hw/pci.h>
#include <errno.h>
#include <unistd.h>

#define _COMPONENT          ACPI_OS_SERVICES
        ACPI_MODULE_NAME    ("osqnxxf")


static int pci_handle = -1;

typedef struct AcpiInterruptContext {
    UINT32 InterruptNumber;
    ACPI_OSD_HANDLER ServiceRoutine;
    void* Context;
    int handle;
} AcpiInterruptContext;

#define MAX_ACPI_INTERRUPTS 4
static AcpiInterruptContext InterruptContexts[MAX_ACPI_INTERRUPTS] = { { 0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };

const struct sigevent* AcpiInterruptHandler(void* Context, int intr);


const struct sigevent* AcpiInterruptHandler(void* Context, int intr) {
    AcpiInterruptContext* InterruptContext = (AcpiInterruptContext*) Context;
    InterruptContext->ServiceRoutine(InterruptContext->Context);
    return NULL;
};




static ACPI_SIZE
AcpiOsGetPageSize (
    void)
{
    return sysconf (_SC_PAGESIZE);
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
    UINT8                   *MappedMemory;
    ACPI_PHYSICAL_ADDRESS   Offset;
    ACPI_SIZE               PageSize;

    /* Align the offset to use mmap */

    PageSize = AcpiOsGetPageSize ();
    Offset = Where % PageSize;

    /* Map the table header to get the length of the full table */
    MappedMemory = mmap_device_memory(NULL, (Length + Offset), PROT_NOCACHE | PROT_READ | PROT_WRITE, 0, (Where - Offset));
    if (MappedMemory == MAP_FAILED)
    {
        fprintf (stderr, "Cannot map %08lld\n", Where);
        return (NULL);
    }

    return (ACPI_CAST8 (MappedMemory + Offset));
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
    ACPI_PHYSICAL_ADDRESS   Offset;
    ACPI_SIZE               PageSize;


    PageSize = AcpiOsGetPageSize ();
    Offset = ACPI_TO_INTEGER (Where) % PageSize;
    munmap_device_memory ((UINT8 *) Where - Offset, (Length + Offset));
}



/******************************************************************************
 *
 * FUNCTION:    Spinlock interfaces
 *
 * DESCRIPTION: Map these interfaces to semaphore interfaces
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsCreateLock (
    ACPI_SPINLOCK           *OutHandle)
{
    if (!OutHandle) return AE_BAD_ADDRESS;

    *OutHandle = (intrspin_t*) malloc(sizeof(intrspin_t));
    if (!*OutHandle) return AE_NO_MEMORY;

    memset( *OutHandle, 0, sizeof(ACPI_SPINLOCK));

    return AE_OK;
}


void
AcpiOsDeleteLock (
    ACPI_SPINLOCK           Handle)
{
    free(Handle);
}


ACPI_CPU_FLAGS
AcpiOsAcquireLock (
    ACPI_HANDLE             Handle)
{
    InterruptLock(Handle);
    return (0);
}


void
AcpiOsReleaseLock (
    ACPI_SPINLOCK           Handle,
    ACPI_CPU_FLAGS          Flags)
{
    InterruptUnlock(Handle);
}




/******************************************************************************
 *
 * FUNCTION:    AcpiOsInstallInterruptHandler
 *
 * PARAMETERS:  InterruptNumber     - Level handler should respond to.
 *              Isr                 - Address of the ACPI interrupt handler
 *              ExceptPtr           - Where status is returned
 *
 * RETURN:      Handle to the newly installed handler.
 *
 * DESCRIPTION: Install an interrupt handler. Used to install the ACPI
 *              OS-independent handler.
 *
 *****************************************************************************/


UINT32
AcpiOsInstallInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine,
    void                    *Context)
{
    size_t index;

    for (index = 0; index < MAX_ACPI_INTERRUPTS; ++index) {
        if (InterruptContexts[index].ServiceRoutine == NULL) break;
    };
    if (index >= MAX_ACPI_INTERRUPTS) {
        return AE_LIMIT;
    };

    InterruptContexts[index].InterruptNumber = InterruptNumber;
    InterruptContexts[index].ServiceRoutine = ServiceRoutine;
    InterruptContexts[index].Context = Context;

    InterruptContexts[index].handle = InterruptAttach(InterruptNumber, &AcpiInterruptHandler, &InterruptContexts[index], 0, _NTO_INTR_FLAGS_PROCESS);
    if (InterruptContexts[index].handle == -1) {
        InterruptContexts[index].ServiceRoutine = NULL;
        return AE_ERROR;
    } else {
        return AE_OK;
    };
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsRemoveInterruptHandler
 *
 * PARAMETERS:  Handle              - Returned when handler was installed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Uninstalls an interrupt handler.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsRemoveInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine)
{
    size_t index;

    for (index = 0; index < MAX_ACPI_INTERRUPTS; ++index) {

        if ((InterruptContexts[index].ServiceRoutine == ServiceRoutine)
          && (InterruptContexts[index].InterruptNumber == InterruptNumber)) break;
    };

    if (index >= MAX_ACPI_INTERRUPTS) {
        return AE_BAD_PARAMETER;
    };

    InterruptDetach(InterruptContexts[index].handle);

    return (AE_OK);
}





/******************************************************************************
 *
 * FUNCTION:    AcpiOsStall
 *
 * PARAMETERS:  microseconds        - Time to sleep
 *
 * RETURN:      Blocks until sleep is completed.
 *
 * DESCRIPTION: Sleep at microsecond granularity
 *
 *****************************************************************************/

void
AcpiOsStall (
    UINT32                  microseconds)
{
    uint64_t nanoseconds = 1000ull * microseconds;
    nanospin_ns(nanoseconds);
}



/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadPciConfiguration
 *
 * PARAMETERS:  PciId               - Seg/Bus/Dev
 *              PciRegister         - Device Register
 *              Value               - Buffer where value is placed
 *              Width               - Number of bits
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read data from PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsReadPciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  PciRegister,
    UINT64                  *Value,
    UINT32                  Width)
{
    // Alas QNX renumbers the buses :(
    // But we try anyways: hopefully the numbering is similar??
    int rv;

    if (pci_handle == -1) {
        pci_handle = pci_attach(0);
        if (pci_handle == -1) {
            fprintf(stderr,"Unable to connect to PCI server: %d\n",errno);
            return AE_ACCESS;
        };
    };

    switch(Width) {
        case 8: rv = pci_read_config8(PciId->Bus, PCI_DEVFUNC(PciId->Device, PciId->Function), PciRegister, 1, Value); break;
        case 16: rv = pci_read_config16(PciId->Bus, PCI_DEVFUNC(PciId->Device, PciId->Function), PciRegister, 1, Value); break;
        case 32: rv = pci_read_config32(PciId->Bus, PCI_DEVFUNC(PciId->Device, PciId->Function), PciRegister, 1, Value); break;
        default:
            return AE_BAD_PARAMETER;
    }
    //fprintf(stderr,"PCIRead: %d:%d:%d:%d %d -> %08X [%d]\n", PciId->Segment, PciId->Bus, PciId->Device, PciId->Function, Width, *(uint32_t*)Value, rv);
    return (rv == PCI_SUCCESS) ? (AE_OK) : AE_ERROR;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritePciConfiguration
 *
 * PARAMETERS:  PciId               - Seg/Bus/Dev
 *              PciRegister         - Device Register
 *              Value               - Value to be written
 *              Width               - Number of bits
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Write data to PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWritePciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  PciRegister,
    UINT64                  Value,
    UINT32                  Width)
{
    //fprintf(stderr,"PCIWrite: %d:%d:%d:%d %d -> %08llX\n", PciId->Segment, PciId->Bus, PciId->Device, PciId->Function, Width, Value);
    int rv;

    if (pci_handle == -1) {
        pci_handle = pci_attach(0);
        if (pci_handle == -1) {
            fprintf(stderr,"Unable to connect to PCI server: %d\n",errno);
            return AE_ACCESS;
        };
    };

    switch(Width) {
        case 8: rv = pci_write_config8(PciId->Bus, PCI_DEVFUNC(PciId->Device, PciId->Function), PciRegister, 1, (char*)&Value); break;
        case 16: rv = pci_write_config16(PciId->Bus, PCI_DEVFUNC(PciId->Device, PciId->Function), PciRegister, 1, (char*)&Value); break;
        case 32: rv = pci_write_config32(PciId->Bus, PCI_DEVFUNC(PciId->Device, PciId->Function), PciRegister, 1, (char*)&Value); break;
        default:
            return AE_BAD_PARAMETER;
    }
    return (rv == PCI_SUCCESS) ? (AE_OK) : AE_ERROR;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadPort
 *
 * PARAMETERS:  Address             - Address of I/O port/register to read
 *              Value               - Where value is placed
 *              Width               - Number of bits
 *
 * RETURN:      Value read from port
 *
 * DESCRIPTION: Read data from an I/O port or register
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsReadPort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  *Value,
    UINT32                  Width)
{
    ACPI_STATUS ret = AE_OK;
    size_t len = (Width/8);
    uintptr_t addr = mmap_device_io(len, Address);
    if (addr == MAP_DEVICE_FAILED) {
        fprintf(stderr,"Unable to map io at %08llX length %d: %d\n",Address,len,errno);
        return AE_ACCESS;
    };


    switch (Width) {
        case 8: *(uint8_t*) Value = in8(addr); break;
        case 16: *(uint16_t*) Value = in16(addr); break;
        case 32: *(uint32_t*) Value = in32(addr); break;
        //case 64: *(uint64_t*) Value = *(uint64_t*)addr; break;
        default:
            fprintf(stderr,"Invalid bit width to io read, paddr %08llX: %d\n",Address,Width);
            ret = AE_BAD_PARAMETER;
    }

    munmap_device_io(addr,len);
    return ret;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritePort
 *
 * PARAMETERS:  Address             - Address of I/O port/register to write
 *              Value               - Value to write
 *              Width               - Number of bits
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write data to an I/O port or register
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWritePort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  Value,
    UINT32                  Width)
{
    ACPI_STATUS ret = AE_OK;
    size_t len = (Width/8);
    uintptr_t addr = mmap_device_io(len, Address);
    if (addr == MAP_DEVICE_FAILED) {
        fprintf(stderr,"Unable to map io at %08llX length %d: %d\n",Address,len,errno);
        return AE_ACCESS;
    };

    switch (Width) {
        case 8: out8(addr, Value); break;
        case 16: out16(addr, Value); break;
        case 32: out32(addr, Value); break;
        //case 64: *(uint64_t*)addr = *(uint64_t*) Value; break;
        default:
            fprintf(stderr,"Invalid bit width to io write, paddr %08llX: %d\n",Address,Width);
            ret = AE_BAD_PARAMETER;
    }

    munmap_device_io(addr,len);
    return ret;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadMemory
 *
 * PARAMETERS:  Address             - Physical Memory Address to read
 *              Value               - Where value is placed
 *              Width               - Number of bits (8,16,32, or 64)
 *
 * RETURN:      Value read from physical memory address. Always returned
 *              as a 64-bit integer, regardless of the read width.
 *
 * DESCRIPTION: Read data from a physical memory address
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsReadMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  *Value,
    UINT32                  Width)
{
    ACPI_STATUS ret = AE_OK;
    size_t len = (Width/8);
    void* addr = mmap_device_memory(NULL, len, PROT_NOCACHE | PROT_READ, 0, Address);
    if (!addr) {
        fprintf(stderr,"Unable to map memory to paddr %08llX: %d\n",Address,errno);
        return AE_ACCESS;
    };

    switch (Width) {
        case 8: *(uint8_t*) Value = *(uint8_t*)addr; break;
        case 16: *(uint16_t*) Value = *(uint16_t*)addr; break;
        case 32: *(uint32_t*) Value = *(uint32_t*)addr; break;
        case 64: *(uint64_t*) Value = *(uint64_t*)addr; break;
        default:
            fprintf(stderr,"Invalid bit width to memory read, paddr %08llX: %d\n",Address,Width);
            ret = AE_BAD_PARAMETER;
    }

    munmap_device_memory(addr,len);
    return ret;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWriteMemory
 *
 * PARAMETERS:  Address             - Physical Memory Address to write
 *              Value               - Value to write
 *              Width               - Number of bits (8,16,32, or 64)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write data to a physical memory address
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWriteMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  Value,
    UINT32                  Width)
{
    ACPI_STATUS ret = AE_OK;
    size_t len = (Width/8);
    void* addr = mmap_device_memory(NULL, len, PROT_NOCACHE | PROT_WRITE, 0, Address);
    if (!addr) {
        fprintf(stderr,"Unable to map memory to paddr %08llX: %d\n",Address,errno);
        return AE_ACCESS;
    };

    switch (Width) {
        case 8: *(uint8_t*)addr = Value; break;
        case 16: *(uint16_t*)addr = Value; break;
        case 32: *(uint32_t*)addr = Value; break;
        case 64: *(uint64_t*)addr = Value; break;
        default:
            fprintf(stderr,"Invalid bit width to memory write, paddr %08llX: %d\n",Address,Width);
            ret = AE_BAD_PARAMETER;
    }

    munmap_device_memory(addr,len);
    return ret;}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadable
 *
 * PARAMETERS:  Pointer             - Area to be verified
 *              Length              - Size of area
 *
 * RETURN:      TRUE if readable for entire length
 *
 * DESCRIPTION: Verify that a pointer is valid for reading
 *
 *****************************************************************************/

BOOLEAN
AcpiOsReadable (
    void                    *Pointer,
    ACPI_SIZE               Length)
{

    return (TRUE);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritable
 *
 * PARAMETERS:  Pointer             - Area to be verified
 *              Length              - Size of area
 *
 * RETURN:      TRUE if writable for entire length
 *
 * DESCRIPTION: Verify that a pointer is valid for writing
 *
 *****************************************************************************/

BOOLEAN
AcpiOsWritable (
    void                    *Pointer,
    ACPI_SIZE               Length)
{

    return (TRUE);
}




ACPI_PHYSICAL_ADDRESS
AcpiOsGetRootPointer (
    void)
{
    ACPI_PHYSICAL_ADDRESS TableAddress;
    ACPI_STATUS result = AcpiFindRootPointer(&TableAddress);

    if (result == AE_OK) {
        return TableAddress;
    } else {
        return 0;
    };
};
