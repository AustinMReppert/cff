#ifndef CFF_PARSER_H
#define CFF_PARSER_H

#include "Token.h"
#include "ASTNode.h"
#include "AST.h"

#include <vector>
#include <set>
#include <memory>

namespace CFF {

  class Parser {

  private:
    std::vector<std::shared_ptr<Token>>* tokens;
    std::size_t cur;
  public:
    explicit Parser(std::vector<std::shared_ptr<Token>>* tokens);
    std::shared_ptr<CFF::StatementList> parse();
    std::shared_ptr<CFF::Statement> declaration();
    std::shared_ptr<CFF::ASTNode> expression();
    std::shared_ptr<CFF::ASTNode> term();
    std::shared_ptr<CFF::ASTNode> factor();
    void error();
    void advance();
    std::shared_ptr<CFF::Token> peek();
    bool matches(size_t index, const std::set<TokenType>& tokenTypes);
    bool matches(const std::set<TokenType>& tokenTypes);

  };

}

#endif // CFF_PARSER_H