
#include <string.h>

#include "log.h"
#include "time.h"
#include "basic_defs.h"

#include "help/help.h"
#include "format/format.h"

#define SDCARD_PARTITION ("/dev/mmcblk1p1")

/*abool format_partition(const char *partition, struct partition_header_t *header)
{
	int fd_partition = open(partition, O_RDWR);
	if (fd_partition == -1)
	{
		E("cannot open storage partition");
		return FALSE;
	}
	
	// set top 4GB in SD card to zero as characters relation map
	const uint64_t page_size = 1024 * 1024 * 64; // 64MB
	const uint64_t write_time = ((uint64_t)4 * 1024 * 1024 * 1024) / page_size; // 4GB / page_size
	void *page_buff = malloc(page_size);
	memset(page_buff, 0, page_size);
	for (uint64_t i = 0; i < write_time; ++i)
	{
		write(fd_partition, page_buff, page_size);
	}
	free(page_buff);
	
	// write partition header
	write(fd_partition, (void *)header, sizeof(header));
	
	close(fd_partition);
	return TRUE;
}*/

int main(int argc, const char **argv)
{
	const static struct 
	{
		char cmd[32];
		int(*action)(int, const char **);
	} cmd_list[] = 
	{
		{ "-help", print_help_msg }, 
		{ "-format", format_partition }, 
	};
	
	if (argc > 1)
	{
		for (int i = 0; i < sizeof(cmd_list) / sizeof(cmd_list[0]); ++i)
		{
			if (strncmp(cmd_list[i].cmd, argv[1], sizeof(cmd_list[i].cmd)) == 0)
			{
				return cmd_list[i].action(argc, argv);
			}
		}
	}
	return print_help_msg(argc, argv);
}
