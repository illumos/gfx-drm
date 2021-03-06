#
# Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# uts/intel/amd64_gart/Makefile
#

#
#	This makefile drives the framework of agp protocol
#	(amd64_gart) kernel module.
#
#
#	Path to the base of the uts directory tree (usually /usr/src/uts).
#
UTSBASE = ../..

#
#	Define the module and object file sets.
#
MODULE		= amd64_gart
OBJECTS		= $(AMD64GART_OBJS:%=$(OBJS_DIR)/%)
LINTS		= $(AMD64GART_OBJS:%.o=$(LINTS_DIR)/%.ln)
ROOTMODULE	= $(ROOT_DRV_DIR)/$(MODULE)

#
#	Include common rules.
#
include $(UTSBASE)/intel/Makefile.intel
AMD64GART_OBJS += amd64_gart.o

#
#	Define targets
#
ALL_TARGET	= $(BINARY)
LINT_TARGET	= $(MODULE).lint
INSTALL_TARGET	= $(BINARY) $(ROOTMODULE)

#
#	Default build targets.
#
.KEEP_STATE:

def:		$(DEF_DEPS)

all:		$(ALL_DEPS)

clean:		$(CLEAN_DEPS)

clobber:	$(CLOBBER_DEPS)

lint:		$(LINT_DEPS)

modlintlib:	$(MODLINTLIB_DEPS)

clean.lint:	$(CLEAN_LINT_DEPS)

install:	$(INSTALL_DEPS)

$(OBJS_DIR)/%.o:		$(UTSBASE)/intel/io/agpgart/%.c
	$(COMPILE.c) -o $@ $<
	$(CTFCONVERT_O)

$(LINTS_DIR)/%.ln:		$(UTSBASE)/intel/io/agpgart/%.c
	@($(LHEAD) $(LINT.c) $< $(LTAIL))

#
#	Include common targets.
#
include $(UTSBASE)/intel/Makefile.targ
