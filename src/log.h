
#ifndef _LOG_H_

void init_log_module();

void add_log(const char *lvl, const char *file, int line, const char *fmt, ...);

#define I(_fmt_, _arg_...) add_log("info", __FILE__, __LINE__, _fmt_, ##_arg_)
#define W(_fmt_, _arg_...) add_log("warning", __FILE__, __LINE__, _fmt_, ##_arg_)
#define E(_fmt_, _arg_...) add_log("error", __FILE__, __LINE__, _fmt_, ##_arg_)
#define D(_fmt_, _arg_...) add_log("debug", __FILE__, __LINE__, _fmt_, ##_arg_)

//#define _DEBUG
//#ifdef _DEBUG
//#else
//#define D(_fmt_, _arg_...)
//#endif

#endif
