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
 *
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Copyright 2011 Nexenta Systems, Inc.  All rights reserved.
 */


/*
 * Sample driver
 */

#include <sys/types.h>
#include <sys/errno.h>
#include <sys/stat.h>

#include <sys/file.h>
#include <sys/open.h>
#include <sys/poll.h>
#include <sys/uio.h>
#include <sys/cred.h>
#include <sys/modctl.h>
#include <sys/conf.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>

#include <sys/foo.h>

static dev_info_t *foo_dip;
static uint32_t foo_count;

static int foo_open(dev_t *, int, int, cred_t *);
static int foo_close(dev_t, int, int, cred_t *);
static int foo_ioctl(dev_t dev, int cmd, intptr_t arg, int mode,
				cred_t *credp, int *rvalp);

static int foo_attach(dev_info_t *, ddi_attach_cmd_t);
static int foo_detach(dev_info_t *, ddi_detach_cmd_t);
static int foo_getinfo(dev_info_t *, ddi_info_cmd_t, void *, void **);

/* DDI declarations */
static struct cb_ops foo_cb_ops = {
	foo_open,		/* open */
	foo_close,		/* close */
	nodev,			/* strategy */
	nodev,			/* print */
	nodev,			/* dump */
	nodev,			/* read */
	nodev,			/* write */
	foo_ioctl,		/* ioctl */
	nodev,			/* devmap */
	nodev,			/* mmap */
	nodev,			/* segmap */
	nochpoll,		/* chpoll */
	ddi_prop_op,		/* prop_op */
	NULL,			/* streamtab  */
	(D_NEW | D_MP), 	/* cb_flag */
	CB_REV,			/* cb_rev */
	nodev,			/* aread */
	nodev			/* awrite */
};

static struct dev_ops foo_ops = {
	DEVO_REV,		/* devo_rev, */
	0,			/* refcnt  */
	foo_getinfo,		/* get_dev_info */
	nulldev,		/* identify */
	nulldev,		/* probe */
	foo_attach,		/* attach */
	foo_detach,		/* detach */
	nodev,			/* reset */
	&foo_cb_ops,		/* driver operations */
	NULL,			/* bus operations */
	NULL,			/* power */
	ddi_quiesce_not_needed,		/* quiesce */
};

/* Modlinkage */
static struct modldrv modldrv = {
	&mod_driverops,
	"foo sample device",
	&foo_ops
};

static struct modlinkage modlinkage = {	MODREV_1, { &modldrv, NULL } };


/* DDI glue */

int
_init(void)
{
	return (mod_install(&modlinkage));
}

int
_fini(void)
{
	return (mod_remove(&modlinkage));
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}

static int
foo_attach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	if (cmd != DDI_ATTACH)
		return (DDI_FAILURE);

	if (ddi_create_minor_node(dip, "foo", S_IFCHR, 0,
	    DDI_PSEUDO, 0) == DDI_FAILURE) {
		ddi_remove_minor_node(dip, NULL);
		return (DDI_FAILURE);
	}

	foo_dip = dip;

	return (DDI_SUCCESS);
}

static int
foo_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	if (cmd != DDI_DETACH)
		return (DDI_FAILURE);

	foo_dip = NULL;
	ddi_remove_minor_node(dip, NULL);

	return (DDI_SUCCESS);
}

/*ARGSUSED*/
static int
foo_getinfo(dev_info_t *dip, ddi_info_cmd_t infocmd, void *arg, void **result)
{
	int error;

	switch (infocmd) {
	case DDI_INFO_DEVT2DEVINFO:
		*result = foo_dip;
		error = DDI_SUCCESS;
		break;
	case DDI_INFO_DEVT2INSTANCE:
		*result = (void *)0;
		error = DDI_SUCCESS;
		break;
	default:
		error = DDI_FAILURE;
	}
	return (error);
}

/*ARGSUSED3*/
static int
foo_open(dev_t *devp, int flag, int otyp, cred_t *credp)
{
	if (otyp != OTYP_CHR)
		return (EINVAL);

	if (flag & FEXCL)
		return (EINVAL);

	return (0);
}

/*ARGSUSED*/
static int
foo_close(dev_t dev, int flag, int otyp, cred_t *credp)
{
	return (0);
}

/*ARGSUSED*/
static int
foo_ioctl(dev_t dev, int cmd, intptr_t arg, int flags,	/* model.h */
	cred_t *cr, int *rvalp)
{
	int err;

	err = 0;
	switch (cmd) {
	case FOO_IOC_GETCNT:
		atomic_inc_32(&foo_count);
		if (ddi_copyout(&foo_count, (void *)arg,
		    sizeof (foo_count), flags))
			err = EFAULT;
		break;

	default:
		err = ENOTTY;
		break;
	}

	return (err);
}
