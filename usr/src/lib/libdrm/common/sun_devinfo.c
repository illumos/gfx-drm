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
 * Helper functions for sun_xf86drm.c to find DRM device nodes
 * given a pair of device major/minor numbers.
 *
 * Some of this code was cribbed from the "prtconf" command.
 */

/*
 * Device major numbers on illumos and Solaris are dynamic.
 *
 * Device node naming is also different.  See:
 *	uts/common/io/drm/drm_stub.c drm_get_minor()
 *	uts/common/io/drm/drm_sysfs.c drm_sysfs_device_add()
 *
 * Device "types" (encoded in some of the minor bits)
 * Typical device setup with intel graphics:
 *
 * DRM_MINOR_LEGACY	/devices/pci@0,0/display@2:drm0
 * DRM_MINOR_CONTROL	/devices/pci@0,0/display@2:controlD0
 * DRM_MINOR_RENDER	/devices/pci@0,0/display@2:renderD0
 * DRM_MINOR_VGATEXT	/devices/pci@0,0/display@2:gfx0
 * DRM_MINOR_AGPMASTER	/devices/pci@0,0/display@2:agpmaster0
 *
 * The "devlinks" system also makes links under /dev
 * which normally look something like this:
 *
 *	/dev/fbs/gfx0	-> .../display@2:gfx0
 *	/dev/fb		-> .../display@2:gfx0
 *	/dev/fb0	-> fbs/text-0
 *	/dev/fb1 	-> fbs/gfx0
 *	/dev/agp/agpmaster0 -> .../display@2:agpmaster0
 *	/dev/dri/card1	-> .../display@2:controlD0
 *
 * (i916 driver)	/devices/pci@0,0/pci1179,1@0:agptarget
 *	/dev/agp/agptarget0 -> /devices/pci@0,0/pci1179,1@0:agptarget
 *
 * (agpgart driver)	/devices/agpgart:agpgart
 *	/dev/agpgart -> /devices/agpgart:agpgart
 */

#include <string.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <libdevinfo.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mkdev.h>

#include "xf86drm.h"

struct search_args {
	char *s_path;
	int s_minor;
};

static int find_dev(di_node_t, void *);
static int find_minor(di_node_t, di_minor_t, struct search_args *);

static int _sun_drm_major; /* cache */

int _sun_drm_get_major(void)
{
	struct stat sbuf;
	dev_t dev = 0;
	char *path;
	int i, ret;

	if (_sun_drm_major != 0)
		return (_sun_drm_major);

	for (i = 0; i < DRM_MAX_MINOR; i++) {
		ret = _sun_drm_find_device(i, &path);
		if (ret != 0)
			continue;
		ret = stat(path, &sbuf);
		free(path);
		if (ret != 0)
			continue;
		if (!S_ISCHR(sbuf.st_mode))
			continue;
		dev = major(sbuf.st_rdev);
		if (dev != 0) {
			_sun_drm_major = dev;
			return (dev);
		}
	}

	/*
	 * No devices found?  No way to return errors here,
	 * so just return an impossible value, and let
	 * later calls like open fail.
	 */
	return (MAXMAJ32);
}

int
_sun_drm_find_device(int min, char **pathp)
{
	struct search_args sargs;
	di_node_t root_node;

	root_node = di_init("/", DINFOCPYALL);
	if (root_node == DI_NODE_NIL)
		return (-errno);

	memset(&sargs, 0, sizeof (sargs));

	di_walk_node(root_node, DI_WALK_CLDFIRST, &sargs, find_dev);
	di_fini(root_node);

	if (sargs.s_path == NULL)
		return (-ENOENT);

	if (pathp != NULL)
		*pathp = sargs.s_path;
	else
		free(sargs.s_path);

	return (0);
}

/*
 * Call back function for di_walk_node, called for every device node.
 */
