#include "file_hash_map.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdlib.h>

int main()
{
    HashMap<int> hashMap(10);

    while (true) {
        std::cout << "Enter action (" << Color::CYAN << "show" << Color::RESET << ", " << Color::CYAN << "find"
                  << Color::RESET << ", " << Color::CYAN << "add" << Color::RESET << ", " << Color::CYAN << "delete"
                  << Color::RESET << "): " << Color::YELLOW;

        std::string action;
        std::cin >> action;

        std::cout << Color::RESET;

        if (action == "show") {
            hashMap.show();
        } else if (action == "find") {
            std::cout << "Enter key to find: ";
            std::string key;
            std::cin >> key;

            hashMap.find(key);
        } else if (action == "add") {
            std::cout << "Enter key to add: ";
            std::string key;
            std::cin >> key;

            std::cout << "Enter value to add: ";
            int value;
            std::cin >> value;

            hashMap.insert(key, value);
        } else if (action == "delete") {
            std::cout << "Enter key to delete: ";
            std::string key;
            std::cin >> key;

            hashMap.remove(key);
        } else {
            std::cout << "Invalid action!" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
