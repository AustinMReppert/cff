#include "Statement.h"

void CFF::Statement::accept(CFF::ASTNodeVisitor& visitor) {
  visitor.visitStatement(*this);
}

CFF::Statement::Statement(std::shared_ptr<Token> token) : ASTNode(token) {
}
