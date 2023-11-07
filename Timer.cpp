
#include "Timer.h"


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else                 // _WIN32
#include <sys/time.h> //gettimeofday()
#include <unistd.h>   // sleep()
#endif                // _WIN32


double Timer::get_current_time()
{

#ifdef _WIN32
    LARGE_INTEGER freq;
    LARGE_INTEGER pc;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&pc);

    return pc.QuadPart * 1000.0 / freq.QuadPart;
#else  // _WIN32
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
#endif // _WIN32

}

void Timer::sleep(unsigned long long int milliseconds)
{

#ifdef _WIN32
    Sleep(milliseconds);
#elif defined(__unix__) || defined(__APPLE__)
    usleep(milliseconds * 1000);
#elif _POSIX_TIMERS
    struct timespec ts;
    ts.tv_sec = milliseconds * 0.001;
    ts.tv_nsec = 0;
    nanosleep(&ts, &ts);
#else
    // TODO How to handle it ?
#endif

}