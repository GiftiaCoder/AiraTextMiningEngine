
#ifndef _FORMAT_H_
#define _FORMAT_H_

#include "../defs.h"

int format_partition(int argc, const char **argv);

int begin_format(const char *path, struct partition_header_t *hdr);

#endif
