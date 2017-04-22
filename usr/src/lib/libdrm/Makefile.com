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
# Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# Copyright 2011 Nexenta Systems, Inc.  All rights reserved.
#

LIBRARY=	libdrm.a
VERS=		.2

# See common/libdrm/libdrm-*/Makefile.in am__objects
OBJECTS=	xf86drm.o xf86drmHash.o \
	xf86drmRandom.o xf86drmSL.o xf86drmMode.o \
	sun_devinfo.o

include ../../Makefile.lib
include $(SRC)/common/libdrm/Makefile.drm

LIBS =		$(DYNLIB)
PCS =		$(LIBRARY:.a=.pc)

MAPFILES=
SRCDIR =	$(LIBDRM_CMN_DIR)
SRCS =		$(OBJECTS:%.o=$(SRCDIR)/%.c)

CPPFLAGS +=	-I$(LIBDRM_CMN_DIR)

# CFLAGS +=	$(CCVERBOSE)
LDLIBS += -lm -ldevinfo -lc

all : $(LIBS) $(PCS)

lint :

include ../Makefile.pc
include ../../Makefile.targ

objs/%.o pics/%.o: ../common/%.c
	$(COMPILE.c) -o $@ $<
	$(POST_PROCESS_O)

.KEEP_STATE:
