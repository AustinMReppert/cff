#include "BinaryExpression.h"

CFF::BinaryExpression::BinaryExpression(std::shared_ptr<Token> op, std::shared_ptr<ASTNode> left,
                                        std::shared_ptr<ASTNode> right) : ASTNode(op) {
  this->op = op;
  this->left = left;
  this->right = right;
}

std::shared_ptr<CFF::ASTNode>& CFF::BinaryExpression::getLeft() {
  return left;
}

std::shared_ptr<CFF::ASTNode>& CFF::BinaryExpression::getRight() {
  return right;
}

void CFF::BinaryExpression::accept(CFF::ASTNodeVisitor& visitor) {
  visitor.visitBinaryExpression(*this);
}
