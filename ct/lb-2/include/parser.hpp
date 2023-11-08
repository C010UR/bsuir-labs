#pragma once

#include "keywords.hpp"
#include "lexer.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Parser
{
  public:
    void parse(std::string code)
    {
        Lexer lexer(code);

        std::vector<Token> tokens;
        Token              token;

        do {
            token = lexer.getNextToken();
            tokens.push_back(token);
        } while (token.type != TokenType::None);

        int bracketsOpen = 0;

        for (int i = 0; i < (int)tokens.size(); i++) {
            switch (tokens[i].type) {
                case TokenType::OperatorPlus:
                case TokenType::OperatorMultiply:
                case TokenType::OperatorDivide:
                case TokenType::OperatorSubtract:
                case TokenType::OperatorEqual:
                case TokenType::OperatorNotEqual:
                case TokenType::OperatorGreater:
                case TokenType::OperatorLess:
                case TokenType::Identifier:
                case TokenType::Number:
                case TokenType::Literal:
                case TokenType::Colon:
                    break;
                case TokenType::OperatorAssignment:
                    if (i == 0 || i + 1 == (int)tokens.size() || tokens[i - 1].type != TokenType::Identifier
                        || (tokens[i + 1].type != TokenType::Number && tokens[i + 1].type != TokenType::BracketOpen
                            && tokens[i + 1].type != TokenType::Identifier)) {
                        std::cout << "Unexpected token appeared (" << tokens[i].lexeme << ")" << std::endl;
                        return;
                    }

                    break;
                case TokenType::BracketOpen:
                    bracketsOpen++;
                    break;
                case TokenType::BracketClose:
                    bracketsOpen--;
                    break;
                case TokenType::None:
                    break;
                default:
                    std::cout << "Unexpected token appeared (" << tokens[i].lexeme << ")" << std::endl;

                    return;
            }
        }

        if (bracketsOpen > 0) {
            std::cout << "Brackets not closed" << std::endl;

            return;
        }

        if (bracketsOpen < 0) {
            std::cout << "Brackets not open" << std::endl;

            return;
        }

        std::cout << "Everything is fine" << std::endl;
    }
};