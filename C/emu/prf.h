/* Simple Profiler 
 * 
 * Authors:     Emanuel Regnath (emanuel.regnath@tum.de)
 *
 * Description:
 * Allows time and call measurments with little overhead. 
 * Can be deactivated to avoid any compilation.
 * Requires <stdio.h> and <time.h>
 */

#ifndef _PROFILER_H
#define _PROFILER_H

// number of samples analyzed for the moving average
#define PRF_AVG_WINDOW 10.0f

#ifndef CFG_PROFILER_ENABLED
#define CFG_PROFILER_ENABLED 1  /* 1: enabled, 0: disable profiling and remove any function call */
#endif

typedef unsigned long Profiler_Time_Type;

typedef struct {
    Profiler_Time_Type t_start;
    Profiler_Time_Type t_min;
    Profiler_Time_Type t_max;
    Profiler_Time_Type t_avg;
    Profiler_Time_Type t_total;
    unsigned int samples;   
} PRF_Profile;

#if CFG_PROFILER_ENABLED == 1

void PRF_start(PRF_Profile* profile);

void PRF_stop(PRF_Profile* profile);

void PRF_reset(PRF_Profile* profile);

Profiler_Time_Type PRF_time(PRF_Profile* profile);

void PRF_print(char* name, PRF_Profile* profile);

#else
#define PRF_start(p)
#define PRF_stop(x)
#define PRF_reset(x)
#define PRF_time(x) (0)
#define PRF_print(x, y)
#endif

#endif // _PROFILER_H
