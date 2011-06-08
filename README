
This is a skeleton of an "ON" (illumos) build.

You can use it to build drivers, libraries, and commands,
that you might plan to later integrate into illumos, but
don't want to wait for full illumos builds while you're
developing your code.

As provided, this skeleton builds one driver, one library,
and one command, all named "foo".  These are intentionally
trivial objects, just to demonstrate how it builds.

This does not do any package building (no IPS, no SysV).
Instead, this uses the script Install-foo as an example of
how one might do a developer-style "quick" install.

Here is a list of all the places you might want to copy
to add another driver, library, or command:

	uts/common/sys/foo.h
	uts/common/io/foo/*
	uts/common/Makefile.files	(FOO_OBJS += foo.o)
	uts/common/Makefile.rules	(common/io/foo, two places)
	uts/intel/Makefile.intel.shared	(DRV_KMODS += foo)
	uts/intel/foo/Makefile
	uts/sparc/Makefile.sparc.shared	(DRV_KMODS += foo)
	uts/sparc/foo/Makefile

	lib/libfoo/Makefile
	lib/libfoo/Makefile.com
	lib/libfoo/*/Makefile
	lib/libfoo/common/*

	cmd/foo

	Install-foo
