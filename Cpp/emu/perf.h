/** Time profiling library
 *
 * \author Emanuel Regnath (emanuel.regnath@tum.de)
 *
 * \note
 *
 * usage:
 *    1. instanciate profiler
 *    2. call start()
 *    3. do your calculations
 *    4. call stop()
 *
 * you can deactivate the profiler with disable() to avoid performance loss
 *
 */


#ifndef _PROFILER_H
#define _PROFILER_H

// number of samples analyzed for the average
#define PROF_AVG_WINDOW 10.0F

typedef unsigned long Profiler_Time_Type;



class Profiler_Type {

    public:

        //Profiler_Type();

        void enable(void);
        void disable(void);

        void start(void);
        void stop(void);
        void reset(void);

        Profiler_Time_Type getMaximum();
        Profiler_Time_Type getAverage();
        unsigned long      getNumSamples();

    private:

        Profiler_Time_Type getTime();

        bool               m_isEnabled = true;
        Profiler_Time_Type m_startTime = Profiler_Time_Type(0);
        Profiler_Time_Type m_maxTime = Profiler_Time_Type(0);
        float              m_avgTime = 0.0;
        unsigned long      m_numSamples = 0;
};

#endif // _PROFILER_H
