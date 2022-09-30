#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "console.hpp"

class Format
{
public:
    template <typename T>
    static std::string array(const std::string name, const std::vector<T> &arr, std::function<std::string(const std::size_t, const T)> func)
    {
        std::size_t size = arr.size();
        std::string result = Console::text(Console::Style::green, name) + "[" + Console::text(Console::Style::yellow, std::to_string(size)) + "]: [";
        for (std::size_t i = 0; i < size; i++)
        {
            result += func(i, arr[i]);

            if (i < size - 1)
                result += ", ";
        }

        result += "]";

        return result;
    }

    template <typename T>
    static std::string array(const std::string name, const T *arr, const std::size_t size, std::function<std::string(const std::size_t, const T)> func)
    {
        std::vector<T> vec(arr, arr + size);
        return Format::array<T>(name, vec, func);
    }
};

#endif