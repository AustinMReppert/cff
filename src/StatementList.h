#ifndef CFF_STATEMENTLIST_H
#define CFF_STATEMENTLIST_H

#include <vector>
#include "ASTNode.h"

namespace CFF {

  class StatementList : public ASTNode {

    std::vector<std::shared_ptr<Statement>> statements;

  public:
    StatementList(std::shared_ptr<Token> token);
    void accept(ASTNodeVisitor& visitor) override;
    void addStatement(std::shared_ptr<Statement>& statement);
    std::vector<std::shared_ptr<Statement>> getStatements();
  };

}

#endif