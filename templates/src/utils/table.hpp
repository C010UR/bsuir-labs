#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include <string>
#include "console.hpp"

/**
 * @brief Allows to draw tables
 * 
 */
class Table
{

public:
    struct Column
    {
        std::string label;
        unsigned width;
        std::vector<Console::Style> styles;
    };

    Table(std::vector<Table::Column> columns);

    /**
     * @brief Draws table separator
     * 
     */
    void draw_separator();

    /**
     * @brief Draws table headers
     * 
     */
    void draw_headers();

    /**
     * @brief Draws table row
     * 
     * @param row 
     */
    void draw_row(std::vector<std::string> row);

private:
    size_t size;
    std::vector<Table::Column> columns;
};

#endif