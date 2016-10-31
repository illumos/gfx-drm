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

LIBRARY=	libutil.a

OBJECTS= format.o kms.o pattern.o

UTIL_FILES = \
	common.h \
	format.c \
	format.h \
	kms.c \
	kms.h \
	pattern.c \
	pattern.h

include $(SRC)/lib/Makefile.lib
include $(SRC)/common/libdrm/Makefile.drm

LIBS =		$(LIBRARY)

SRCDIR =	$(LIBDRM_CMN_DIR)/tests/util
SRCS =		$(OBJECTS:%.o=$(SRCDIR)/%.c)

CPPFLAGS +=	-DHAVE_CAIRO
CPPFLAGS +=	-I/usr/include/cairo
all : $(LIBS) $(PCS)

lint :

include $(SRC)/lib/Makefile.targ

.KEEP_STATE:

