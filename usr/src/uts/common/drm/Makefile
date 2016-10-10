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
# Copyright 2016 <contributor>
#


include ../../../Makefile.master

HDRS=	\
	drm.h		\
	drm_fourcc.h	\
	drm_mode.h	\
	drm_os_solaris.h \
	drm_sarea.h	\
	i915_drm.h


ROOTDIR= $(ROOT)/usr/include/drm
ROOTHDRS= $(HDRS:%=$(ROOTDIR)/%)
CHECKHDRS= $(HDRS:%.h=%.check)

$(ROOTDIR)/%: %
	$(INS.file)

$(ROOTDIR):
	$(INS.dir)

.KEEP_STATE:

.PARALLEL: $(CHECKHDRS)

install_h: $(ROOTDIR) $(ROOTHDRS)

check: $(CHECKHDRS)
