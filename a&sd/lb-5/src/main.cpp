#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdlib.h>

#include "hash_map.h"

template <typename T = unsigned> void showVector(std::vector<T> vec)
{
    std::cout << "Input array ("
              << "\033[33m" << vec.size() << "\033[0m"
              << "):" << std::endl;

    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << "  array["
                  << "\033[36m" << std::setw(2) << i << "\033[0m"
                  << "] - "
                  << "\033[33m" << vec[i] << "\033[0m" << std::endl;
    }

    std::cout << std::endl;
}

int main()
{
    const int M   = 20;
    const int n   = 15;
    const int min = 12000;
    const int max = 34000;

    // Some random C++ bullsh*t
    std::random_device rd;
    // seed value is designed specifically to make initialization
    // parameters of std::mt19937 (instance of std::mersenne_twister_engine<>)
    // different across executions of application
    std::mt19937::result_type seed
        = rd()
          ^ ((std::mt19937::result_type
             )std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())
                 .count()
             + (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch()
             )
                   .count());

    std::mt19937 gen(seed);

    std::uniform_int_distribution<unsigned> distribution(min, max);

    std::vector<unsigned> vec;
    HashMap<unsigned>     map(M);

    for (int i = 0; i < n; i++)
    {
        vec.push_back(distribution(gen));
        map.insert(i + 1, vec.back());
        std::cout << std::endl;
    }

    showVector(vec);
    map.show();

    std::cout << std::endl;

    while (true)
    {
        int searchKey;
        std::cout << "Search for value with key ("
                  << "\033[35m"
                  << "use ctrl + c to exit"
                  << "\033[0m"
                  << ") - "
                  << "\033[33m";
        std::cin >> searchKey;
        std::cout << "\033[0m";

        unsigned *value = map.find(searchKey);

        if (value == nullptr)
        {
            std::cout << std::endl
                      << "\033[31m"
                      << "  Key is not present in the hash map."
                      << "\033[0m" << std::endl
                      << std::endl;
        }
        else
        {
            std::cout << std::endl
                      << "  Found: "
                      << "\033[33m" << *value << "\033[0m" << std::endl
                      << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
