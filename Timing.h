#ifndef TIMING_H
#define TIMING_H

#include <sys/time.h>

timeval operator -(const timeval &l, const timeval &r);
timeval operator +(const timeval &l, const timeval &r);
double time2sec(const timeval &t);

#endif // TIMING_H
