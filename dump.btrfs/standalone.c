#include "kerncompat.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include "kernel-shared/disk-io.h"
#include "kernel-shared/volumes.h"

void uuid_unparse(const uuid_t uu, char *out)
{
	sprintf(out,
		"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		uu[0], uu[1], uu[2], uu[3], uu[4], uu[5], uu[6], uu[7],
		uu[8], uu[9], uu[10], uu[11], uu[12], uu[13], uu[14], uu[15]);
}

static int hexval(int c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	return -1;
}

int uuid_parse(const char *in, uuid_t uu)
{
	char compact[32];
	int n = 0;

	for (; *in; in++) {
		if (*in == '-')
			continue;
		if (!isxdigit((unsigned char)*in) || n >= 32)
			return -1;
		compact[n++] = *in;
	}
	if (n != 32)
		return -1;
	for (n = 0; n < 16; n++) {
		int hi = hexval(compact[n * 2]);
		int lo = hexval(compact[n * 2 + 1]);

		if (hi < 0 || lo < 0)
			return -1;
		uu[n] = (hi << 4) | lo;
	}
	return 0;
}

void uuid_generate(uuid_t out)
{
	unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
	int i;

	for (i = 0; i < 16; i++) {
		seed = seed * 1103515245U + 12345U;
		out[i] = (seed >> 16) & 0xff;
	}
	out[6] = (out[6] & 0x0f) | 0x40;
	out[8] = (out[8] & 0x3f) | 0x80;
}

int uuid_is_null(const uuid_t uu)
{
	int i;

	for (i = 0; i < 16; i++) {
		if (uu[i])
			return 0;
	}
	return 1;
}

int btrfs_scan_devices(int verbose)
{
	(void)verbose;
	return 0;
}

int btrfs_scan_argv_devices(int dev_optind, int argc, char **argv)
{
	int ret = 0;

	while (dev_optind < argc) {
		struct btrfs_fs_devices *fs_devices;
		u64 num_devices;
		int fd;

		fd = open(argv[dev_optind], O_RDONLY);
		if (fd < 0) {
			ret = -errno;
			fprintf(stderr, "ERROR: cannot open '%s': %m\n",
				argv[dev_optind]);
			goto next;
		}
		ret = btrfs_scan_one_device(fd, argv[dev_optind], &fs_devices,
					    &num_devices,
					    BTRFS_SUPER_INFO_OFFSET,
					    SBREAD_DEFAULT);
		close(fd);
next:
		dev_optind++;
	}
	return ret;
}

int btrfs_register_all_devices(void)
{
	return 0;
}

int test_uuid_unique(const char *uuid_str)
{
	(void)uuid_str;
	return 1;
}

int device_get_queue_param(const char *file, const char *param, char *buf,
			   size_t len)
{
	(void)file;
	(void)param;
	(void)buf;
	(void)len;
	return -ENOENT;
}

u64 device_get_zone_unusable(int fd, u64 flags)
{
	(void)fd;
	(void)flags;
	return 0;
}

u64 device_get_zone_size(int fd, const char *name)
{
	(void)fd;
	(void)name;
	return 0;
}
