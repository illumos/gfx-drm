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
 * Copyright 2011 Nexenta Systems, Inc.  All rights reserved.
 */

#include <stdio.h>
#include <foo.h>
#include <libintl.h>

int
main(int argc, char **argv)
{
	uint32_t cnt;
	int rc;

	rc = foo_getcnt(&cnt);
	if (rc != 0) {
		fprintf(stderr, "%s: err = %d\n", argv[0], rc);
		return (1);
	}

	printf(gettext("cnt = %u\n"), cnt);
	return (0);
}
