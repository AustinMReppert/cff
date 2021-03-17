#ifndef CFF_BINARYEXPRESSION_H
#define CFF_BINARYEXPRESSION_H

#include "ASTNode.h"

#include <memory>

namespace CFF {

  class BinaryExpression : public ASTNode {
  private:
    std::shared_ptr<Token> op;
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;

  public:
    BinaryExpression(std::shared_ptr<Token> op, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right);

    std::shared_ptr<ASTNode>& getLeft();

    std::shared_ptr<ASTNode>& getRight();

    void accept(CFF::ASTNodeVisitor& visitor) override;

  };

}


#endif //CFF_BINARYEXPRESSION_H
