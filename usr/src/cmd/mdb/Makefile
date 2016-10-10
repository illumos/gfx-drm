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
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

include $(SRC)/Makefile.master

.KEEP_STATE:

sparc_SUBDIRS =
i386_SUBDIRS = \
	foo \
	i915

SUBDIRS = $($(MACH)_SUBDIRS)
TARGET =

all := TARGET = all
clean.lint := TARGET = clean.lint
clean := TARGET = clean
clobber := TARGET = clobber
dmods := TARGET = dmods
install := TARGET = install
install_h := TARGET = install_h
lint := TARGET = lint

all lint: $(SUBDIRS)

dmods install: $(SUBDIRS)

install_h:

clean.lint clean: $(SUBDIRS)

clobber: $(SUBDIRS)

$(SUBDIRS): FRC
	@cd $@; pwd; $(MAKE) $(TARGET)

FRC:
