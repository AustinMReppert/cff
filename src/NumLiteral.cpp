#include "NumLiteral.h"

CFF::NumLiteral::NumLiteral(std::shared_ptr<Token> token, double val) : ASTNode(token) {
  this->val = val;
}

void CFF::NumLiteral::accept(CFF::ASTNodeVisitor& visitor) {
  visitor.visitNumLiteral(*this);
}
