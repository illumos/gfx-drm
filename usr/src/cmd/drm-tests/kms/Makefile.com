#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Gordon W. Ross
#

# from bin_PROGRAMS
PROG= \
	kms-steal-crtc \
	kms-universal-planes

# from libkms_test_la_SOURCES
TEST_OBJS= \
	libkms-test-crtc.o \
	libkms-test-device.o \
	libkms-test-framebuffer.o \
	libkms-test-plane.o \
	libkms-test-screen.o

include	../../Makefile.drm

SRCDIR= $(LIBDRM_CMN_DIR)/tests/kms

LDLIBS	 +=	-ldrm -lm -lcairo

LDLIBS32 +=	$(LIBUTIL32) \
		-L$(ROOT)/usr/lib/xorg \
		-R/usr/lib/xorg
LDLIBS64 +=	$(LIBUTIL64) \
		-L$(ROOT)/usr/lib/xorg/$(MACH64) \
		-R/usr/lib/xorg/$(MACH64)

all:	 $(PROG)

#This is in the lower Makefile
#install:	$(ROOTCMD)

lint:

clean:     
	$(RM) $(PROG:%=%.o) $(TEST_OBJS)

kms-steal-crtc: kms-steal-crtc.o $(TEST_OBJS)
	$(LINK.c) -o $@ kms-steal-crtc.o \
		$(TEST_OBJS) $(LDLIBS)

kms-universal-planes: kms-universal-planes.o $(TEST_OBJS)
	$(LINK.c) -o $@ kms-universal-planes.o \
		$(TEST_OBJS) $(LDLIBS)

%.o : $(SRCDIR)/%.c
	$(COMPILE.c) -o $@ -c $<

.KEEP_STATE:

include	../../../Makefile.targ
