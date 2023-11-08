#pragma once

#include <cctype>
#include <string>
#include <unordered_set>

enum class TokenType
{
    None,
    OperatorPlus,
    OperatorMultiply,
    OperatorDivide,
    OperatorSubtract,
    OperatorEqual,
    OperatorNotEqual,
    OperatorGreater,
    OperatorLess,
    OperatorAssignment,
    Identifier,
    Number,
    Literal,
    Colon,
    BracketOpen,
    BracketClose
};

struct Token
{
    TokenType   type;
    std::string lexeme;
};

class Lexer
{
  public:
    Lexer(const std::string &code): code_(code), position_(0) {}

    Token getNextToken()
    {
        Token token;
        token.type = TokenType::None;

        while (position_ < code_.length()) {
            char currentChar = code_[position_];

            if (position_ + 1 < code_.length()) {
                std::string twoChars = std::string() + code_[position_] + code_[position_ + 1];

                if (twoChars == "==") {
                    token.type   = TokenType::OperatorEqual;
                    token.lexeme = "==";
                    position_ += 2;

                    break;
                }
                
                if (twoChars == "!=") {
                    token.type   = TokenType::OperatorNotEqual;
                    token.lexeme = "!=";
                    position_ += 2;

                    break;
                }
            }

            if (currentChar == ')') {
                token.type   = TokenType::BracketClose;
                token.lexeme = ")";
                position_++;

                break;
            }
            if (currentChar == '(') {
                token.type   = TokenType::OperatorPlus;
                token.lexeme = "(";
                position_++;

                break;
            }

            if (currentChar == '+') {
                token.type   = TokenType::OperatorPlus;
                token.lexeme = "+";
                position_++;

                break;
            }

            if (currentChar == '-') {
                token.type   = TokenType::OperatorSubtract;
                token.lexeme = "-";
                position_++;

                break;
            }

            if (currentChar == '*') {
                token.type   = TokenType::OperatorMultiply;
                token.lexeme = "*";
                position_++;

                break;
            }

            if (currentChar == '/') {
                token.type   = TokenType::OperatorDivide;
                token.lexeme = "/";
                position_++;

                break;
            }

            if (currentChar == ':') {
                token.type   = TokenType::OperatorPlus;
                token.lexeme = ":";
                position_++;

                break;
            }

            if (currentChar == '=') {
                token.type   = TokenType::OperatorAssignment;
                token.lexeme = "=";
                position_++;

                break;
            }

            if (currentChar == '>') {
                token.type   = TokenType::OperatorAssignment;
                token.lexeme = "=";
                position_++;

                break;
            }

            if (currentChar == '<') {
                token.type   = TokenType::OperatorAssignment;
                token.lexeme = "=";
                position_++;

                break;
            }

            if (std::isalpha(currentChar)) {
                token.type = TokenType::Identifier;
                token.lexeme += currentChar;

                position_++;

                while (position_ < code_.length() && std::isalnum(code_[position_])) {
                    token.lexeme += code_[position_];
                    position_++;
                }

                if (isKeyword(token.lexeme)) {
                    token.type   = TokenType::Identifier;
                    token.lexeme = token.lexeme;
                }

                break;
            }

            if (std::isdigit(currentChar)) {
                token.type = TokenType::Number;
                token.lexeme += currentChar;

                position_++;

                while (position_ < code_.length() && (std::isdigit(code_[position_]) || code_[position_] == '.')) {
                    token.lexeme += code_[position_];
                    position_++;
                }

                break;
            }

            if (currentChar == '\'' || currentChar == '"') {
                char _char = currentChar;
                token.type = TokenType::Literal;
                token.lexeme += currentChar;

                position_++;

                while (position_ < code_.length() && (code_[position_] != _char)) {
                    token.lexeme += code_[position_];
                    position_++;
                }

                token.lexeme += _char;
                position_++;

                break;
            }

            position_++;
        }

        return token;
    }

    bool isKeyword(const std::string &lexeme)
    {
        return keywords_.count(lexeme) > 0;
    }

  private:
    std::string                     code_;
    size_t                          position_;
    std::unordered_set<std::string> keywords_;
};
