#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include <vector>

/**
 * @brief ANSI Escape code generator
 * 
 */
class Console
{
public:
    enum Style
    {
        bold = 1,
        dim = 2,
        italic = 3,
        underline = 4,
        blinking = 5,
        strikethrough = 9,
        black = 30,
        bg_black = 40,
        red = 31,
        bg_red = 41,
        green = 32,
        bg_green = 42,
        yellow = 33,
        bg_yellow = 43,
        blue = 34,
        bg_blue = 44,
        magenta = 35,
        bg_magenta = 45,
        cyan = 36,
        bg_cyan = 46,
        white = 37,
        bg_white = 47,
        _default = 39,
        _bg_default = 49,
    };

    /**
     * @brief Returns string that will set specified style in console.
     *
     * @param style
     * @return ANSI escape code.
     */
    static std::string set_style(const Console::Style style);

    /**
     * @brief Returns string that will set specified styles in console.
     *
     * @param styles
     * @return ANSI escape code.
     */
    static std::string set_styles(const std::vector<Console::Style> styles);

    /**
     * @brief Returns string that will reset all styles in console.
     *
     * @return ANSI escape code.
     */
    static std::string reset_style();

    /**
     * @brief Returns text with ANSI Escape Code style.
     *
     * @param style
     * @param text
     * @return Text with ANSI Escape Codes.
     *
     * @attention Use it only to display styled text in terminal. Using for operations with strings may result in undefined behaviour!
     */
    static std::string text(const Console::Style style, const std::string text);

    /**
     * @brief Returns text with ANSI Escape Code styles.
     *
     * @param style
     * @param text
     * @return Text with ANSI Escape Codes.
     *
     * @attention Use it only to display styled text in terminal. Using for operations with strings may result in undefined behaviour!
     */
    static std::string text(const std::vector<Console::Style> style, const std::string text);

    /**
     * @brief Returns formatted success message.
     *
     * @param message
     * @return Text with ANSI Escape Codes.
     *
     * @attention Use it only to display styled text in terminal. Using for operations with strings may result in undefined behaviour!
     */
    static std::string success(const std::string message);

    /**
     * @brief Returns formatted info message.
     *
     * @param message
     * @return Text with ANSI Escape Codes.
     *
     * @attention Use it only to display styled text in terminal. Using for operations with strings may result in undefined behaviour!
     */
    static std::string info(const std::string message);

    /**
     * @brief Returns formatted warning message.
     *
     * @param message
     * @return Text with ANSI Escape Codes.
     *
     * @attention Use it only to display styled text in terminal. Using for operations with strings may result in undefined behaviour!
     */
    static std::string warning(const std::string message);

    /**
     * @brief Returns formatted error message.
     *
     * @param message
     * @return Text with ANSI Escape Codes.
     *
     * @attention Use it only to display styled text in terminal. Using for operations with strings may result in undefined behaviour!
     */
    static std::string error(const std::string message);

    /**
     * @brief Moves terminal cursor to start position.
     *
     * @return ANSI Escape Code.
     *
     */
    static std::string move_to_start();

    /**
     * @brief Moves terminal cursor to specified position.
     *
     * @param line
     * @param column
     *
     * @return ANSI Escape Code.
     *
     */
    static std::string move_to(unsigned line, unsigned column);

    /**
     * @brief Moves cursor up specified amount of lines.
     *
     * @param lines
     * @return ANSI Escape Code.
     */
    static std::string move_up(unsigned lines);
    /**
     * @brief Moves cursor down specified amount of lines.
     *
     * @param lines
     * @return ANSI Escape Code.
     */
    static std::string move_down(unsigned lines);

    /**
     * @brief Moves cursor left specified amount of columns.
     *
     * @param columns
     * @return ANSI Escape Code.
     */
    static std::string move_left(unsigned columns);

    /**
     * @brief Moves cursor up specified amount of lines.
     *
     * @param lines
     * @return ANSI Escape Code.
     */
    static std::string move_up_column_reset(unsigned lines);
    /**
     * @brief Moves cursor down specified amount of lines.
     *
     * @param lines
     * @return ANSI Escape Code.
     */
    static std::string move_down_column_reset(unsigned lines);

    /**
     * @brief Moves cursor right specified amount of columns.
     *
     * @param columns
     * @return ANSI Escape Code.
     */
    static std::string move_right(unsigned columns);

    /**
     * @brief Erases screen from cursor to end of the screen.
     *
     * @return ANSI Escape Code.
     */
    static std::string erase_to_end();

    /**
     * @brief Erases screen from cursor to beginning of the screen.
     *
     * @return ANSI Escape Code.
     */
    static std::string erase_to_beginning();

    /**
     * @brief Erases entire screen.
     *
     * @return ANSI Escape Code.
     */
    static std::string erase_all();

    /**
     * @brief Erases entire line.
     *
     * @return ANSI Escape Code.
     */
    static std::string erase_line();

    /**
     * @brief Erases screen from cursor to end of the line.
     *
     * @return ANSI Escape Code.
     */
    static std::string erase_to_end_in_line();

    /**
     * @brief Erases screen from cursor to beginning of the line.
     *
     * @return ANSI Escape Code.
     */
    static std::string erase_to_beginning_in_line();
};

#endif