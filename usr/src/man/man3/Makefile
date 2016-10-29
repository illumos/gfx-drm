#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet
# at http://www.illumos.org/license/CDDL.
#

#
# Copyright 2011, Richard Lowe
#

include		$(SRC)/Makefile.master

MANSECT= 	3

# generated man pages
GENMAN= \
		drmAvailable.3 \
		drmHandleEvent.3 \
		drmModeGetResources.3

MANFILES= $(GENMAN)
MANLINKS=

.KEEP_STATE:

include		$(SRC)/man/Makefile.man
include		$(SRC)/common/libdrm/Makefile.drm

install:	$(ROOTMANFILES) $(ROOTMANLINKS)

$(ROOTMAN)/man3/%.3 : $(LIBDRM_CMN_DIR)/man/%.xml
	$(XSLTPROC_PROCESS_MAN)
