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
# Copyright 2012 Nexenta Systems, Inc.  All rights reserved.
#

# This is just for ctfmerge; copy from the build machine.

GUDIR=/kernel

LINKS= debug32/genunix debug64/genunix \
	obj32/genunix obj64/genunix

def: all
all: $(LINKS)

debug32/genunix:
	-rm -rf debug32
	mkdir debug32
	ln -s $(GUDIR)/genunix $@

debug64/genunix:
	-rm -rf debug64
	mkdir debug64
	ln -s $(GUDIR)/amd64/genunix $@

obj32/genunix:
	-rm -rf obj32
	mkdir obj32
	ln -s $(GUDIR)/genunix $@

obj64/genunix:
	-rm -rf obj64
	mkdir obj64
	ln -s $(GUDIR)/amd64/genunix $@

clean:	FRC
	-rm -f $(LINKS)

clobber: clean

lint:

modlintlib:

clean.lint:

install: all

FRC:
