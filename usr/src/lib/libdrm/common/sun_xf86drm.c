/**
 * \file xf86drm.c 
 * User-level interface to DRM device
 *
 * \author Rickard E. (Rik) Faith <faith@valinux.com>
 * \author Kevin E. Martin <martin@valinux.com>
 */

/*
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * OS-dependent versions of several functions found in:
 * libdrm/xf86drm.c (mostly where those need "udev")
 * Here we use libdevinfo.h instead via these
 * private interfaces in libdrm:
 *	_sun_drm_find_device()
 *	_sun_drm_get_pci_info()
 *
 * See sun_devinfo.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mkdev.h>

#include "xf86drm.h"

/* Device majors are dynamic. */
#define DRM_MAJOR	(_sun_drm_get_major())

char *_sun_drmGetMinorNameForFD(int fd, int type)
{
	char *path = NULL;
	struct stat sbuf;
	int err, maj, min;

	if (fstat(fd, &sbuf))
		return NULL;

	maj = major(sbuf.st_rdev);
	min = minor(sbuf.st_rdev);

	if (maj != DRM_MAJOR || !S_ISCHR(sbuf.st_mode))
		return NULL;

	/* Walk devices looking for this minor */
	err = _sun_drm_find_device(min, &path);
	if (err != 0)
		return (NULL);

	return (path);
}

int _sun_drmParseSubsystemType(int maj, int min)
{
	char *path = NULL;
	char *p;
	int ret;

	if (maj != DRM_MAJOR)
		return -EINVAL;

	ret = _sun_drm_find_device(min, &path);
	if (ret != 0)
		return (ret);

	p = path;
	if (strncmp(p, "/devices", 8) == 0)
		p += 8;

	if (strncmp(p, "/pci@", 5) == 0)
		ret = DRM_BUS_PCI;
	else
		ret = -EINVAL;
	free(path);

	return (ret);
}

int _sun_drmParsePciBusInfo(int maj, int min, drmPciBusInfoPtr info)
{
	char *path = NULL;
	int bus, slot, unit;
	int n, ret;

	if (maj != DRM_MAJOR)
		return -EINVAL;

	ret = _sun_drm_find_device(min, &path);
	if (ret != 0)
		return (ret);

	n = sscanf(path, "/devices/pci@%d,%d/display@%d:",
		   &bus, &slot, &unit);
	free(path);
	if (n != 3)
		return -EINVAL;

	info->domain = 0;
	info->bus = bus;
	info->dev = slot;
	info->func = unit;

	return 0;
}

/*
 * Given d_name as some name under /dev,
 * find the /devices path and then get the
 * PCI properties for that device.
 */
int _sun_drmParsePciDeviceInfo(const char *d_name,
			       drmPciDeviceInfo *pcii)
{
	struct stat sbuf;
	int err, maj, min;
	char dev_path[256];
	char *path = NULL;

	if (d_name[0] == '/')
		strlcpy(dev_path, d_name, sizeof (dev_path));
	else
		snprintf(dev_path, sizeof (dev_path),
			 DRM_DIR_NAME "/%s", d_name);
	if (stat(dev_path, &sbuf))
		return -errno;

	maj = major(sbuf.st_rdev);
	min = minor(sbuf.st_rdev);
	if (maj != DRM_MAJOR || !S_ISCHR(sbuf.st_mode))
		return -EINVAL;

	/* Get the /devices path */
	err = _sun_drm_find_device(min, &path);
	if (err != 0)
		return err;

	err = _sun_drm_get_pci_info(path, pcii);
	free(path);

	return err;
}

/*
 * XXX: todo - int drmCheckModesettingSupported()
 */
