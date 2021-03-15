#ifndef CFF_PARSER_H
#define CFF_PARSER_H

#include "Token.h"

#include <vector>
#include <set>
#include <memory>

#include "AST.h"
#include "Expression.h"

namespace CFF {

  class Parser {

  private:
    std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens;
    std::size_t cur;
  public:
    explicit Parser(std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);
    CFF::AST parse();
    std::shared_ptr<CFF::Expression> expression();
    std::shared_ptr<CFF::Expression> term();
    std::shared_ptr<CFF::Expression> factor();
    void error();
    void advance();
    std::shared_ptr<CFF::Token> peek();
    bool matches(size_t index, const std::set<TokenType>& tokenTypes);

  };

}

#endif // CFF_PARSER_H