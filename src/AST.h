#ifndef CFF_AST_H
#define CFF_AST_H

#include "ASTNode.h"

#include <vector>
#include <memory>

namespace CFF {

  class AST {
  private:
    std::vector<std::shared_ptr<ASTNode>> children;
  public:
    AST();
    std::vector<std::shared_ptr<ASTNode>>& getChildren();
    void addChild(std::shared_ptr<ASTNode> child);

  };

}


#endif //CFF_AST_H
