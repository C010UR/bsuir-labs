#include "table.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "console.hpp"

Table::Table(std::vector<Table::Column> columns)
{
    this->columns = columns;
    this->size = columns.size();
}

void Table::draw_separator()
{
    std::cout << "|";

    for (std::size_t i = 0; i < this->size; i++)
    {
        std::cout << std::string(columns[i].width + 2, '-');

        if (i < this->size - 1)
        {
            std::cout << "+";
        }
    }

    std::cout << "|" << std::endl;
}

void Table::draw_headers()
{

    std::cout << "| ";

    for (std::size_t i = 0; i < this->size; i++)
    {
        std::cout
            << Console::set_styles(columns[i].styles)
            << std::setw(columns[i].width)
            << columns[i].label
            << Console::reset_style();

        if (i < this->size - 1)
        {
            std::cout << " | ";
        }
    }

    std::cout << " |" << std::endl;
    this->draw_separator();
}

void Table::draw_row(std::vector<std::string> row)
{

    std::cout << "| ";
    while (this->size > row.size())
    {
        row.push_back("");
    }

    for (std::size_t i = 0; i < this->size; i++)
    {
        std::cout
            << Console::set_styles(columns[i].styles)
            << std::setw(columns[i].width)
            << row[i]
            << Console::reset_style();

        if (i < this->size - 1)
        {
            std::cout << " | ";
        }
    }

    std::cout << " |" << std::endl;
}
