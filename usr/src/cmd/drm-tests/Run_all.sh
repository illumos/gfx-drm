#!/bin/sh
#
# Copyright 2016 Gordon W. Ross
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

#
# Running the tests:
#	/opt/drm-tests/Run_all.sh > drm-tests.log
#

# Leaving out random (takes a while), and in the meantime has been removed.
# Also updatedraw (broken at the moment)
# Deleted dristat drmstat from list below, also gone.
TESTS="drmdevice drmsl hash"

run_all() {
for f in $TESTS ; do
	echo "Running: $f";
	$1/$f
	x=$?
	if [ "$x" = 0 ] ; then
		echo "PASS: $f" >&2
	else
		echo "FAIL: $f" >&2
	fi
done
}

echo "Running all (32-bit)" >&2
run_all /opt/drm-tests

echo "Running all (64-bit)" >&2
run_all /opt/drm-tests/amd64
