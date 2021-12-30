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

# Copyright (c) 1989, 2010, Oracle and/or its affiliates. All rights reserved.
# Copyright 2011 Nexenta Systems, Inc.  All rights reserved.

include ../Makefile.master

#	Note that libcurses installs commands along with its library.
#	This is a minor bug which probably should be fixed.
#	Note also that a few extra libraries are kept in cmd source.
#
# Certain libraries are linked with, hence depend on, other libraries.
#
# Although we have historically used .WAIT to express dependencies, it
# reduces the amount of parallelism and thus lengthens the time it
# takes to build the libraries.  Thus, we now require that any new
# libraries explicitly call out their dependencies.  Eventually, all
# the library dependencies will be called out explicitly.  See
# "Library interdependencies" near the end of this file.
#
# Aside from explicit dependencies (and legacy .WAITs), all libraries
# are built in parallel.
#
.PARALLEL:

#
#
SUBDIRS= \
	$($(MACH)_SUBDIRS)

i386_SUBDIRS= \
	libdrm .WAIT \
	libkms \
	libdrm_intel \
	libdrm_amdgpu \
	libdrm_exynos \
	libdrm_etnaviv \
	libdrm_freedreno \
	libdrm_omap \
	libdrm_radeon \
	libdrm_tegra \
	libdrm_nouveau

sparc_SUBDIRS=


#
# Create a special version of $(SUBDIRS) with no .WAIT's, for use with the
# clean and clobber targets (for more information, see those targets, below).
#
NOWAIT_SUBDIRS= $(SUBDIRS:.WAIT=)

DCSUBDIRS =


MSGSUBDIRS=	\
	$($(MACH)_MSGSUBDIRS)

sparc_MSGSUBDIRS=

i386_MSGSUBDIRS=

all :=		TARGET= all
check :=	TARGET= check
clean :=	TARGET= clean
clobber :=	TARGET= clobber
install :=	TARGET= install
install_h :=	TARGET= install_h
lint :=		TARGET= lint
_dc :=		TARGET= _dc
_msg :=		TARGET= _msg

.KEEP_STATE:


all:			$(SUBDIRS)

install:		$(SUBDIRS)

clean clobber lint:	$(NOWAIT_SUBDIRS)

install_h check:	$(SUBDIRS)

_msg:			$(MSGSUBDIRS) .WAIT _dc

_dc:			$(DCSUBDIRS)

#
# Library interdependencies are called out explicitly here
#
libbe: 		libzfs

#
# The reason this rule checks for the existence of the
# Makefile is that some of the directories do not exist
# in certain situations (e.g., exportable source builds,
# OpenSolaris).
#
$(SUBDIRS): FRC
	@if [ -f $@/Makefile  ]; then \
		cd $@; pwd; $(MAKE) $(TARGET); \
	else \
		true; \
	fi

FRC:
