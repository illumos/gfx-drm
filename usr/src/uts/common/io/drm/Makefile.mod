#
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#
###############################################################################
#
#  This Makefile.mod defines DRM_OBJS
#
###############################################################################

DRM_OBJS = ati_pcigart.o \
	drm_agpsupport.o \
	drm_auth.o \
	drm_bufs.o \
	drm_cache.o \
	drm_context.o \
	drm_crtc.o \
	drm_crtc_helper.o \
	drm_dma.o \
	drm_dp_helper.o \
	drm_dp_i2c_helper.o \
	drm_drv.o \
	drm_edid.o \
	drm_fb_helper.o \
	drm_fops.o \
	drm_gem.o \
	drm_io32.o \
	drm_ioctl.o \
	drm_irq.o \
	drm_kstat.o \
	drm_linux.o \
	drm_lock.o \
	drm_memory.o \
	drm_mm.o \
	drm_modes.o \
	drm_msg.o \
	drm_pci.o \
	drm_rect.o \
	drm_scatter.o \
	drm_stub.o \
	drm_sun_i2c.o \
	drm_sun_idr.o \
	drm_sun_pci.o \
	drm_sun_timer.o \
	drm_sun_workqueue.o \
	drm_sunmod.o \
	drm_sysfs.o
