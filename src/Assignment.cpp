#include "Assignment.h"

CFF::Assignment::Assignment(const icu::UnicodeString& name, std::shared_ptr<ASTNode> value)
    : Statement(std::shared_ptr<Token>()) {
  this->name = name;
  this-> value = value;
}

void CFF::Assignment::accept(CFF::ASTNodeVisitor& visitor) {
  visitor.visitAssignment(*this);
}
