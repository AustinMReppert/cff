#ifndef CFF_ASTNODE_H
#define CFF_ASTNODE_H

#include "ASTNodeVisitor.h"
#include "Token.h"

#include <memory>

namespace CFF {

  class ASTNode {
  private:
    std::shared_ptr<Token> token;
  public:
    ASTNode(std::shared_ptr<Token> token);

    virtual void accept(CFF::ASTNodeVisitor& visitor) = 0;
    std::shared_ptr<Token> getToken();

  };

}


#endif //CFF_ASTNODE_H
