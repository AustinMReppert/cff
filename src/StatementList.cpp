#include "StatementList.h"

void CFF::StatementList::accept(CFF::ASTNodeVisitor& visitor) {
  visitor.visitStatementList(*this);
}

void CFF::StatementList::addStatement(std::shared_ptr<Statement>& statement) {
  statements.push_back(statement);
}

CFF::StatementList::StatementList(std::shared_ptr<Token> token) : ASTNode(token) {
}

std::vector<std::shared_ptr<CFF::Statement>> CFF::StatementList::getStatements() {
  return statements;
}
