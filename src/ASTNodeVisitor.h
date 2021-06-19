#ifndef CFF_ASTNODEVISITOR_H
#define CFF_ASTNODEVISITOR_H

namespace CFF {

  class BinaryExpression;
  class Statement;
  class NumLiteral;
  class Assignment;
  class StatementList;

  class ASTNodeVisitor {

  public:
    virtual void visitBinaryExpression(CFF::BinaryExpression& node) = 0;
    virtual void visitStatement(CFF::Statement& node) = 0;
    virtual void visitNumLiteral(CFF::NumLiteral& node) = 0;
    virtual void visitAssignment(CFF::Assignment& node) = 0;
    virtual void visitStatementList(CFF::StatementList& node) = 0;

  };

}

#endif
