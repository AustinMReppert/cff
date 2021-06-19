#ifndef CFF_ASTPRINTER_H
#define CFF_ASTPRINTER_H

#include "ASTNodeVisitor.h"
#include "BinaryExpression.h"
#include "Statement.h"
#include "Assignment.h"
#include "NumLiteral.h"
#include "AST.h"

namespace CFF {

  class ASTPrinter : public ASTNodeVisitor {
  private:
    std::size_t indentLevel = 0;
  public:
    void visitBinaryExpression(CFF::BinaryExpression& node) override;
    void visitStatement(CFF::Statement& node) override;
    void visitNumLiteral(CFF::NumLiteral& node) override;
    void visitAssignment(CFF::Assignment& node) override;
    void visitStatementList(CFF::StatementList& node) override;

    void print(CFF::AST& ast);

    icu::UnicodeString indent();
  };

}


#endif //CFF_ASTPRINTER_H
