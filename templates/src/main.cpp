#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "utils/console.hpp"
#include "utils/utils.hpp"
#include "utils/get.hpp"
#include "utils/table.hpp"
#include "utils/format.hpp"

int main(void)
{
    // used vector because pointers are old and not fun
    std::vector<int> arr = Get::stdin_vector<int>("Array", [](std::string str) -> int
                                                  { return std::stoi(str); });
    int count = 0;
    std::cout << Format::array<int>("array", arr, [](std::size_t index, int value)
                                         { (void)index; ; return std::to_string(value); })
              << std::endl;
    for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
    {
        if (*iter > 0)
            count++;
    }

    std::cout
        << "Number of positive numbers - "
        << Console::text(Console::Style::yellow, std::to_string(count))
        << std::endl;

    return EXIT_SUCCESS;
}