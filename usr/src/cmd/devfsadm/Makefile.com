#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

include $(SRC)/lib/Makefile.lib

COMMON = ..
UTSBASE = $(SRC)/uts

LINKMOD_DIR = linkmod
DEVFSADM_DIR = devfsadm

CLOBBERFILES = $(LINK_MODS)

LINK_OBJS_CMN =

LINK_OBJS =	$(LINK_OBJS_CMN) \
		$(LINK_OBJS_$(MACH))

LINK_MODS =	$(LINK_OBJS:%.o=SUNW_%.so)

CPPFLAGS +=	-D_POSIX_PTHREAD_SEMANTICS -D_REENTRANT \
		-I$(COMMON) -I$(UTSBASE)/common
CFLAGS += $(CCVERBOSE) $(C_PICFLAGS)

# Define the dependencies required by devfsadm and all shared objects.
LDLIBS +=		-ldevinfo

# All libraries are built from the same SUNW_%.so rule (see below), and define
# their own SONAME using -h explicitly.  Null the generic -h macro that gets
# inherited from Makefile.lib, otherwise we'll get two -h definitions.
HSONAME =

OBJS = $(LINK_OBJS)

POFILES =
POFILE =

# install specifics

ROOTLIB_DEVFSADM = $(ROOTLIBDIR)/$(DEVFSADM_DIR)
ROOTLIB_DEVFSADM_LINKMOD = $(ROOTLIB_DEVFSADM)/$(LINKMOD_DIR)
ROOTLIB_DEVFSADM_LINK_MODS = $(LINK_MODS:%=$(ROOTLIB_DEVFSADM_LINKMOD)/%)

FILEMODE= 755

all :=		TARGET= all
install :=	TARGET= install
clean :=	TARGET= clean
clobber :=	TARGET= clobber
lint :=		TARGET= lint

.KEEP_STATE:

all: $(LINK_MODS)

install: all				\
	$(ROOTLIB_DEVFSADM)		\
	$(ROOTLIB_DEVFSADM_LINKMOD)	\
	$(ROOTLIB_DEVFSADM_LINK_MODS)

clean:
	$(RM) $(OBJS) 

lint:

include ../../Makefile.targ

SUNW_%.so: %.o $(MAPFILES)
	$(CC) -o $@ $(GSHARED) $(DYNFLAGS) -h $@ $< $(LDLIBS) -lc
	$(POST_PROCESS_SO)

%.o: $(COMMON)/%.c
	$(COMPILE.c) -o $@ $< $(CTFCONVERT_HOOK)
	$(POST_PROCESS_O)

$(ROOTLIB_DEVFSADM):
	$(INS.dir)

$(ROOTLIB_DEVFSADM_LINKMOD):
	$(INS.dir)

$(ROOTLIB_DEVFSADM_LINKMOD)/%: %
	$(INS.file)
