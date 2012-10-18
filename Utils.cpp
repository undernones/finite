#include "Utils.h"
#include <iomanip>
#include <sstream>
#include <iostream>

namespace Utils
{

std::string
makeRed(const std::string &s)
{
    return "\033[22;31m" + s + "\033[01;37m";
}

void
error(const std::string &s)
{
    std::cerr << makeRed(s) << std::endl;
}

std::string
ftoa(double d, int decimalPlaces)
{
    std::stringstream stream;
    stream << std::setiosflags(std::ios::fixed) << std::setprecision(decimalPlaces) << d;
    return stream.str();
}

}
