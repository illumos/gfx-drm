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
# Copyright 2016 Gordon Ross <gordon.w.ross@gmail.com>
#

#
# This Makefile is intentionally very simple, and should work with
# any make implementation (BSD, GNU, Sun).  Just a convenience for
# people unfamiliar with illumos-gate (ON) builds (bldenv etc).
# Customizations happen via the myenv.sh file.
#
ONBLD_TOOLS=/opt/onbld

# Do both debug and non-debug build in uts, in that order, so
# (a) we know the debug code builds, and (b) install non-debug.
install: FRC
	$(ONBLD_TOOLS)/bin/bldenv -d myenv.sh \
	"cd usr/src/uts ; make install"
	$(ONBLD_TOOLS)/bin/bldenv myenv.sh \
	"cd usr/src ; make install"

debug: FRC
	$(ONBLD_TOOLS)/bin/bldenv -d myenv.sh \
	"cd usr/src ; make install"

clean: FRC
	$(ONBLD_TOOLS)/bin/bldenv myenv.sh \
	"cd usr/src ; make clobber"

package: FRC
	$(ONBLD_TOOLS)/bin/bldenv myenv.sh \
	"cd usr/src/pkg ; make install"

FRC:
