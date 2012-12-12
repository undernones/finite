#include "Timing.h"

timeval
operator -(const timeval& l, const timeval& r)
{
    timeval result;
    result.tv_sec = l.tv_sec - r.tv_sec;
    result.tv_usec = l.tv_usec - r.tv_usec;

    if (result.tv_usec < 0) {
        result.tv_usec = 1e6 + result.tv_usec;
        result.tv_sec--;
    }

    return result;
}

timeval
operator +(const timeval& l, const timeval& r)
{
    timeval result;
    result.tv_sec = l.tv_sec + r.tv_sec;
    result.tv_usec = l.tv_usec + r.tv_usec;

    time_t extraSeconds = result.tv_usec / 1e6;
    result.tv_sec += extraSeconds;
    result.tv_usec -= extraSeconds * 1e6;

    return result;
}

double
time2sec(const timeval& t)
{
    return t.tv_sec + (t.tv_usec / 1e6);
}
