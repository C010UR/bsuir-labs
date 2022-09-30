#ifndef READ_HPP
#define READ_HPP

#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <functional>
#include <string>
#include <vector>
#include <random>
#include "console.hpp"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old);         /* grab old terminal i/o settings */
    current = old;              /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo)
    {
        current.c_lflag |= ECHO; /* set echo mode */
    }
    else
    {
        current.c_lflag &= ~ECHO; /* set no echo mode */
    }
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}
#endif

class Get
{
private:
    template <typename T>
    struct History
    {
        T value;
        unsigned state;
    };

public:
    /**
     * @brief Generates random number of type T.
     *
     * @tparam T scalar type
     * @param min
     * @param max
     * @return Random number.
     */
    template <typename T>
    static T random_scalar(T min, T max)
    {
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<T> distr(min, max);
        return distr(generator);
    }

    /**
     * @brief Generates random number of type T and outputs it to the terminal.
     *
     * @tparam T scalar type
     * @param min
     * @param max
     * @param message
     * @return Random number.
     */
    template <typename T>
    static T random_scalar(T min, T max, std::string message)
    {
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<T> distr(min, max);
        T rand = distr(generator);
        std::cout
            << Console::text(Console::Style::green, message)
            << ": " << rand
            << std::endl;
        return rand;
    }

    /**
     * @brief Reads scalar value of type T from stdin.
     *
     * @tparam T scalar type
     * @param label
     * @return Read value.
     */
    template <typename T>
    static T stdin_scalar(std::string message)
    {
        T value;
        std::cout
            << Console::text(Console::Style::green, message)
            << ": "
            << Console::set_style(Console::Style::yellow);
        std::cin >> value;
        std::cout << Console::reset_style();
        return value;
    }

    /**
     * @brief Reads vector of T from stdin.
     *
     * @tparam T scalar type
     * @param label
     * @return Read vector.
     */
    template <typename T>
    static std::vector<T> stdin_vector(std::string message, std::function<T(std::string)> convert)
    {
        std::cout
            << Console::move_down(1)
            << Console::info("Usage: Input numbers separated by whitespace or comma. To stop input type ']'.")
            << Console::move_up_column_reset(1);

        std::cout
            << Console::text(Console::Style::green, message)
            << ": [";

        std::vector<T> arr;
        std::vector<Get::History<char>> char_history;
        std::vector<Get::History<std::string>> history;

        char c;
        std::string val;

        enum
        {
            positive_number,
            negative_number,
            possibly_negative_number,
            not_a_number
        };
        unsigned state = not_a_number;

        std::function<unsigned(unsigned)> set_state = [](unsigned state) -> unsigned
        {
            switch (state)
            {
            case positive_number:
                std::cout << Console::set_style(Console::Style::green);
                break;
            case negative_number:
                std::cout << Console::set_style(Console::Style::red);
                break;
            case not_a_number:
                std::cout << Console::set_style(Console::Style::yellow);
                break;
            default:
                std::cout << Console::reset_style();
                break;
            }
            return state;
        };

        while ((c = getch()))
        {
            if (c < 0)
            {
                continue;
            }

            if (c == '\027' || c == '\177')
            {
                if (!history.empty())
                {
                    std::cout << Console::move_left(val.size() + 2) << Console::erase_to_end_in_line();

                    val = std::string(history.back().value);
                    char_history.resize(char_history.size() - history.back().value.length());
                    state = set_state(history.back().state);
                    history.pop_back();
                    arr.pop_back();
                }
                else if (!val.empty())
                {
                    std::cout << Console::move_left(val.size()) << Console::erase_to_end_in_line();

                    state = set_state(20);
                    char_history.clear();
                    val = "";
                }
                continue;
            }
            if (c == '\010')
            {
                if (!val.empty())
                {
                    std::cout << Console::move_left(val.size()) << Console::erase_to_end_in_line();

                    val.pop_back();
                    char_history.pop_back();

                    state = set_state(char_history.back().state);
                    std::cout << val;
                }
                else if (!history.empty())
                {
                    val = std::string(history.back().value);
                    state = set_state(history.back().state);
                    history.pop_back();
                    arr.pop_back();
                    std::cout << Console::move_left(2) << Console::erase_to_end_in_line();
                }
                else
                {
                    std::cout << Console::move_right(1);
                    state = set_state(20);
                }
                continue;
            }

            if (isspace(c) || c == ',' || (unsigned)c < 32)
            {
                if (val.empty())
                {
                    std::cout << Console::move_left(2) << Console::reset_style() << "]" << std::endl;
                    break;
                }
                try
                {
                    arr.push_back(convert(val));
                    history.push_back({val, state});
                }
                catch (const std::exception &e)
                {
                    std::cout
                        << Console::reset_style() << "]" << std::endl
                        << Console::erase_to_end_in_line()
                        << Console::error("'" + val + "' can not be converted.")
                        << std::endl;
                    exit(EXIT_FAILURE);
                }
                std::cout << Console::reset_style() << ", ";
                val = "";
                continue;
            }
            if (c == ']')
            {
                if (!val.empty())
                {
                    try
                    {
                        arr.push_back(convert(val));
                    }
                    catch (const std::exception &e)
                    {
                        std::cout
                            << Console::reset_style() << "]" << std::endl
                            << Console::erase_to_end_in_line()
                            << Console::error("'" + val + "' can not be converted.")
                            << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
                else if (!arr.empty())
                {
                    std::cout << Console::move_left(2);
                }
                std::cout << Console::reset_style() << "]" << std::endl;
                break;
            }

            if (val.empty())
            {
                if (c == '-')
                    state = set_state(possibly_negative_number);
                else if (isdigit(c))
                    state = set_state(positive_number);
                else
                    state = set_state(not_a_number);

                val += c;
                char_history.push_back({c, state});

                std::cout << c;
                continue;
            }

            if (state == possibly_negative_number && isdigit(c))
            {
                if (isdigit(c))
                {
                    std::cout << Console::move_left(1);
                    state = set_state(negative_number);
                    std::cout << "-";
                }
                else
                {
                    state = set_state(not_a_number);
                }

                val += c;
                char_history.push_back({c, state});

                std::cout << c;
                continue;
            }

            if ((state == negative_number || state == positive_number) && c == '.')
            {
                val += c;
                char_history.push_back({c, state});

                std::cout << Console::reset_style();
                std::cout << c;
                std::cout << Console::set_style(state == positive_number ? Console::Style::green : Console::Style::red);
                continue;
            }

            if ((state == negative_number || state == positive_number) && !isdigit(c))
            {
                std::cout << Console::move_left(val.size());

                state = set_state(not_a_number);
                val += c;
                char_history.push_back({c, state});

                std::cout << Console::set_style(Console::Style::yellow);
                std::cout << val;
                continue;
            }

            char_history.push_back({c, state});
            val += c;
            std::cout << c;
        }

        std::cout << Console::erase_to_end_in_line();
        return arr;
    }
};

#endif