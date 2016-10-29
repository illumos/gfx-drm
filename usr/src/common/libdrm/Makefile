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
# Copyright 2016 Gordon W. Ross
#

#
#	Include common rules.
#

include $(SRC)/Makefile.master

FETCH=	$(SRC)/tools/userland-fetch

LIBDRM_VERS=2.4.71
LIBDRM_DIR=libdrm-$(LIBDRM_VERS)
LIBDRM_ARCHIVE=$(LIBDRM_DIR).tar.bz2
LIBDRM_URL=http://dri.freedesktop.org/libdrm/$(LIBDRM_ARCHIVE)
LIBDRM_HASH=sha256:c66287ddeee5f46ea8f8880b94b80acb3bbc33ba6321d17767eef145046df9b8

def all install install_h: .patched check

# The "check" target will fail if any of the library headers don't
# match the kernel DRM headers.  That's intentional.  It's critical
# that these headers match or things will NOT work correctly.
#
# If these headers really need changes, you'll need to update the
# kernel headers, update the kernel driver code to do the right
# thing with those updates, and finally update the patches here
# to make the patched headers match the kernel again.  We could
# also just delete these lib copies of these headers, but then
# you would not notice changes when updating to a newer version
# of the libdrm code, and fail to make necessary updates.
#
KDRM_HDRS= drm.h drm_fourcc.h drm_mode.h drm_sarea.h i915_drm.h
check: FRC
	@echo "You should see: No differences ... (5x)"
	for f in $(KDRM_HDRS) ; do \
	  echo diff ... $$f ;\
	  diff -u $(LIBDRM_DIR)/include/drm/$$f $(SRC)/uts/common/drm/$$f ;\
	done

.patched: .unpacked
	(cd $(LIBDRM_DIR) && \
	for p in ../patches/*.patch ; do \
	patch -b -N -p 1 -i $$p ; done )
	touch $@

.unpacked: $(LIBDRM_ARCHIVE)
	tar xvfjo $(LIBDRM_ARCHIVE)
	touch $@

$(LIBDRM_ARCHIVE) :
	$(FETCH) -u $(LIBDRM_URL) -h $(LIBDRM_HASH)

clobber: clean
	$(RM) $(LIBDRM_ARCHIVE)

clean: FRC
	$(RM) -rf $(LIBDRM_DIR)
	$(RM) .unpacked .patched

lint:

FRC:
