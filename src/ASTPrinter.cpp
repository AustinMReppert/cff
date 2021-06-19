#include "ASTPrinter.h"

#include "StatementList.h"
#include "Statement.h"

#include <iostream>
#include <unicode/ustream.h>

void CFF::ASTPrinter::visitBinaryExpression(CFF::BinaryExpression& node) {
  std::cout << indent() << "Binary Expression:" << std::endl;

  ++indentLevel;
  std::cout << indent() << "operation: " << node.getToken()->raw << std::endl;
  std::cout << indent() << "left:" << std::endl;

  ++indentLevel;
  node.getLeft()->accept(*this);
  --indentLevel;

  std::cout << indent() << "Right:" << std::endl;

  ++indentLevel;
  node.getRight()->accept(*this);
  --indentLevel;

  --indentLevel;
}

void CFF::ASTPrinter::visitNumLiteral(CFF::NumLiteral& node) {
  std::cout << indent() << "Numeric Literal:" << std::endl;

  ++indentLevel;
  std::cout << indent() << "Value: " << node.getToken()->raw << std::endl;
  --indentLevel;
}

void CFF::ASTPrinter::print(CFF::AST& ast) {
  indentLevel = 0;
  for(const std::shared_ptr<ASTNode>& node : ast.getChildren())
    node->accept(*this);
}

void CFF::ASTPrinter::visitStatement(CFF::Statement& node) {
  std::cout << "statement" << std::endl;
}

void CFF::ASTPrinter::visitStatementList(CFF::StatementList& node) {
  for(const auto& statement : node.getStatements()) {
    statement->accept(*this);
  }
}

void CFF::ASTPrinter::visitAssignment(CFF::Assignment& node) {
  std::cout << "Assignment:" << std::endl;

  ++indentLevel;
  std::cout << indent() << "\tName: " << node.name << std::endl;
  std::cout << indent() << "\tValue: " << std::endl;
  node.value->accept(*this);
  --indentLevel;
}

icu::UnicodeString CFF::ASTPrinter::indent() {
  return icu::UnicodeString(indentLevel, ' ', 2*indentLevel);
}
