#include "log.h"

#if CFG_LOG_ENABLED==1 /* otherwise skip compilation */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// globals
static Log_Level_Type LOG_logLvl = LOG_LVL_INFO;
static FILE* LOG_logFile = NULL;

static const char *level_names[] = {
#if LOG_USE_COLOR==1
  "\x1b[94mTRACE\x1b[0m", "\x1b[36mDBGUG\x1b[0m", "\x1b[32mINFO \x1b[0m", "\x1b[33mWARN \x1b[0m", "\x1b[31mERROR\x1b[0m", "\x1b[35mFATAL\x1b[0m", "LOG"
#else
  "TRACE", "DBGUG", "INFO ", "WARN ", "ERROR", "FATAL", "LOG"
#endif
};


void LOG_log(Log_Level_Type level, const char *filename, int line, const char *format_str, ...){
	if (level < LOG_logLvl) { return; }
	va_list args;

	// get time
	time_t t = time(NULL);
	struct tm *lt = localtime(&t);
    char thetime[16];
    thetime[strftime(thetime, sizeof(thetime), "%H:%M:%S", lt)] = '\0';

	// log to stderr
	fprintf(stderr, "%s %s %s:%d: ", thetime, level_names[level], filename, line);
	//fprintf(stderr, "%s %s:%d: ", level_names[level], filename, line);
	va_start(args, format_str);
    vfprintf(stderr, format_str, args); fprintf(stderr, "\n");
    va_end(args);
    fflush(stderr);

	// log to file
	if (LOG_logFile != NULL){
		fprintf(LOG_logFile, "%s %.5s %s:%d: ", thetime, level_names[level]+5, filename, line);
		va_start(args, format_str);
    	vfprintf(LOG_logFile, format_str, args); fprintf(LOG_logFile, "\n");
		va_end(args);
    	fflush(LOG_logFile);
	}

}

void LOG_setLevel(Log_Level_Type level){
	LOG_logLvl = level;
	LOG_log(6, __FILEBASENAME__, __LINE__, "set log level to %s (%d)", level_names[level], level);  
}


void log_close_logfile(){
	fclose(LOG_logFile);
}

void LOG_setLogFile(const char *filepath){
	LOG_logFile = fopen(filepath, "a");
	fprintf(LOG_logFile, "\n\n=====\nStart Logging on %s\n=====\n", __DATE__);
	atexit(log_close_logfile);
}

#endif