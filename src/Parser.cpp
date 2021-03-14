#include "Parser.h"

#include <unicode/ustream.h>

#include <algorithm>
#include <functional>

void CFF::Parser::parse(const std::vector<Token>& tokens) {
  std::size_t i = 0;
  while(i < tokens.size() - 1) {
    std::cout << "Parsing Token: " << tokens[i].raw << std::endl;
    expression(tokens, i);
  }
}

void CFF::Parser::expression(const std::vector<Token>& tokens, size_t& cur) {
  if(matches(tokens, cur, {TokenType::LEFT_PARENTHESIS})) {
    std::cout << "a" << std::endl;
    advance(tokens, cur);
    expression(tokens, cur);
    if(matches(tokens, cur, {TokenType::RIGHT_PARENTHESIS}))
      advance(tokens, cur);
    else
      error(tokens, cur);
  } else if (matches(tokens, cur, {TokenType::MINUS})) {
    std::cout << "b" << std::endl;
    advance(tokens, cur);
    expression(tokens, cur);
  } else if (matches(tokens, cur, {TokenType::NUM})) {
    std::cout << "c" << std::endl;
    term(tokens, cur);
  } else {
    std::cout << "d" << std::endl;
    expression(tokens, cur);
    if(matches(tokens, cur, {TokenType::PLUS, TokenType::MINUS}))
      advance(tokens, cur);
    else
      error(tokens, cur);
    expression(tokens, cur);
  }
}

void CFF::Parser::term(const std::vector<Token>& tokens, size_t& cur) {
  if(matches(tokens, cur, {TokenType::NUM}) && matches(tokens, cur + 1, {TokenType::ASTERISK, TokenType ::SLASH})) {
    advance(tokens, cur);
    advance(tokens, cur);
    term(tokens, cur);
  } else if(matches(tokens, cur, {TokenType::NUM})) {
    advance(tokens, cur);
  } else {
    error(tokens, cur);
  }
}

void CFF::Parser::error(const std::vector<Token>& tokens, size_t& cur) {
  std::cout << "error parsing: " << ((cur < tokens.size()) ? tokens[cur].getName() : "EOF") << " at " << cur
            << std::endl;
  throw std::runtime_error("invalid expression");
}

void CFF::Parser::advance(const std::vector<Token>& tokens, size_t& cur) {
  ++cur;
  if(cur >= tokens.size())
    error(tokens, cur);
}

CFF::Token CFF::Parser::peek(const std::vector<Token>& tokens, size_t& cur) {
  return tokens[cur + 1];
}

bool CFF::Parser::matches(const std::vector<Token>& tokens, size_t cur, const std::set<TokenType>& tokenTypes) {
  return std::ranges::any_of(tokenTypes, [tokens, cur](TokenType f) { return f == tokens[cur].type; });
}

