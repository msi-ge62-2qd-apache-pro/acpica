#
# standalone disassembler
#

#
# Note: This makefile is intended to be used from within the native
# ACPICA directory structure, from under generate/unix. It specifically
# places all object files in a generate/unix subdirectory, not within
# the various ACPICA source directories. This prevents collisions
# between different compilations of the same source file with different
# compile options, and prevents pollution of the source code.
#
include ../Makefile.config
FINAL_PROG = ../$(BINDIR)/acpidisasm
PROG = $(OBJDIR)/acpidisasm

#
# Search paths for source files
#
vpath %.c \
    $(ASL_COMPILER)\
    $(ACPICA_DEBUGGER)\
    $(ACPICA_DISASSEMBLER)\
    $(ACPICA_DISPATCHER)\
    $(ACPICA_EXECUTER)\
    $(ACPICA_NAMESPACE)\
    $(ACPICA_PARSER)\
    $(ACPICA_TABLES)\
    $(ACPICA_UTILITIES)\
    $(ACPICA_COMMON)\
    $(ACPICA_OSL)\
    $(ACPIDISASM)


HEADERS = \
    $(wildcard $(ACPIDISASM)/*.h)\
    $(wildcard $(ASL_COMPILER)/*.h)

OBJECTS = \
	$(OBJDIR)/aslmapenter.o\
	$(OBJDIR)/aslstubs.o\
	$(OBJDIR)/admain.o\
	$(OBJDIR)/adisasm.o\
	$(OBJDIR)/acfileio.o\
	$(OBJDIR)/adfile.o\
	$(OBJDIR)/adwalk.o\
	$(OBJDIR)/ahids.o\
	$(OBJDIR)/ahpredef.o\
	$(OBJDIR)/ahtable.o\
	$(OBJDIR)/ahuuids.o\
	$(OBJDIR)/cmfsize.o\
	$(OBJDIR)/dbfileio.o\
	$(OBJDIR)/dmbuffer.o\
	$(OBJDIR)/dmcstyle.o\
	$(OBJDIR)/dmdeferred.o\
	$(OBJDIR)/dmextern.o\
	$(OBJDIR)/dmnames.o\
	$(OBJDIR)/dmopcode.o\
	$(OBJDIR)/dmresrc.o\
	$(OBJDIR)/dmresrcl.o\
	$(OBJDIR)/dmresrcl2.o\
	$(OBJDIR)/dmresrcs.o\
	$(OBJDIR)/dmrestag.o\
	$(OBJDIR)/dmswitch.o\
	$(OBJDIR)/dmtable.o\
	$(OBJDIR)/dmtables.o\
	$(OBJDIR)/dmtbdump.o\
	$(OBJDIR)/dmtbinfo.o\
	$(OBJDIR)/dmutils.o\
	$(OBJDIR)/dmwalk.o\
	$(OBJDIR)/dsargs.o\
	$(OBJDIR)/dscontrol.o\
	$(OBJDIR)/dsfield.o\
	$(OBJDIR)/dsobject.o\
	$(OBJDIR)/dsopcode.o\
	$(OBJDIR)/dspkginit.o\
	$(OBJDIR)/dsutils.o\
	$(OBJDIR)/dswexec.o\
	$(OBJDIR)/dswload.o\
	$(OBJDIR)/dswload2.o\
	$(OBJDIR)/dswscope.o\
	$(OBJDIR)/dswstate.o\
	$(OBJDIR)/exconcat.o\
	$(OBJDIR)/exconvrt.o\
	$(OBJDIR)/excreate.o\
	$(OBJDIR)/exdump.o\
	$(OBJDIR)/exmisc.o\
	$(OBJDIR)/exmutex.o\
	$(OBJDIR)/exnames.o\
	$(OBJDIR)/exoparg1.o\
	$(OBJDIR)/exoparg2.o\
	$(OBJDIR)/exoparg3.o\
	$(OBJDIR)/exoparg6.o\
	$(OBJDIR)/exprep.o\
	$(OBJDIR)/exregion.o\
	$(OBJDIR)/exresnte.o\
	$(OBJDIR)/exresolv.o\
	$(OBJDIR)/exresop.o\
	$(OBJDIR)/exstore.o\
	$(OBJDIR)/exstoren.o\
	$(OBJDIR)/exstorob.o\
	$(OBJDIR)/exsystem.o\
	$(OBJDIR)/exutils.o\
	$(OBJDIR)/getopt.o\
	$(OBJDIR)/nsaccess.o\
	$(OBJDIR)/nsalloc.o\
	$(OBJDIR)/nsdump.o\
	$(OBJDIR)/nsnames.o\
	$(OBJDIR)/nsobject.o\
	$(OBJDIR)/nsparse.o\
	$(OBJDIR)/nssearch.o\
	$(OBJDIR)/nsutils.o\
	$(OBJDIR)/nswalk.o\
	$(OBJDIR)/nsxfobj.o\
	$(OBJDIR)/osunixxf.o\
	$(OBJDIR)/psargs.o\
	$(OBJDIR)/psloop.o\
	$(OBJDIR)/psobject.o\
	$(OBJDIR)/psopcode.o\
	$(OBJDIR)/psopinfo.o\
	$(OBJDIR)/psparse.o\
	$(OBJDIR)/psscope.o\
	$(OBJDIR)/pstree.o\
	$(OBJDIR)/psutils.o\
	$(OBJDIR)/pswalk.o\
	$(OBJDIR)/tbdata.o\
	$(OBJDIR)/tbfadt.o\
	$(OBJDIR)/tbinstal.o\
	$(OBJDIR)/tbprint.o\
	$(OBJDIR)/tbutils.o\
	$(OBJDIR)/tbxface.o\
	$(OBJDIR)/tbxfload.o\
	$(OBJDIR)/utaddress.o\
	$(OBJDIR)/utalloc.o\
	$(OBJDIR)/utascii.o\
	$(OBJDIR)/utbuffer.o\
	$(OBJDIR)/utcache.o\
	$(OBJDIR)/utcopy.o\
	$(OBJDIR)/utdebug.o\
	$(OBJDIR)/utdecode.o\
	$(OBJDIR)/utdelete.o\
	$(OBJDIR)/uterror.o\
	$(OBJDIR)/utexcep.o\
	$(OBJDIR)/utglobal.o\
	$(OBJDIR)/uthex.o\
	$(OBJDIR)/utinit.o\
	$(OBJDIR)/utlock.o\
	$(OBJDIR)/utmath.o\
	$(OBJDIR)/utmisc.o\
	$(OBJDIR)/utmutex.o\
	$(OBJDIR)/utnonansi.o\
	$(OBJDIR)/utobject.o\
	$(OBJDIR)/utownerid.o\
	$(OBJDIR)/utresdecode.o\
	$(OBJDIR)/utresrc.o\
	$(OBJDIR)/utstate.o\
	$(OBJDIR)/utstrtoul64.o\
	$(OBJDIR)/utstrsuppt.o\
	$(OBJDIR)/utstring.o\
	$(OBJDIR)/utuuid.o\
	$(OBJDIR)/utxface.o\
	$(OBJDIR)/utxferror.o

#
# Flags specific to iASL compiler
#
CFLAGS += \
    -DACPI_ASL_COMPILER\
    -DACPI_DISASM_APP\
    -I$(ACPIDISASM)\
    -I$(ASL_COMPILER)\
    -I$(OBJDIR)


#
# Common Rules
#
include ../Makefile.rules

