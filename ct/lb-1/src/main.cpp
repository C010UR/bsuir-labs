    #include "keywords.hpp"
    #include "lexer.hpp"

    #include <iostream>
    #include <string>
    #include <unordered_set>

    int main()
    {
        std::string code =
            "y = 2.2"
            "x = 1"
            "if x != 2:"
            "    z = 2 / x * 2"
            "if x == 1:"
            "    print(\"x is 1.\")";

        Lexer lexer(code);

        Token token = lexer.getNextToken();
        while (token.type != TokenType::None) {
            std::string tokenType;

            switch (token.type) {
                case TokenType::None:
                    tokenType = "Unknown";
                    break;
                case TokenType::OperatorPlus:
                    tokenType = "Plus";
                    break;
                case TokenType::OperatorMultiply:
                    tokenType = "Multiply";
                    break;
                case TokenType::OperatorDivide:
                    tokenType = "Divide";
                    break;
                case TokenType::OperatorSubtract:
                    tokenType = "Subtract";
                    break;
                case TokenType::OperatorEqual:
                    tokenType = "Equal";
                    break;
                case TokenType::OperatorNotEqual:
                    tokenType = "Not Equal";
                    break;
                case TokenType::OperatorGreater:
                    tokenType = "Greater";
                    break;
                case TokenType::OperatorLess:
                    tokenType = "Less";
                    break;
                case TokenType::OperatorAssignment:
                    tokenType = "Assignment";
                    break;
                case TokenType::Identifier:
                    tokenType = "Identifier";
                    break;
                case TokenType::Number:
                    tokenType = "Number";
                    break;
                case TokenType::Literal:
                    tokenType = "Literal";
                    break;
                case TokenType::Colon:
                    tokenType = "Colon";
                    break;
                case TokenType::BracketOpen:
                    tokenType = "Open Bracket";
                    break;
                case TokenType::BracketClose:
                    tokenType = "Closing Bracket";
                    break;
            }

            std::string isKeyword =
                (token.type == TokenType::Identifier && keywords.count(token.lexeme) > 0) ? " (Keyword)" : "";

            std::cout << "Token: \""
                    << "\033[36m" << token.lexeme << "\033[0m"
                    << "\" (Type: "
                    << "\033[33m" << tokenType << "\033[0m"
                    << ")" << isKeyword << std::endl;

            token = lexer.getNextToken();
        }

        return 0;
    }
