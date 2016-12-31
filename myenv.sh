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
# Copyright (c) 2005, 2010, Oracle and/or its affiliates. All rights reserved.
# Copyright 2012 Joshua M. Clulow <josh@sysmgr.org>
# Copyright 2013 Nexenta Systems, Inc. All rights reserved.
#

#	Configuration variables for the runtime environment of the
# "buildenv" script, and construction and packaging of releases.
# Note: gfx-drm does NOT contain cw tools etc, so turn OFF 't'
# See also: BUILD_TOOLS, ONBLD_TOOLS below.
export NIGHTLY_OPTIONS="-nrN +t"

# CODEMGR_WS - where is your workspace
export CODEMGR_WS=`git rev-parse --show-toplevel`

# Maximum number of dmake jobs.  Small WS -- keep it simple.
export DMAKE_MAX_JOBS=4

# where is the proto area etc.
export MACH="$(uname -p)"
export ROOT="$CODEMGR_WS/proto/root_${MACH}"
export SRC="$CODEMGR_WS/usr/src"
export MULTI_PROTO="no"

#
# Build environment variables, including version info for mcs, etc.
# We want the git changeset hash.  GATE, GIT_REV are just a locals.
GATE=`basename ${CODEMGR_WS}`
GIT_REV=`git rev-parse --short=10 HEAD`
export VERSION="${GATE}:${GIT_REV}"
export ONNV_BUILDNUM=152
export PKGVERS_BRANCH=2016.1

# export RELEASE='5.11'
# export RELEASE_DATE='October 2007'

# Package creation variables.
export PKGARCHIVE="${CODEMGR_WS}/packages/${MACH}/nightly"
# export PKGPUBLISHER_REDIST='on-redist'

# Package manifest format version.
export PKGFMT_OUTPUT='v1'

# Disable shadow compilation.
export CW_NO_SHADOW='1'

# Build tools - don't change these unless you know what you're doing.
export BUILD_TOOLS=/opt
export ONBLD_TOOLS=/opt/onbld

# see usr/src/pkg
# export PKGPUBLISHER=on-skel
