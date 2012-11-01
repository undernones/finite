#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils
{

const double PI = 3.14159265359;

inline bool isWhitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

inline double clamp(double x, double min, double max)
{
    return std::min(max, std::max(min, x));
}

inline double cube(double value)
{
    return value * value * value;
}

inline double sign(double x)
{
    return (x < 0) ? -1 : 1;
}

std::string makeRed(const std::string &s);
void error(const std::string &s);
std::string ftoa(double d, int decimalPlaces = 2);

}

#endif // UTILS_H
