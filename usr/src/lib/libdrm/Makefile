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
# Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# Copyright 2011 Nexenta Systems, Inc.  All rights reserved.
#

# include library definitions
include ../Makefile.lib

include $(SRC)/common/libdrm/Makefile.drm

SUBDIRS = $(MACH)
$(BUILD64)SUBDIRS += $(MACH64)

all :=		TARGET= all
clean :=	TARGET= clean
clobber :=	TARGET= clobber
install :=	TARGET= install
lint :=		TARGET= lint

HDRS= \
	libsync.h \
	xf86drm.h \
	xf86drmMode.h

# Note -- these headers come from uts/common/drm:
#   drm.h drm_fourcc.h drm_mode.h drm_sarea.h i915_drm.h
# See KDRM_HDRS in $src/common/libdrm/Makefile

DRM_HDRS= \
	amdgpu_drm.h \
	mach64_drm.h \
	mga_drm.h \
	nouveau_drm.h \
	qxl_drm.h \
	r128_drm.h \
	radeon_drm.h \
	savage_drm.h \
	sis_drm.h \
	tegra_drm.h \
	vc4_drm.h \
	via_drm.h \
	vmwgfx_drm.h

ROOT_DRM_HDRS=	$(DRM_HDRS:%=$(ROOTHDRDIR)/drm/%)

.KEEP_STATE:

install: all .WAIT $(SUBDIRS)

all clean clobber lint: $(SUBDIRS)

install_h: $(ROOTHDRS) $(ROOT_DRM_HDRS) $(ROOTHDRDIR)/libdrm

# need to mkdir...
$(ROOT_DRM_HDRS) : $(ROOTHDRDIR)/drm
$(ROOTHDRDIR)/drm :
	$(INS.dir) $@

$(ROOTHDRDIR)/libdrm: FRC
	$(RM) -r $@; $(LN) -s drm $@

check:	$(CHECKHDRS)

_msg: # no msgfiles here

$(POFILE):      pofile_MSGFILES

# install rules for install_h target
$(ROOTHDRDIR)/drm/%: $(LIBDRM_CMN_DIR)/include/drm/%
	$(INS.file)

# HDRS=...
$(ROOTHDRDIR)/%: $(LIBDRM_CMN_DIR)/%
	$(INS.file)

$(SUBDIRS): FRC
	@cd $@; pwd; $(MAKE) $(TARGET)

FRC:

include ../Makefile.targ
