
#include "format.h"

#include <stdio.h>
#include <string.h>

#include "../log.h"

const static struct partition_header_t DEFAULT_PARTITION_HEADER = { 0 };

const static char format_help_info[] = "format help:\n\t\
-p:set storage partition path(eg. -p/dev/mmcblk1p1)\n\t\
-b:set block size(eg. -b4k)\n\t\
-s:set serial bytes(eg. -s8)\n\t\
-d:set max data len(eg. -d4g)";

struct partition_format_info_t 
{
	struct partition_header_t hdr;
	char pth[1024];
};

static abool get_size_param(const char *par, uint64_t *out)
{
	uint64_t val = 0;
	char unit = 0;
	sscanf(par, "%lu%c", &val, &unit);
	switch(unit)
	{
	case '\0':
		break;
	case 'k': case 'K':
		val *= (uint64_t)1024;
		break;
	case 'm': case 'M':
		val *= ((uint64_t)1024 * 1024);
		break;
	case 'g': case 'G':
		val *= ((uint64_t)1024 * 1024 * 1024);
		break;
	default:
		E("unknown unit name: %c", unit);
		return FALSE;
	}
	return (*out = val) > 0;
}

static abool format_show_help_info(struct partition_format_info_t *inf, const char *par)
{
	I(format_help_info);
	return TRUE;
}

static abool format_set_partition_path(struct partition_format_info_t *inf, const char *par)
{
	strncpy(inf->pth, par, sizeof(inf->pth));
	D("path: %s", inf->pth);
	return TRUE;
}

static abool format_set_block_size(struct partition_format_info_t *inf, const char *par)
{
	uint64_t block_size = 0;
	if (get_size_param(par, &block_size))
	{
		D("block size: %lu", block_size);
		return (inf->hdr.config.block_size = (uint32_t)block_size) > 0;
	}
	return FALSE;
}

static abool format_set_serial_bytes(struct partition_format_info_t *inf, const char *par)
{
	uint64_t serial_bytes = 0;
	if (get_size_param(par, &serial_bytes))
	{
		D("serial bytes: %lu", serial_bytes);
		return (inf->hdr.config.serial_bytes = (uint32_t)serial_bytes) > 0;
	}
	return FALSE;
}

static abool format_set_max_data_len(struct partition_format_info_t *inf, const char *par)
{
	uint64_t max_data_len = 0;
	if (get_size_param(par, &max_data_len))
	{
		D("max data len: %lu", max_data_len);
		return (inf->hdr.config.max_data_len = max_data_len) > 0;
	}
	return FALSE;
}

// format entrance
int format_partition(int argc, const char **argv)
{
	const static struct 
	{
		char c;
		abool(*set_param)(struct partition_format_info_t *, const char *);
	}par_list[] = 
	{
		{ 'h', format_show_help_info }, 
		{ 'p', format_set_partition_path }, 
		{ 'b', format_set_block_size }, 
		{ 's', format_set_serial_bytes }, 
		{ 'd', format_set_max_data_len }, 
	};
	
	struct partition_format_info_t *inf = (struct partition_format_info_t *)malloc(sizeof(struct partition_format_info_t));
	inf->hdr = DEFAULT_PARTITION_HEADER;
	memset((void *)inf->pth, 0, sizeof(inf->pth));
	
	for (int par_idx = 2; par_idx < argc; ++par_idx)
	{
		const char *par = argv[par_idx];
		if (*par != '-')
		{
			E("error param format: %s", par);
			format_show_help_info(NULL, NULL);
			return ERROR;
		}

		char c = *(++par);
		for (int hdl_idx = 0; hdl_idx < sizeof(par_list) / sizeof(par_list[0]); ++hdl_idx)
		{
			if (c == par_list[hdl_idx].c)
			{
				if (par_list[hdl_idx].set_param(inf, ++par))
				{
					break;
				}
				
				E("read param error");
				return ERROR;
			}
		}
	}
	
	int ret = begin_format(inf->pth, &inf->hdr);
	free(inf);
	return ret;
}