static int
find_dev(di_node_t node, void *vargs)
{
	struct search_args *sargs = vargs;
	const char *node_name;
	di_minor_t minor_node;

	node_name = di_node_name(node);

	if (strcmp(node_name, "pseudo") == 0)
		return (DI_WALK_PRUNECHILD);

	/*
	 * Had: udev_enumerate_add_match_subsystem(e, "drm");
	 * so skip anything outside "drm".
	 * For illumos or Solaris, I think we want to skip
	 * anything that's not named "display".
	 */
	if (strcmp(node_name, "display") != 0)
		return (DI_WALK_CONTINUE);

	/*
	 * Walk the minor node paths searching...
	 */
	minor_node = DI_MINOR_NIL;
	while ((minor_node = di_minor_next(node, minor_node)) != DI_MINOR_NIL) {
		if (find_minor(node, minor_node, sargs)) {
			/* Found it! */
			return (DI_WALK_TERMINATE);
		}
	}

	return (DI_WALK_CONTINUE);
}

/*
 * Search function called for each minor node under some device
 * that was found to be of likely interest above.
 * Return non-zero if match found.
 */
static int
find_minor(di_node_t node, di_minor_t minor, struct search_args *sargs)
{
	char	*path;
	dev_t	devt;
	int	ret;

	devt = di_minor_devt(minor);

	/* Does the caller want a specific minor number? */
	if (sargs->s_minor >= 0 &&
	    sargs->s_minor != minor(devt))
		return (0);

	/*
	 * get device minor node path
	 * Note: allocates path
	 */
	if ((path = di_devfs_minor_path(minor)) == NULL)
		return (0);
	ret = asprintf(&sargs->s_path, "/devices%s", path);
	di_devfs_path_free(path);

	if (ret < 0) {
		free(sargs->s_path);
		return (0);
	}

	return (1);
}

/*
 * Get PCI data for the give device path.
 *
 * Note path given is a full minor under /devices i.e.
 *	/devices/pci@0,0/display@2:drm
 * and libdevinfo wants just:
 *	/pci@0,0/display@2
 */
int
_sun_drm_get_pci_info(char *path, drmPciDeviceInfo *pcii)
{
	char pathbuf[MAXPATHLEN];
	di_node_t node;
	char *s;
	char *propstr = NULL;
	int *propval = NULL;
	int ret = -EINVAL;

	/* Skip the /devices prefix, if present. */
	if (strncmp(path, "/devices/", 9) == 0)
		path += 8; /* the next slash */
	strlcpy(pathbuf, path, sizeof (pathbuf));

	/* Strip :drm0 or whatever */
	if ((s = strrchr(pathbuf, ':')) != NULL)
		*s = '\0';

	/*
	 * Ask libdevinfo about this device
	 */
	node = di_init(pathbuf, DINFOCPYALL);
	if (node == DI_NODE_NIL)
		return -EINVAL;

	/*
	 * Get the various PCI properties.
	 * Only the first two are required.
	 */
	memset(pcii, 0, sizeof(*pcii));
	if (di_prop_lookup_ints(DDI_DEV_T_ANY, node,
				"vendor-id", &propval) > 0)
		pcii->vendor_id = (uint16_t)*propval;
	else
		goto out;

	if (di_prop_lookup_ints(DDI_DEV_T_ANY, node,
				"device-id", &propval) > 0)
		pcii->device_id = (uint16_t)*propval;
	else
		goto out;

	if (di_prop_lookup_ints(DDI_DEV_T_ANY, node,
				"subsystem-vendor-id", &propval) > 0)
		pcii->subvendor_id = (uint16_t)*propval;

	if (di_prop_lookup_ints(DDI_DEV_T_ANY, node,
				"subsystem-id", &propval) > 0)
		pcii->subdevice_id = (uint16_t)*propval;

	if (di_prop_lookup_ints(DDI_DEV_T_ANY, node,
				"revision-id", &propval) > 0)
		pcii->revision_id = (uint16_t)*propval;

	ret = 0;
out:
	di_fini(node);
	return (ret);
}
