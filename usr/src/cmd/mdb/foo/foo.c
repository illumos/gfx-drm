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
 * Copyright 2016 Gordon Ross <gordon.w.ross@gmail.com>
 */

/*
 * Example mdb module: foo
 */
#include <sys/mdb_modapi.h>
#include <sys/foo.h>

/*
 * One would be correct to observe that a dcmd is unnecessary for
 * just printing a variable with mdb.  This is just an example,
 * where a more real-world case would print something larger and
 * more complex than a foocnt_t.
 */

void
foo_cnt_help(void)
{
	mdb_printf("Print device ID information of Intel graphics card.\n");
}

/* ARGSUSED */
static int
foo_cnt_dcmd(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	GElf_Sym sym;
	foocnt_t count;

	/* Does not take an address. */
	if (flags & DCMD_ADDRSPEC)
		return (DCMD_USAGE);

	/* Locate the foo_count variable */
	if (mdb_lookup_by_obj("foo", "foo_count", &sym)) {
		mdb_warn("failed to lookup `foo_count'\n");
		return (DCMD_ERR);
	}
	addr = (uintptr_t)sym.st_value;

	if (mdb_vread(&count, sizeof (count), addr) == -1) {
		mdb_warn("failed to read foo_count at %p", addr);
		return (DCMD_ERR);
	}

	mdb_printf("foo_count = %d\n", count);

	return (DCMD_OK);
}


/*
 * MDB module linkage information:
 *
 * We declare a list of structures describing our dcmds, a list of structures
 * describing our walkers, and a function named _mdb_init to return a pointer
 * to our module information.
 */

static const mdb_dcmd_t dcmds[] = {
	{
		"foo_cnt",
		"?",
		"get foo_count",
		foo_cnt_dcmd,
		foo_cnt_help
	},
	{ NULL }
};

static const mdb_walker_t walkers[] = {
	/* none */
	{ NULL }
};

static const mdb_modinfo_t modinfo = {
	MDB_API_VERSION, dcmds, walkers
};

const mdb_modinfo_t *
_mdb_init(void)
{
	return (&modinfo);
}
