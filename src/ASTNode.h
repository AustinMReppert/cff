#ifndef CFF_ASTNODE_H
#define CFF_ASTNODE_H

#include <memory>
#include "Token.h"

namespace CFF {

  class ASTNode {
  private:
    std::shared_ptr<Token> token;
  public:
  public: ASTNode(std::shared_ptr<Token> token);
    virtual ~ASTNode() = default;
    std::shared_ptr<Token> getToken();
  };

}


#endif //CFF_ASTNODE_H
