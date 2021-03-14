#ifndef CFF_PARSER_H
#define CFF_PARSER_H

#include "Token.h"

#include <vector>
#include <set>

namespace CFF {

  class Parser {

  public:
    static void parse(const std::vector<Token>& tokens);
    static void expression(const std::vector<Token>& tokens, size_t& cur);
    static void term(const std::vector<Token>& tokens, size_t& cur);
    static void error(const std::vector<Token>& tokens, size_t& cur);
    static void advance(const std::vector<Token>& tokens, size_t& cur);
    static Token peek(const std::vector<Token>& tokens, size_t& cur);
    static bool matches(const std::vector<Token>& tokens, size_t cur, const std::set<TokenType>& tokenTypes);

  };

}

#endif // CFF_PARSER_H