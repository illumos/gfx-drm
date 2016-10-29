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

LIBRARY=	libdrm_freedreno.a
VERS=		.1

# See common/libdrm/libdrm-*/freedreno/Makefile.in am__objects
OBJS_TOP= \
	freedreno_device.o freedreno_pipe.o \
	freedreno_ringbuffer.o freedreno_bo.o freedreno_bo_cache.o

OBJS_MSM= \
	msm_bo.o \
	msm_device.o msm_pipe.o msm_ringbuffer.o

OBJS_KGSL= \
	kgsl_bo.o kgsl_device.o kgsl_pipe.o \
	kgsl_ringbuffer.o

OBJECTS= $(OBJS_TOP) $(OBJS_MSM) $(OBJS_KGSL)

include ../../Makefile.lib
include $(SRC)/common/libdrm/Makefile.drm

LIBS =		$(DYNLIB)
PCS =		$(LIBRARY:.a=.pc)

MAPFILES=
SRCDIR =	$(LIBDRM_CMN_DIR)/freedreno

CPPFLAGS +=	-DHAVE_FREEDRENO_KGSL

CPPFLAGS +=	-I$(LIBDRM_CMN_DIR)/freedreno
CPPFLAGS +=	-I$(LIBDRM_CMN_DIR)
CPPFLAGS +=	-I/usr/include/pixman-1

LDLIBS32 +=	-L$(ROOT)/usr/lib/xorg
LDLIBS64 +=	-L$(ROOT)/usr/lib/xorg/$(MACH64)

LDLIBS += -lpciaccess -ldrm -lc

all : $(LIBS) $(PCS)

lint :

include ../../libdrm/Makefile.pc
include ../../Makefile.targ

objs/%.o pics/%.o: $(SRCDIR)/msm/%.c
	$(COMPILE.c) -o $@ $<
	$(POST_PROCESS_O)

objs/%.o pics/%.o: $(SRCDIR)/kgsl/%.c
	$(COMPILE.c) -o $@ $<
	$(POST_PROCESS_O)

.KEEP_STATE:
