
#include "format.h"

#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/vfs.h>
#include <sys/statvfs.h>
#include <fcntl.h>

#include <unistd.h>

#include "../log.h"

#include <stdio.h>
static uint64_t get_disk_size(const char *path)
{
	uint64_t size = 0;
	FILE *fp = fopen(path, "rb");
	if (!fp)
	{
		E("open file fail: %s", path);
		return FALSE;
	}
	fseek(fp, SEEK_SET, SEEK_END);
	size = ftell(fp);
	fclose(fp);
	return size;
}

static abool check_header_data(const char *path, struct partition_header_t *hdr)
{
	uint64_t disk_size = get_disk_size();
	if (disk_size < 1)
	{
		E("get disk size error: %s", path);
	}
	
	// TODO data check
	
	return FALSE;
}

static abool reset_char_relation_map(int fd)
{
	// TODO
}

static abool init_data_header(int fd, struct partition_header_t *hdr)
{
	// TODO
}

int begin_format(const char *path, struct partition_header_t *hdr)
{
	if (!check_header_data(fd, hdr))
	{
		E("invalid header info");
		close(fd);
		return ERROR;
	}
	
	int fd = open(path, O_RDWR);
	if (fd < 0)
	{
		E("cannot open storage partition");
		return ERROR;
	}
	
	// set top 4GB in SD card to zero as characters relation map
	const uint64_t page_size = 1024 * 1024 * 64; // 64MB
	const uint64_t write_time = ((uint64_t)4 * 1024 * 1024 * 1024) / page_size; // 4GB / page_size
	void *page_buff = malloc(page_size);
	memset(page_buff, 0, page_size);
	for (uint64_t i = 0; i < write_time; ++i)
	{
		//write(fd, page_buff, page_size);
	}
	free(page_buff);
	
	// write partition header
	//write(fd, (void *)hdr, sizeof(*hdr));
	
	close(fd);
	return OK;
}
