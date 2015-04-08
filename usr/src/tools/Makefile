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
# Copyright 2015 Nexenta Systems, Inc.  All rights reserved.
#

#
# Don't want to copy the tools into this skeleton,
# so just make a link to /opt/onbld
#

include ../Makefile.master

all install:  proto/root_$(MACH)-nd/opt

proto/root_$(MACH)-nd/opt :
	-/usr/bin/mkdir -p proto/root_$(MACH)-nd
	/usr/bin/rm -f $@
	/usr/bin/ln -s /opt $@

clobber:
	/usr/bin/rm -rf proto

clean:
