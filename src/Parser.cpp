#include "Parser.h"
#include "AST.h"
#include "Expression.h"
#include "BinaryExpression.h"
#include "NumLiteral.h"

#include <unicode/ustream.h>

#include <algorithm>
#include <functional>
#include <utility>

CFF::AST CFF::Parser::parse() {
  AST result;

  while(cur < tokens.size() - 1) {
    std::cout << "Parsing Token: " << tokens[cur]->raw << std::endl;
    result.getChildren()->emplace_back(expression());
  }
  return result;
}

std::shared_ptr<CFF::Expression> CFF::Parser::expression() {
  auto left = term();
  if(matches(cur, {TokenType::PLUS, TokenType::MINUS})) {
    auto op = tokens[cur];
    advance();
    auto right = expression();
    return std::make_shared<BinaryExpression>(op, left, right);
  } else {
    return left;
  }
}

std::shared_ptr<CFF::Expression> CFF::Parser::term() {
  auto left = factor();
  if(matches(cur, {TokenType::ASTERISK, TokenType::SLASH})) {
    auto op = tokens[cur];
    advance();
    auto right = term();
    return std::make_shared<BinaryExpression>(op, left, right);
  } else {
    return left;
  }
}

std::shared_ptr<CFF::Expression> CFF::Parser::factor() {
  if(matches(cur, {TokenType::LEFT_PARENTHESIS})) {
    advance();
    auto expr = expression();
    if(matches(cur, {TokenType::RIGHT_PARENTHESIS})) {
      advance();
      return expr;
    }
    else error();
  } else if(matches(cur, {TokenType::NUM})) {
    std::shared_ptr<Token> literal = tokens[cur];
    advance();
    return std::make_shared<NumLiteral>(literal, 4.0);
  } else {
    error();
  }
  return nullptr;
}

void CFF::Parser::error() {
  std::cout << "error parsing: " << ((cur < tokens.size()) ? tokens[cur]->getName() : "EOF") << " at " << cur
            << std::endl;
  throw std::runtime_error("invalid expression");
}

void CFF::Parser::advance() {
  ++cur;
  if(cur >= tokens.size())
    error();
}

std::shared_ptr<CFF::Token> CFF::Parser::peek() {
  return tokens[cur + 1];
}

bool CFF::Parser::matches(size_t index, const std::set<TokenType>& tokenTypes) {
  return std::ranges::any_of(tokenTypes, [this, index](TokenType f) { return f == this->tokens[index]->type; });
}

CFF::Parser::Parser(std::vector<std::shared_ptr<Token>> tokens) {
  this->tokens = std::move(tokens);
  cur = 0;
}
