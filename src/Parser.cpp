#include "Parser.h"

#include "BinaryExpression.h"
#include "NumLiteral.h"
#include "Assignment.h"
#include "StatementList.h"

#include <unicode/ustream.h>

#include <algorithm>
#include <functional>

std::shared_ptr<CFF::StatementList> CFF::Parser::parse() {
  auto statementList = std::make_shared<StatementList>(nullptr);
  while(cur < tokens->size() - 1) {
    std::cout << "Parsing Token: " << (*tokens)[cur]->raw << std::endl;
    auto stmnt = declaration();
    statementList->addStatement(stmnt);
  }

  return statementList;
}

std::shared_ptr<CFF::Statement> CFF::Parser::declaration() {
  if(matches({TokenType::LET})) {
    advance();
    if(matches({TokenType::IDENTIFIER})) {
      auto identifier = (*tokens)[cur];
      advance();
      std::shared_ptr<ASTNode> value = nullptr;
      if(matches({TokenType::EQUALS})) {
        advance();
        value = expression();
        if(!value) {
          std::cerr << "Missing expression after assignment." << std::endl;
          error();
        }
      }
      if(matches({TokenType::SEMICOLON})) {
        advance();
        return dynamic_pointer_cast<Statement>(std::make_shared<Assignment>(identifier->raw, value));
      } else {
        std::cerr << "Invalid let statement: expected semicolon." << std::endl;
        error();
      }
    } else {
      std::cerr << "Invalid let statement: expected identifier." << std::endl;
      error();
    }
  } else {
    error();
  }
}

std::shared_ptr<CFF::ASTNode> CFF::Parser::expression() {
  auto left = term();
  if(matches({TokenType::PLUS, TokenType::MINUS})) {
    auto op = (*tokens)[cur];
    advance();
    auto right = expression();
    return dynamic_pointer_cast<ASTNode>(std::make_shared<BinaryExpression>(op, left, right));
  } else {
    return left;
  }
}

std::shared_ptr<CFF::ASTNode> CFF::Parser::term() {
  auto left = factor();
  if(matches({TokenType::ASTERISK, TokenType::SLASH})) {
    auto op = (*tokens)[cur];
    advance();
    auto right = term();
    return dynamic_pointer_cast<ASTNode>(std::make_shared<BinaryExpression>(op, left, right));
  } else {
    return left;
  }
}

std::shared_ptr<CFF::ASTNode> CFF::Parser::factor() {
  if(matches({TokenType::LEFT_PARENTHESIS})) {
    advance();
    auto expr = expression();
    if(matches({TokenType::RIGHT_PARENTHESIS})) {
      advance();
      return expr;
    }
    else error();
  } else if(matches({TokenType::NUM})) {
    std::shared_ptr<Token> literal = (*tokens)[cur];
    advance();
    return dynamic_pointer_cast<ASTNode>(std::make_shared<NumLiteral>(literal, 4.0));
  } else {
    error();
  }
  return nullptr;
}

// TODO: Fix
void CFF::Parser::error() {
  std::cerr << "Error parsing: " << ((cur < tokens->size()) ? (*tokens)[cur]->getName() : "EOF") << " at token #" << cur << std::endl;
  throw std::runtime_error("Invalid expression");
}

void CFF::Parser::advance() {
  ++cur;
  if(cur >= tokens->size())
    error();
}

std::shared_ptr<CFF::Token> CFF::Parser::peek() {
  return (*tokens)[cur + 1];
}

bool CFF::Parser::matches(size_t index, const std::set<TokenType>& tokenTypes) {
  return std::ranges::any_of(tokenTypes, [this, index](TokenType f) { return f == (*this->tokens)[index]->type; });
}

bool CFF::Parser::matches(const std::set<TokenType>& tokenTypes) {
  return matches(cur, tokenTypes);
}

CFF::Parser::Parser(std::vector<std::shared_ptr<Token>>* tokens) {
  this->tokens = tokens;
  cur = 0;
}
