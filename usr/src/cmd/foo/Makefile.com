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
# Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# Copyright 2011 Nexenta Systems, Inc.  All rights reserved.
#
# cmd/ls/Makefile.com
#

PROG=		foo
OBJS=           $(PROG).o
SRCS=           $(OBJS:%.o=../%.c)

include ../../Makefile.cmd

LDLIBS += -lfoo
CFLAGS	+=	$(CCVERBOSE)

CFLAGS64 +=	$(CCVERBOSE)
CPPFLAGS += -D_FILE_OFFSET_BITS=64

CLOBBERFILES += $(PROG)

all:	$(PROG)

lint:	lint_SRCS

clean:
	$(RM) *.o

include ../../Makefile.targ

%: ../%.c
	$(LINK.c) -o $@ $< $(LDLIBS)
	$(POST_PROCESS)

.KEEP_STATE:
