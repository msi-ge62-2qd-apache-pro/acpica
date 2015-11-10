# acpia

The acpia package is the reference implementation of an ACPI interpreter; essentially, it contains the tools for interacting with an ACPI BIOS.   This is required for enumeration of hardware devices on modern BIOSes, which no longer support the older PNPBIOS standard.  (I'm looking at you, Adlink cPCI-3790.) 

To add support for such systems in QNX's hardware detection layer, we have added a new target to this package: source/tools/enum-acpi.   This binary integrates the ACPI interpreter and execution engine, allowing it to dump a list of hardware devices in the enum-devices format.   This is picked up and used by hwdetect to complete hardware initialization.
