/*
 * Copyright © 2007 Intel Corporation
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *
 */

/*
 * Copyright 2016 Gordon W. Ross
 */

/*
 * Helper functions for libdrm/tests.  See:
 * drm_open_any()
 *	getclient.c
 *	getstats.c
 *	getversion.c
 *	openclose.c
 * drm_open_any_master()
 *	setversion.c
 *	updatedraw.c
 *
 * This module replaces libdrm/tests/drmtest.c
 * which needs the linux "udev" interfaces.
 * Here we use libdevinfo.h instead via these
 * private interfaces in libdrm:
 *	_sun_drm_find_device()
 *	_sun_drm_get_pci_info()
 */

#include <string.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "drmtest.h"

#include <libdevinfo.h>

static int is_master(int fd)
{
	drm_client_t client;
	int ret;

	/* Check that we're the only opener and authed. */
	client.idx = 0;
	ret = ioctl(fd, DRM_IOCTL_GET_CLIENT, &client);
	assert (ret == 0);
	if (!client.auth)
		return 0;
	client.idx = 1;
	ret = ioctl(fd, DRM_IOCTL_GET_CLIENT, &client);
	if (ret != -1 || errno != EINVAL)
		return 0;

	return 1;
}

/*
 * Open the first DRM device matching the criteria
 */
int drm_open_matching(const char *pci_glob, int flags)
{
	char *path = NULL;
	int i, ret;
	int fd = -1;

	/*
	 * If our glob patter matches all, let's skip
	 * getting the PCI info etc.
	 */
	if (strcmp(pci_glob, "*:*") == 0)
		pci_glob = NULL;

	/* Could also start at the offset for some device type. */
	for (i = 0; i < DRM_MAX_MINOR; i++) {
		free(path);
		ret = _sun_drm_find_device(i, &path);
		if (ret != 0)
			continue;

		if (pci_glob != NULL) {
			drmPciDeviceInfo pcii;
			char pci_str[32];
			ret = _sun_drm_get_pci_info(path, &pcii);
			if (ret != 0)
				continue;
			snprintf(pci_str, sizeof (pci_str),
			    "%x:%x", pcii.vendor_id, pcii.device_id);
			if (fnmatch(pci_glob, pci_str, 0) != 0)
				continue;
		}

		fd = open(path, O_RDWR);
		if (fd < 0)
			continue;

		if ((flags & DRM_TEST_MASTER) && !is_master(fd)) {
			close(fd);
			fd = -1;
			continue;
		}

		break;
	}

	free(path);

	return fd;
}

int drm_open_any(void)
{
	int fd = drm_open_matching("*:*", 0);

	if (fd < 0) {
		fprintf(stderr, "failed to open any drm device\n");
		exit(0);
	}

	return fd;
}

/**
 * Open the first DRM device we can find where we end up being the master.
 */
int drm_open_any_master(void)
{
	int fd = drm_open_matching("*:*", DRM_TEST_MASTER);

	if (fd < 0) {
		fprintf(stderr, "failed to open any drm device\n");
		exit(0);
	}

	return fd;

}
