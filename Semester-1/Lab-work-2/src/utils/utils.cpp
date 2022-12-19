#include "utils.hpp"

double Utils::round(double value, unsigned short precision)
{
    unsigned long prec = 1;
    for (; precision > 1; --precision, prec *= 10)
        ;
    return (long long)(value * prec) / (double)prec;
}