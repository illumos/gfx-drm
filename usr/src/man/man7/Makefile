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

MANSECT= 	7

# generated man pages
GENMANS= \
	drm.7 \
	drm-kms.7 \
	drm-memory.7

LINKSRC= drm-memory.7
GENLINKS= \
	drm-mm.7 \
	drm-gem.7 \
	drm-ttm.7

MANFILES= $(GENMANS)

MANLINKS=

.KEEP_STATE:

include		$(SRC)/man/Makefile.man
include		$(SRC)/common/libdrm/Makefile.drm

ROOTGENLINKS=	$(GENLINKS:%=$(ROOTMAN)/man$(MANSECT)/%)

install:	$(ROOTMANFILES) $(ROOTMANLINKS) $(ROOTGENLINKS)

$(ROOTMAN)/man7/%.7 : $(LIBDRM_CMN_DIR)/man/%.xml
	$(XSLTPROC_PROCESS_MAN)


$(ROOTGENLINKS):
		$(RM) $@; $(SYMLINK) $(LINKSRC) $@
