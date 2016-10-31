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
	exynos_fimg2d_test \
	exynos_fimg2d_perf \
	exynos_fimg2d_event

include	../../Makefile.drm

SRCDIR= $(LIBDRM_CMN_DIR)/tests/exynos

CPPFLAGS +=	-I$(SRCDIR)
CPPFLAGS +=	-I$(LIBDRM_CMN_DIR)/exynos
CPPFLAGS +=	-I$(LIBDRM_CMN_DIR)/libkms

LDLIBS	 +=	-lkms -ldrm -ldrm_exynos -lm

LDLIBS32 +=	-L$(ROOT)/usr/lib/xorg \
		-R/usr/lib/xorg
LDLIBS64 +=	-L$(ROOT)/usr/lib/xorg/$(MACH64) \
		-R/usr/lib/xorg/$(MACH64)

all:	 $(PROG)

#This is in the lower Makefile
#install:	$(ROOTCMD)

lint:

clean:     
	$(RM) $(PROG:%=%.o)

% : $(SRCDIR)/%.c
	$(COMPILE.c) -o $@.o $<
	$(LINK.c) -o $@ $@.o $(LDLIBS)

.KEEP_STATE:

include	../../../Makefile.targ
