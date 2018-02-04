
#include "time.h"

#include <stdlib.h>
#include <sys/time.h>

uint64_t get_curr_sec()
{
	struct timeval tim = { 0 };
	gettimeofday(&tim, NULL);
	return (uint64_t)tim.tv_sec;
}

uint64_t get_curr_usec()
{
	struct timeval tim = { 0 };
	gettimeofday(&tim, NULL);
	return (uint64_t)tim.tv_usec;
}
