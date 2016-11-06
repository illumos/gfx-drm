/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */
/*
 * Copyright 2016 Gordon W. Ross
 */

/*
 * Tests for the OS-dependent functions over in:
 * libdevinfo/common/sun_devinfo.c
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <fnmatch.h>
#include <libdevinfo.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mkdev.h>

#include "xf86drm.h"

int main(int argc, char **argv)
{
	drmPciBusInfo pci_bus;
	drmPciDeviceInfo pci_dev;
	char *path;
	char *path2;
	int failures = 0;
	int min = 0;
	int maj;
	int fd, ret;

	if (argc > 1)
		min = atoi(argv[1]);

	maj = _sun_drm_get_major();
	printf("drm major: %d\n", maj);

	ret = _sun_drm_find_device(min, &path);
	if (ret) {
		printf("FAIL: _sun_drm_find_device(%d, &) -> %d\n", min, ret);
		failures++;
	} else {
		printf("Found device: %s\n", path);
	}

	ret = _sun_drmParseSubsystemType(maj, min);
	if (ret != DRM_BUS_PCI) {
		printf("FAIL: _sun_drmParseSubsystemType(%d, %d) -> %d\n",
		       maj, min, ret);
		failures++;
	}

	ret = _sun_drmParsePciBusInfo(maj, min, &pci_bus);
	if (ret) {
		printf("FAIL: _sun_drmParsePciBusInfo(%d, %d, &) -> %d\n",
		       maj, min, ret);
		failures++;
	} else {
		printf("PCI bus info: dom=%d bus=%d dev=%d func=%d\n",
		       pci_bus.domain,
		       pci_bus.bus,
		       pci_bus.dev,
		       pci_bus.func);
	}

	ret = _sun_drmParsePciDeviceInfo(path, &pci_dev);
	if (ret) {
		printf("FAIL: _sun_drmParsePciDeviceInfo(\"%s\", &) -> %d\n",
		       path, ret);
		failures++;
	} else {
		printf("PCI device info: ven=%x dev=%x "
		       "subven=%x subdev=%x rev=%x\n",
		       pci_dev.vendor_id,
		       pci_dev.device_id,
		       pci_dev.subvendor_id,
		       pci_dev.subdevice_id,
		       pci_dev.revision_id);
	}

	fd = open(path, O_RDWR);
	if (fd < 0) {
		ret = errno;
		printf("FAIL: open(%s) -> %d\n", path, ret);
		return (1);
	}

	path2 = _sun_drmGetMinorNameForFD(fd, 0);
	if (path2 == NULL) {
		ret = errno;
		printf("FAIL: open(%s) -> %d\n", path, ret);
		failures++;
	} else {
		printf("Path from fd: %s\n", path2);
		if (strcmp(path2, path) != 0) {
			printf("FAIL\n");
			failures++;
		}
	}

	close(fd);
	free(path2);
	free(path);

	return (failures ? 1 : 0);
}
