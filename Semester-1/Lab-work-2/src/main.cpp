#include <iostream>
#include <cstdlib>
#include "utils/console.hpp"
#include "utils/utils.hpp"
#include "utils/get.hpp"

int main(void)
{
    int a = Get::stdin_scalar<int>("A");
    int b = Get::stdin_scalar<int>("B");
    int sum = 0;

    for (; a < b; sum += a, a++)
        ;

    std::cout
        << "Sum of "
        << Console::text(Console::Style::green, "[")
        << Console::text(Console::Style::yellow, "A")
        << "; "
        << Console::text(Console::Style::yellow, "B")
        << Console::text(Console::Style::green, ")")
        << " equals to "
        << Console::text(Console::Style::yellow, std::to_string(sum))
        << std::endl;

    return EXIT_SUCCESS;
}