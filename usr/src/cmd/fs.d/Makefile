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
# Copyright (c) 1990, 2010, Oracle and/or its affiliates. All rights reserved.
#


include ../Makefile.cmd

SUBDIR1=
SUBDIR2=
SUBDIRS= $(SUBDIR1) $(SUBDIR2)
I18NDIRS= $(SUBDIR2)

all:=		TARGET= all
install:=	TARGET= install
clean:=		TARGET= clean
clobber:=	TARGET= clobber
lint:=		TARGET= lint
_msg:=          TARGET= catalog

FSLIB=		fslib.o
CLOBBERFILES += $(FSLIB)

# for messaging catalog
#
POFILE= fs.d.po

POFILES2= $(I18NDIRS:%=%/%.po)

POFILES=  $(POFILES1) $(POFILES2)

.KEEP_STATE:

# This is too intense when building the whole world.
# .PARALLEL:	$(SUBDIRS)

all:		$(FSLIB) .WAIT $(SUBDIRS)

_msg: $(I18NDIRS) $(POFILES1) $(POFILES_XPG4)
	$(RM) $(POFILE)
	cat $(POFILES) > $(POFILE)
	$(RM) $(MSGDOMAIN)/$(POFILE)
	cp $(POFILE) $(MSGDOMAIN)

install: $(FSLIB) .WAIT $(SUBDIRS)

clean: $(SUBDIRS)

clobber: $(SUBDIRS)
	$(RM) $(CLOBBERFILES)

lint:

$(SUBDIRS): FRC
	@cd $@; pwd; $(MAKE) $(MFLAGS) $(TARGET)

FRC:
