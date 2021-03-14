#include "BinaryExpression.h"

CFF::BinaryExpression::BinaryExpression(std::shared_ptr<Token> op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) :Expression(op) {
  this->op = op;
  this->left = left;
  this->right = right;
}

const std::shared_ptr<CFF::Expression>& CFF::BinaryExpression::getLeft() const {
  return left;
}

const std::shared_ptr<CFF::Expression>& CFF::BinaryExpression::getRight() const {
  return right;
}
