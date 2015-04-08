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

MANSECT= 	3x

MANFILES= 	foo.3x

MANLINKS=	foo_getcnt.3x foo_message.3x libfoo.3x

foo_getcnt.3x 	:= LINKSRC = foo.3x
foo_message.3x	:= LINKSRC = foo.3x
libfoo.3x	:= LINKSRC = foo.3x

.KEEP_STATE:

include		$(SRC)/man/Makefile.man

install:	$(ROOTMANFILES) $(ROOTMANLINKS)
