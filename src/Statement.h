#ifndef CFF_STATEMENT_H
#define CFF_STATEMENT_H

#include "ASTNode.h"

namespace CFF {

  class Statement : public ASTNode {

  public:
    void accept(ASTNodeVisitor& visitor) override;
    Statement(std::shared_ptr<Token> token);
  };

}

#endif