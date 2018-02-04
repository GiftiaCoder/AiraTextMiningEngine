
#include "help.h"

#include "../defs.h"
#include "../log.h"

const static char help_info[] = "help infomations:\n\t\
-help: show help info\n\t\
-format: format a partition to be a new storage(more details see -format -h)\n\t\
-start: start the engine on a specified partition(more details see -start -h)";

int print_help_msg(int argc, const char **argv)
{
	I(help_info);
	return OK;
}
