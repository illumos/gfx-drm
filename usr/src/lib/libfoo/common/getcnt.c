
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <libintl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/foo.h>

int
foo_getcnt(uint32_t *cntp)
{
	const char *devnm = "/dev/foo";
	int fd, rc;
	uint32_t cnt;

	fd = open(devnm, O_RDONLY, 0);
	if (fd == -1)
		return (errno);
	rc = ioctl(fd, FOO_IOC_GETCNT, cntp);
	close(fd);

	if (rc == -1)
		return (errno);

	return (0);
}

const char *
foo_message()
{
	const char *msg;

	msg = gettext("This is just an example");
	return (msg);
}
