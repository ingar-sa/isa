#ifndef ISA_TIMING_HPP

/*
    Add #define DO_TIMING in ONE file where you include it
*/

#include <chrono>
#include <cassert>
#include <iostream>
#include <stdlib.h>

typedef std::chrono::high_resolution_clock::time_point time_point;
typedef std::chrono::duration<double> time_duration;

void
PrintErrTimingDisabled(void)
{
    printf("Timing has not been enabled! "
    "Define DO_TIMING before including the header to enable it.\n");
}

struct timing_data
{
    uint32_t NthTiming;
    time_point StartTime;
    time_point EndTime;
    time_duration Duration;
};

struct timing
{
    time_point StartTime;
    time_point EndTime;
};

struct timings
{
    bool TimingStarted;
    uint32_t NTimings;
    uint32_t idx;

    time_point InitTime;
    timing *Timings;
};


/*
    Private functions. Should only be called through provided macros.
*/
static timings *
GetTimings__()
{
    static timings Timings = { false, 0, 0, time_point(), NULL };
    return &Timings;
}

inline void
StartTiming__(time_point Time)
{
    timings *Timings = GetTimings__();
    assert(!Timings->TimingStarted);
    
    Timings->idx += 1;
    Timings->Timings[Timings->idx].StartTime = Time;
    Timings->TimingStarted = true;
}

inline void
EndTiming__(time_point Time)
{
    timings *Timings = GetTimings__();
    assert(Timings->TimingStarted);

    Timings->Timings[Timings->idx].EndTime = Time;
    Timings->TimingStarted = false;
}


/*
    We use macros so the timing is not done inside a function call
*/
#ifdef DO_TIMING
#define START_TIMING() \
do { \
    time_point TimeStart = std::chrono::high_resolution_clock::now(); \
    StartTiming__(TimeStart); \
} while(0)

#define END_TIMING() \
do { \
    time_point TimeEnd = std::chrono::high_resolution_clock::now(); \
    EndTiming__(TimeEnd); \
} while(0)
#else
#define START_TIMING()
#define END_TIMING()
#endif


/*
    Public functions.
*/
timing_data
GetTimingData(uint32_t NthTiming)
{
#ifndef DO_TIMING
//    PrintErrTimingDisabled();
    return {0};
#else
    timings *Timings = GetTimings__();
    if(NthTiming < 1 || NthTiming >= Timings->NTimings) { return {0}; }

    uint32_t idx  = NthTiming - 1;
    timing Timing = Timings->Timings[idx];

    time_point    StartTime = Timing.StartTime;
    time_point    EndTime   = Timing.EndTime;
    time_duration Duration  = std::chrono::duration_cast<time_duration>(EndTime - StartTime);

    timing_data TimingData = 
    {
        NthTiming,
        StartTime,
        EndTime,
        Duration
    };

    return TimingData;
#endif
}

timing_data
GetLastTimingData(void)
{
#ifndef DO_TIMING
//    PrintErrTimingDisabled();
    return {0};
#else
    return GetTimingData(GetTimings__()->idx + 1);
#endif
}

void
PrintTimingData(timing_data TimingData)
{
#ifndef DO_TIMING
//    PrintErrTimingDisabled();
    return;
#else
    timings *Timings = GetTimings__();

    std::cout << "Timing nr. " << TimingData.NthTiming << ":\n";

    time_duration StartTimeSinceInit = std::chrono::duration_cast<time_duration>(TimingData.StartTime - Timings->InitTime);
    std::cout << "Start time since init: " << StartTimeSinceInit.count() << " seconds\n";

    time_duration EndTimeSinceInit = std::chrono::duration_cast<time_duration>(TimingData.EndTime - Timings->InitTime);
    std::cout << "End time since init: " << EndTimeSinceInit.count() << " seconds\n";

    std::cout << "Timing duration: " << TimingData.Duration.count() << " seconds\n";
#endif
}

void
PrintTimingData(uint32_t NthTiming)
{
#ifndef DO_TIMING
//    PrintErrTimingDisabled();
    return;
#else
    timing_data TimingData = GetTimingData(NthTiming);
    PrintTimingData(TimingData);
#endif
}

void
PrintTimingData(uint32_t NthTiming, const char *Message)
{
#ifndef DO_TIMING
//    PrintErrTimingDisabled();
    return;
#else
    printf(Message);
    timing_data TimingData = GetTimingData(NthTiming);
    PrintTimingData(TimingData);
#endif
}

void
PrintLastTimingData(void)
{
#ifndef DO_TIMING
//    PrintErrTimingDisabled();
    return;
#else
    timing_data TimingData = GetTimingData(GetTimings__()->idx + 1);
    PrintTimingData(TimingData);
#endif
}

int
InitTiming(uint32_t NTimings)
{
#ifndef DO_TIMING
//    PrintErrTimingDisabled();
    return 1;
#else
    timings *Timings = GetTimings__();

    Timings->NTimings = NTimings;
    Timings->idx = -1; // Will be incremented to 0 on first timing
    Timings->Timings = (timing *)calloc(NTimings, sizeof(timing)); 

    if(NULL == Timings->Timings)
    {
        return 1;
    }

    Timings->InitTime = std::chrono::high_resolution_clock::now();

    return 0;
#endif
}

#define ISA_TIMING_HPP
endif