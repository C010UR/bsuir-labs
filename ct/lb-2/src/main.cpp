    #include "keywords.hpp"
    #include "lexer.hpp"
    #include "parser.hpp"

    #include <iostream>
    #include <string>
    #include <unordered_set>

    int main()
    {
        std::string code =
            "= y = 2.2"
            "x = 1"
            "z = x + (0) + (0)"
            "if x != 2:"
            "    z = 2 / x * 2"
            "if x == 1:"
            "    print(\"x is 1.\")"
            "    print(z)";

        Parser parser;

        parser.parse(code);

        return 0;
    }
