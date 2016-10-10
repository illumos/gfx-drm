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
# include global definitions
include ../Makefile.master

#
# List of architectures to build as part of the standard build.
#
sparc_ARCHITECTURES = sparc # sun4v sun4u
i386_ARCHITECTURES  = intel # i86pc i86xpv

#
# Platforms defined in $(MACH)_PARALLEL are built in parallel. DUMMY is placed
# at the end in case $(MACH)_PARALLEL is empty to prevent everything going in
# parallel.
#
.PARALLEL: $($(MACH)_PARALLEL) DUMMY

#
# For build prerequisites we use a special target which is constructed by adding
# '.prereq' suffix to the $(MACH)_PREREQ.
#
PREREQ_TARGET =


def		:=	TARGET= def
all		:=	TARGET= all
install		:=	TARGET= install
install_h	:=	TARGET= install_h
clean		:=	TARGET= clean
clobber		:=	TARGET= clobber
clobber_h	:=	TARGET= clobber
lint		:=	TARGET= lint
clean.lint	:=	TARGET= clean.lint
check		:=	TARGET= check
modlist		:=	TARGET= modlist
modlist		:=	NO_STATE= -K $$MODSTATE$$$$

.KEEP_STATE:

def all lint: all_h $($(MACH)_ARCHITECTURES)

install: all_h install_dirs $($(MACH)_ARCHITECTURES)

install_dirs:
	@cd ..; pwd; $(MAKE) rootdirs
	@pwd

#
# Rule to build architecture files. Build all required prerequisites and then
# build the rest (potentially in parallel).
#
$($(MACH)_ARCHITECTURES): $(PREREQ_TARGET) FRC
	@cd $@; pwd; $(MAKE) $(NO_STATE) $(TARGET)

#
# The following is the list of directories which contain Makefiles with
# targets to install header file. The machine independent headers are
# installed by invoking the Makefile in the directory containing the
# header files. Machine and architecture dependent headers are installed
# by invoking the main makefile for that architecture/machine which,
# in turn, is responsible for invoking the Makefiles which install headers.
# It is done this way so as not to assume that all of the header files in
# the architecture/machine dependent subdirectories are in completely
# isomorphic locations.
#
COMMON_HDRDIRS= \
		common/drm \
		common/sys

#
# Subset of COMMON_HDRDIRS in which at least one header is generated
# at runtime (e.g., rpcgen).  (This is a partial list; there are
# other directories that should be included and do not yet have the
# necessary Makefile support.  See 6414855.)
#
DYNHDRDIRS = common/sys

sparc_HDRDIRS=
i386_HDRDIRS=

HDRDIRS= $(COMMON_HDRDIRS) $($(MACH)_HDRDIRS)
install_h check: $(HDRDIRS) $($(MACH)_ARCHITECTURES)

$(HDRDIRS): FRC
	@cd $@; pwd; $(MAKE) $(TARGET)

# ensures that headers made by rpcgen and others are available in uts source
# for kernel builds to reference without building install_h
#
all_h: FRC
	@cd common/sys; pwd; $(MAKE) $@

clean clobber: $($(MACH)_ARCHITECTURES) $(DYNHDRDIRS)

# testing convenience
clobber_h: $(DYNHDRDIRS)

EXTRA_CLOBBER_TARGETS=
clobber: $(EXTRA_CLOBBER_TARGETS)

clean.lint modlist: $($(MACH)_ARCHITECTURES)

cscope.out tags: FRC
	$(XREF) -x $@

FRC:
