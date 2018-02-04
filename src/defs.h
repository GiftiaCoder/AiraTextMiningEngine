
#ifndef _DEFS_H_
#define _DEFS_H_

#include "basic_defs.h"

struct partition_config_t
{
	uint64_t max_data_len;
	uint32_t block_size;
	uint32_t serial_bytes;
};

struct partition_info_t
{
	uint64_t word_num;
	uint32_t max_block_num;
	uint32_t block_num;
};

typedef char string16_t[16];

struct partition_header_t
{
	struct partition_config_t config;
	uint8_t config_reserve[128 - sizeof(struct partition_config_t)];
	
	struct partition_info_t info;
	uint8_t info_reserve[128 - sizeof(struct partition_info_t)];
	
	string16_t version;
	string16_t name;
	
	char description[4096 - (128 + 128 + sizeof(string16_t) * 2)];
};

#endif
