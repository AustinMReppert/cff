#ifndef CFF_ASTNODEVISITOR_H
#define CFF_ASTNODEVISITOR_H

namespace CFF {

  class BinaryExpression;
  class NumLiteral;

  class ASTNodeVisitor {

  public:
    virtual void visitBinaryExpression(CFF::BinaryExpression& node) = 0;
    virtual void visitNumLiteral(CFF::NumLiteral& node) = 0;

  };

}

#endif //CFF_ASTNODEVISITOR_H
