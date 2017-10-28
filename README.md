## Fork of Intel's iasl for use in OS X

Originally, this fork was only to have the changes required in order to rebuild Intel's version of iasl using the development tools provided by Xcode in OS X.  By making the few changes required, it was possible to keep this fork up-to-date with Intel's github repo (https://github.com/acpica/acpica)

At this point, it has several changes that make it easier to deal with the process of patching OEM ACPI files.  A number of errors have been changed to warnings and a few disassembler features have been turned off such that the output doesn't confuse the MaciASL parser.  Those changes are detailed later in this document.


### Downloads

Downloads of the built binary are kept on bitbucket:

https://bitbucket.org/RehabMan/acpica/downloads/


### How to install

Download the binary (see above), extract it from ZIP, and copy the iasl binary to /usr/bin

```
cd to-directory-where-you-extracted-iasl
# assuming cwd is set to the location of the binary
sudo cp iasl /usr/bin
```

Then verify you installed it correctly.

```
which iasl
```

Should show:
```
/usr/bin/iasl
```

And:
```
iasl -v
```

Should show something like:
```
Intel ACPI Component Architecture
ASL+ Optimizing Compiler version 20160313-64(RM)
Copyright (c) 2000 - 2016 Intel Corporation

```


### MaciASL

My fork of MaciASL is kept in sync with the latest iasl here.

See here: https://github.com/RehabMan/OS-X-MaciASL-patchmatic


### Building from source

You can build with current Xcode tools.

Get a copy of the project:
```
mkdir ~/Projects
cd ~/Projects
git clone https://github.com/RehabMan/Intel-iasl.git iasl.git
```

Build it:
```
cd ~/Projects/iasl.git
make
```

Install it:
```
cd ~/Projects/iasl.git
sudo make install
```

And if you have MaciASL installed:
```
sudo cp /usr/bin/iasl /Applications/MaciASL.app/Contents/MacOS/iasl61
```


### Differences between the Intel version

Modified to build with Xcode tools.

Comments that would confuse MaciASL's parser are not implemented.

Errors changed to warnings:

'Illegal method invocation as target operand' (6126->3126)

'Illegal open scope on external object from within DSDT' (6148->3148)

'Min/Max/Length/Gran are all zero, but no resource tag' (6090->3090)

'Invalid combination of Length and Min/Max fixed flags' (6043->3043, one form only)

'Length is larger than Min/Max window' (6049->3049)

'Length is not equal to fixed Min/Max window' (6050->3050)

'Reserved name must be a control method (with zero arguments)' (6103->3103)

'invalid object type for reserved name' (6105->3105)

'Non-hex letters must be upper case' (6136->3136)

'Result is not used, operator has no effect' (6114->3114)


You can use the -Rd flag to disable these changes regarding errors vs. warnings.
