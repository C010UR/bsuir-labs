#include "console.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <stdexcept>

std::string Console::set_style(const Console::Style style)
{
    return "\033[" + std::to_string(style) + "m";
}

std::string Console::set_styles(const std::vector<Console::Style> styles)
{
    std::string style = "";

    for (std::vector<Console::Style>::const_iterator i = styles.begin(); i != styles.end(); i++)
    {
        style += std::to_string(*i);

        if (i + 1 != styles.end())
        {
            style += ";";
        }
    }
    return "\033[" + style + "m";
}

std::string Console::reset_style()
{
    return "\033[0m";
}

std::string Console::text(const Console::Style style, const std::string text)
{
    return Console::set_style(style) + text + Console::reset_style();
}

std::string Console::text(const std::vector<Console::Style> style, const std::string text)
{
    return Console::set_styles(style) + text + Console::reset_style();
}

std::string Console::success(const std::string message)
{
    return Console::set_styles({Console::Style::white, Console::Style::bg_green}) + ":: " + message + " " + Console::reset_style();
}

std::string Console::info(const std::string message)
{
    return Console::set_styles({Console::Style::white, Console::Style::bg_cyan}) + ":? " + message + " " + Console::reset_style();
}

std::string Console::warning(const std::string message)
{
    return Console::set_styles({Console::Style::white, Console::Style::bg_yellow}) + ":! " + message + " " + Console::reset_style();
}

std::string Console::error(const std::string message)
{
    return Console::set_styles({Console::Style::white, Console::Style::bg_red}) + "!! " + message + " " + Console::reset_style();
}

std::string Console::move_to_start()
{
    return "\033[H";
}

std::string Console::move_to(unsigned line, unsigned column)
{
    return "\033[" + std::to_string(line) + ";" + std::to_string(column) + "H";
}

std::string Console::move_up(unsigned lines)
{
    return "\033[" + std::to_string(lines) + "A";
}

std::string Console::move_down(unsigned lines)
{
    return "\033[" + std::to_string(lines) + "B";
}

std::string Console::move_up_column_reset(unsigned lines)
{
    return "\033[" + std::to_string(lines) + "F";
}

std::string Console::move_down_column_reset(unsigned lines)
{
    return "\033[" + std::to_string(lines) + "E";
}

std::string Console::move_left(unsigned columns)
{
    return "\033[" + std::to_string(columns) + "D";
}

std::string Console::move_right(unsigned columns)
{
    return "\033[" + std::to_string(columns) + "C";
}

std::string Console::erase_to_end()
{
    return "\033[0J";
}

std::string Console::erase_to_beginning()
{
    return "\033[1J";
}

std::string Console::erase_all()
{
    return "\033[2J";
}

std::string Console::erase_line()
{
    return "\033[2K";
}

std::string Console::erase_to_end_in_line()
{
    return "\033[0K";
}

std::string Console::erase_to_beginning_in_line()
{
    return "\033[1K";
}
