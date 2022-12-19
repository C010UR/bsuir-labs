#include <iostream>
#include <cstdlib>
#include <cmath>
#include "utils/get.hpp"
#include "utils/utils.hpp"

int main(void)
{
    double x1 = Get::stdin_scalar<double>("X1");
    double y1 = Get::stdin_scalar<double>("Y1");
    double x2 = Get::stdin_scalar<double>("X2");
    double y2 = Get::stdin_scalar<double>("Y2");
    double x3 = Get::stdin_scalar<double>("X3");
    double y3 = Get::stdin_scalar<double>("Y3");

    // calculate sides lengths
    double line_a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double line_b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    double line_c = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));

    // set precision to 2 so i don't need to find too specific coordinates
    line_a = Utils::round(line_a, 2);
    line_b = Utils::round(line_b, 2);
    line_c = Utils::round(line_c, 2);

    if (line_a == line_b && line_a == line_c)
        std::cout << Console::success("Triangle is equal-sided.") << std::endl;
    else
        std::cout << Console::error("Triangle is not equal-sided.") << std::endl;

    return EXIT_SUCCESS;
}