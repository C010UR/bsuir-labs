#include <cstdlib>
#include <iostream>
#include <stdlib.h>

#include "avl_bst.h"
#include "colors.h"

int main(void)
{

    AVLBST<int> tree;

    while (true)
    {
        std::cout << "Choose one of the options: " << std::endl
                  << COLOR_CYAN << "  1. " << COLOR_RESET << "Insert new value." << std::endl
                  << COLOR_CYAN << "  2. " << COLOR_RESET << "Search a value in the tree." << std::endl
                  << COLOR_CYAN << "  3. " << COLOR_RESET << "Show the binary tree using 3 methods." << std::endl
                  << COLOR_CYAN << "  4. " << COLOR_RESET << "Exit the program." << std::endl;

        int choice;
        std::cout << "Choice: " << COLOR_YELLOW;
        std::cin >> choice;
        std::cout << COLOR_RESET << std::endl;

        switch (choice)
        {
            int value;
        case 1:
            int size;
            std::cout << "Number of values: " << COLOR_YELLOW;
            std::cin >> size;
            std::cout << COLOR_RESET;

            for (int i = 0; i < size; i++)
            {
                std::cout << "Insert value: " << COLOR_YELLOW;
                std::cin >> value;
                std::cout << COLOR_RESET;

                tree.insert(value);
            }

            break;
        case 2:
            std::cout << "Insert value to search: " << COLOR_YELLOW;
            std::cin >> value;
            std::cout << COLOR_RESET << std::endl;

            tree.search(value);

            break;
        case 3:
            tree.show();
            break;
        case 4:
            std::cout << "Exiting the program." << std::endl;
            return EXIT_SUCCESS;
        default:
            std::cout << "Unknown option: " << COLOR_RED << choice << COLOR_RESET << "." << std::endl;
            break;
        }

        std::cout << std::endl;
    }
}