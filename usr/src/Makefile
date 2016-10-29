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
# Copyright (c) 1989, 2010, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2012 by Delphix. All rights reserved.
# Copyright 2014 Nexenta Systems, Inc.  All rights reserved.
#

#
# Makefile for system source
#
# include global definitions
include Makefile.master
#
# the Targetdirs file is the AT&T target.dirs file in a makefile format.
# it defines TARGETDIRS and ROOTDIRS.
include Targetdirs

COMMON_SUBDIRS=	uts lib cmd man #test
sparc_SUBDIRS=
i386_SUBDIRS=

SUBDIRS= $(COMMON_SUBDIRS) $($(MACH)_SUBDIRS)

HDRSUBDIRS=	uts head lib cmd

# UCB headers are bug-for-bug compatible and not checkable against the header
# standards.
#
CHKHDRSUBDIRS=	head uts lib

# The check target also causes smf(5) service manifests to be validated.
CHKMFSTSUBDIRS=	cmd

# And man page formats
CHKMANSUBDIRS = man

MSGSUBDIRS=	cmd lib
DOMAINS= \
	SUNW_OST_ADMIN \
	SUNW_OST_NETRPC \
	SUNW_OST_OSCMD \
	SUNW_OST_OSLIB \
	SUNW_OST_ZONEINFO

MSGDDIRS=       $(DOMAINS:%=$(MSGROOT)/%)
MSGDIRS=        $(MSGROOT) $(MSGDDIRS) $(MSGROOT)/LC_TIME

all :=			TARGET= all
install :=		TARGET= install
install1 :=		TARGET= install
install2 :=		TARGET= install
install_h :=		TARGET= install_h
clean :=		TARGET= clean
clobber :=		TARGET= clobber
check :=		TARGET= check

.KEEP_STATE:

#
# Note: install does not cause a build in pkg.  To build packages,
#	cd pkg and do a 'make install'
#

all: mapfiles sgs .WAIT $(SUBDIRS) pkg

#
# The _msg build is a two-step process.  First, the _msg dependency
# causes recursive makes in $(MSGSUBDIRS), which stages raw message
# files in $(ROOT)/catalog.  Second, the action from the install
# target rule causes those messages to be post-processed from where
# they were staged in $(ROOT)/catalog, and the results placed into the
# proto area.
#
# The stage-licenses target causes the license files needed for
# packaging to be pulled from $(SRC) and $(CLOSED) and staged in
# $(ROOT)/licenses.
#
install: install1 install2 _msg stage-licenses
#	@cd msg; pwd; $(MAKE) _msg
#	@rm -rf "$(ROOT)/catalog"

stage-licenses: install2
	@cd pkg; pwd; $(MAKE) stage-licenses

install1: mapfiles sgs

install2: install1 $(SUBDIRS)

_msg: _msgdirs rootdirs FRC
	@for m in $(MSGSUBDIRS); do \
		cd $$m; pwd; $(MAKE) _msg; cd ..; \
	done

mapfiles: bldtools
	@cd common/mapfiles/common; pwd; $(MAKE) install

clean: $(SUBDIRS) head pkg
clobber: $(SUBDIRS) head pkg clobber_local
clobber_local:
	@cd tools; pwd; $(MAKE) clobber
	@cd common/libdrm; pwd; $(MAKE) clobber
	@cd common/mapfiles/common; pwd; $(MAKE) clobber
#	@cd msg; pwd; $(MAKE) clobber

# no closedbins here

$(SUBDIRS) head pkg: FRC
	@cd $@; pwd; $(MAKE) $(TARGET)

# librpcsvc has a dependency on headers installed by
# userheaders, hence the .WAIT before libheaders.
sgs: rootdirs .WAIT sysheaders userheaders .WAIT \
	libheaders cmdheaders

#
# Top-level setup target to setup the development environment that includes
# headers, tools and generated mapfiles.
#
setup:  bldtools sgs mapfiles

bldtools:
	@cd tools; pwd; $(MAKE) install

#
rootdirs: $(ROOTDIRS)

lint: FRC
	$(MAKE) -f Makefile.lint

_msgdirs:       $(MSGDIRS)

$(ROOTDIRS) $(MSGDIRS):
	$(INS.dir)

userheaders: FRC
	@cd head; pwd; $(MAKE) install_h
	@cd common/libdrm; pwd; $(MAKE) install_h

libheaders: bldtools
	@cd lib; pwd; $(MAKE) install_h

sysheaders: FRC
	@cd uts; pwd; $(MAKE) install_h

cmdheaders: FRC
	@cd cmd; pwd; $(MAKE) install_h

check:	$(CHKHDRSUBDIRS) $(CHKMFSTSUBDIRS) $(CHKMANSUBDIRS)

#
# Cross-reference customization: skip all of the subdirectories that
# don't contain actual source code.
#
XRPRUNE = pkg prototypes
XRINCDIRS = uts/common head ucbhead

cscope.out tags: FRC
	$(XREF) -f -x $@

TAGS: FRC
	find uts common lib cmd -name '*.[ch]' -print |\
	exctags -e -L - 

FRC:

#
# Targets for reporting compiler versions; nightly uses these.
#

cc-version:
	@if $($(MACH)_CC) -_versions >/dev/null 2>/dev/null; then \
		$(ECHO) 32-bit compiler;			\
		$(ECHO) $($(MACH)_CC);				\
		$($(MACH)_CC) -_versions 2>&1 |			\
		    $(EGREP) '^(cw|cc|gcc|primary|shadow)';	\
	else							\
		__COMPILER=`$($(MACH)_CC) -_compiler 2>/dev/null || $(TRUE)`;\
		if [ -z "$$__COMPILER" ]; then			\
			$(ECHO) No 32-bit compiler found;	\
			exit 1;					\
		else						\
			$(ECHO) 32-bit compiler;		\
			$(ECHO) $($(MACH)_CC);			\
			$(ECHO) $$__COMPILER;			\
			$($(MACH)_CC) -V 2>&1 | head -1;	\
		fi;						\
	fi

cc64-version:
	@if $($(MACH64)_CC) -_versions >/dev/null 2>/dev/null; then \
		$(ECHO) 64-bit compiler;			\
		$(ECHO) $($(MACH64)_CC);			\
		$($(MACH64)_CC) -_versions 2>&1 |		\
		    $(EGREP) '^(cw|cc|gcc|primary|shadow)';	\
	else							\
		__COMPILER=`$($(MACH64)_CC) -_compiler 2>/dev/null || $(TRUE)`;\
		if [ -z "$$__COMPILER" ]; then			\
			$(ECHO) No 64-bit compiler found;	\
			exit 1;					\
		else						\
			$(ECHO) 64-bit compiler;		\
			$(ECHO) $($(MACH64)_CC);		\
			$(ECHO) $$__COMPILER;			\
			$($(MACH64)_CC) -V 2>&1 | head -1;	\
		fi;						\
	fi

java-version:
	@if [ -x "$(JAVAC)" ]; then			\
		$(ECHO) $(JAVAC);			\
		$(JAVA_ROOT)/bin/java -fullversion 2>&1 | head -1;	\
	else						\
		$(ECHO) No Java compiler found;		\
		exit 1;					\
	fi
