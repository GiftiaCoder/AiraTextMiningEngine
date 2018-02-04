
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <errno.h>

#include <pthread.h>

static pthread_mutex_t g_log_mut;

void init_log_module()
{
	pthread_mutex_init(&g_log_mut, NULL);
}

void add_log(const char *lvl, const char *file, int line, const char *fmt, ...)
{
	static char log_buff[1024 * 1024] = { 0 };
	
	va_list vl;
	va_start(vl, fmt);
	
	pthread_mutex_lock(&g_log_mut);
	
	vsnprintf(log_buff, sizeof(log_buff) - 1, fmt, vl);
	printf("[%s][f:%s][l:%d][e:%s]%s\n", lvl, file, line, strerror(errno), log_buff);
	
	pthread_mutex_unlock(&g_log_mut);
	
	va_end(vl);
}
