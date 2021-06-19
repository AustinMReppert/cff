#include "AST.h"

CFF::AST::AST() = default;

std::vector<std::shared_ptr<CFF::ASTNode>>& CFF::AST::getChildren() {
  return children;
}

void CFF::AST::addChild(std::shared_ptr<ASTNode> child) {
  children.emplace_back(child);
}
