#include "timer.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

double get_current_time(void)
{
#ifdef _WIN32
    LARGE_INTEGER freq;
    LARGE_INTEGER pc;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&pc);
    return pc.QuadPart * 1000.0 / freq.QuadPart;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
#endif
}

void timer_sleep(unsigned long long int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#elif defined(__unix__) || defined(__APPLE__)
    usleep(milliseconds * 1000);
#elif _POSIX_TIMERS
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    /* 无可用休眠函数时的简单忙等待（不推荐，可根据需要实现） */
    volatile unsigned long long int i;
    for (i = 0; i < milliseconds * 100000; ++i) {
        /* 空循环，仅作示例 */
    }
#endif
}
