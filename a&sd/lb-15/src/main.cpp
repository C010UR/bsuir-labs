#include "b_tree.hpp"

#include <cstdlib>
#include <iostream>
#include <random>

int main()
{
    BTree btree(3);

    while (true) {
        std::cout << "Enter action (" << Color::CYAN << "traverse" << Color::RESET << ", " << Color::CYAN << "find"
                  << Color::RESET << ", " << Color::CYAN << "add" << Color::RESET << ", " << Color::CYAN << "delete"
                  << Color::RESET << "): " << Color::YELLOW;

        std::string action;
        std::cin >> action;

        std::cout << Color::RESET;

        if (action == "traverse") {
            btree.traverse();
        } else if (action == "find") {
            std::cout << "Enter key to find: ";
            int key;
            std::cin >> key;

            auto result = btree.search(key);

            if (result != nullptr) {
                std::cout << Color::GREEN << "Found" << Color::RESET << std::endl;
            } else {
                std::cout << Color::RED << "Not Found" << Color::RESET << std::endl;
            }
        } else if (action == "add") {
            std::cout << "Enter value to add: ";
            int value;
            std::cin >> value;

            btree.insert(value);
        } else if (action == "delete") {
            std::cout << "Enter key to delete: ";
            int key;
            std::cin >> key;

            btree.remove(key);
        } else {
            std::cout << "Invalid action!" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
