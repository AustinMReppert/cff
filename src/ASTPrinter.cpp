#include "ASTPrinter.h"

#include <iostream>
#include <unicode/ustream.h>

void CFF::ASTPrinter::visitBinaryExpression(CFF::BinaryExpression& node) {
  std::cout << "(";
  node.getLeft()->accept(*this);
  std::cout << " " << node.getToken()->raw << " ";
  node.getRight()->accept(*this);
  std::cout << ")";
}

void CFF::ASTPrinter::visitNumLiteral(CFF::NumLiteral& node) {
  std::cout << node.getToken()->raw;
}

void CFF::ASTPrinter::print(CFF::AST& ast) {
  for(const std::shared_ptr<ASTNode>& node : ast.getChildren())
    node->accept(*this);
}
