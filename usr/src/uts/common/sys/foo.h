/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 *
 * A full copy of the text of the CDDL should have accompanied this
 * source.  A copy of the CDDL is also available via the Internet at
 * http://www.illumos.org/license/CDDL.
 */

/*
 * Copyright 2014 Nexenta Systems, Inc.  All rights reserved.
 */

#ifndef _SYS_FOO_H
#define	_SYS_FOO_H

#include <sys/types.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	FOO_IOC_GETCNT	1
typedef uint32_t foocnt_t;

#ifndef	_KERNEL
extern int foo_getcnt(uint32_t *);
#endif

#ifdef	__cplusplus
}
#endif

#endif /* _SYS_FOO_H */
