

#include "perf.h"
#include <sys/time.h>

// adjust this method to return the system time
Profiler_Time_Type Profiler_Type::getTime(){

    struct timeval  tv;
    gettimeofday(&tv, nullptr);

    unsigned long time_in_mill = (tv.tv_sec) * 1000L + (tv.tv_usec) / 1000;

    return time_in_mill;
}


//Profiler_Type::Profiler_Type(){}


void Profiler_Type::enable(void){
    m_isEnabled = true;
}

void Profiler_Type::disable(void){
    m_isEnabled = false;
}

void Profiler_Type::start(void){
    if( !m_isEnabled ){return;}
    m_startTime = getTime();
}

void Profiler_Type::stop(void){
    if( !m_isEnabled ){return;}
    Profiler_Time_Type dt = getTime() - m_startTime;

    if(dt > m_maxTime){ m_maxTime = dt; }
    m_numSamples++;

    m_avgTime = m_avgTime * ((PROF_AVG_WINDOW-1.0)/PROF_AVG_WINDOW) + float(dt)/PROF_AVG_WINDOW;
}

void Profiler_Type::reset(void){
    m_numSamples = 0;
    m_maxTime = Profiler_Time_Type(0);
    m_startTime = Profiler_Time_Type(0);
}

Profiler_Time_Type Profiler_Type::getMaximum(){
    return m_maxTime;
}

Profiler_Time_Type Profiler_Type::getAverage(){
    return Profiler_Time_Type(m_avgTime);
}

unsigned long Profiler_Type::getNumSamples(){
    return m_numSamples;
}
