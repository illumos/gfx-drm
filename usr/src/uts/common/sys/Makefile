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
#
# Copyright (c) 1989, 2010, Oracle and/or its affiliates. All rights reserved.
# Copyright 2011 Nexenta Systems, Inc.  All rights reserved.
#

include $(SRC)/uts/Makefile.uts

FILEMODE=644

#
#	Note that the following headers are present in the kernel but
#	neither installed or shipped as part of the product:
#		cpuid_drv.h:		Private interface for cpuid consumers
#		unix_bb_info.h:		Private interface to kcov
#

i386_HDRS=			\
	agp/agpamd64gart_io.h	\
	agp/agpdefs.h		\
	agp/agpgart_impl.h	\
	agp/agpmaster_io.h	\
	agp/agptarget_io.h	\
	agpgart.h		\
	gfx_private.h

sparc_HDRS=

# Generated headers
GENHDRS=

# Normal headers
CHKHDRS= \
	foo.h

HDRS=	$(GENHDRS) $(CHKHDRS)

# from Makefile.syshdrs
ROOTDIR=	$(ROOT)/usr/include/sys
sparc_ROOTDIRS=
i386_ROOTDIRS=	$(ROOTDIR)/agp
sparc_ROOTHDRS=
i386_ROOTHDRS=

ROOTDIRS=			\
	$(ROOTDIR)		\
	$($(MACH)_ROOTDIRS)

ROOTHDRS=				\
	$($(MACH)_HDRS:%=$(ROOTDIR)/%)	\
	$(HDRS:%=$(ROOTDIR)/%)

agp/%.check:	agp/%.h
	$(DOT_H_CHECK)

$(ROOTDIR)/%: %
	$(INS.file)

$(ROOTDIR)/agp/%:		agp/%
	$(INS.file)

$(ROOTDIRS):
	$(INS.dir)

#end Makefile.syshdrs

CHECKHDRS= \
	$($(MACH)_HDRS:%.h=%.check) \
	$(CHKHDRS:%.h=%.check)

all_h: $(GENHDRS)

install_h:			\
	$(ROOTDIRS)		\
	.WAIT			\
	$(ROOTHDRS)		\
	$($(MACH)_ROOTHDRS)

clean:
	$(RM) $(GENHDRS)

clobber:	clean

check:	$(CHECKHDRS)

FRC:
