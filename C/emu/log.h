/* Simple Logger by Emanuel Regnath (emanuel.regnath@tum.de)    Date: 2015-05-20
 *
 * Description:
 * allows logging of string messages at several logging levels. 
 * Requires <stdio.h> <stdarg.h> <string.h> <time.h>
 */

#ifndef LOG_LOGGER_H
#define LOG_LOGGER_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdarg.h>
#include <string.h>


// settings: set to 1 or 0
#ifndef CFG_LOG_ENABLED
#define CFG_LOG_ENABLED 1    /* 1: enabled, 0: disable logging and remove any function calls */
#endif

#define LOG_USE_COLOR 1  /* 1: xterm color output 0: no color */


typedef enum Log_Level_Enum {
		LOG_LVL_TRACE,
		LOG_LVL_DEBUG, 
		LOG_LVL_INFO,   /* default level */
		LOG_LVL_WARN,
		LOG_LVL_ERROR,
		LOG_LVL_FATAL,
		LOG_LVL_OFF
	} Log_Level_Type;


/* public log interfaces */
#define LOG_trace(...) LOG_log(LOG_LVL_TRACE, __FILEBASENAME__, __LINE__, __VA_ARGS__)
#define LOG_debug(...) LOG_log(LOG_LVL_DEBUG, __FILEBASENAME__, __LINE__, __VA_ARGS__)
#define LOG_info(...)  LOG_log(LOG_LVL_INFO,  __FILEBASENAME__, __LINE__, __VA_ARGS__)
#define LOG_warn(...)  LOG_log(LOG_LVL_WARN,  __FILEBASENAME__, __LINE__, __VA_ARGS__)
#define LOG_error(...) LOG_log(LOG_LVL_ERROR, __FILEBASENAME__, __LINE__, __VA_ARGS__)
#define LOG_fatal(...) LOG_log(LOG_LVL_FATAL, __FILEBASENAME__, __LINE__, __VA_ARGS__)


#if CFG_LOG_ENABLED==1

	void LOG_log(Log_Level_Type level, const char *filename, int line, const char *format_str, ...);

	void LOG_setLevel(Log_Level_Type level);

	void LOG_setLogFile(const char *filepath);

#else // undefine functions if disabled
	#define LOG_log(a, b, c, d, ...)
	#define LOG_setLevel(x)
	#define LOG_setLogFile(x)
#endif


#define __FILEBASENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#ifdef __cplusplus
}
#endif
#endif

