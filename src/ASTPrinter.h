#ifndef CFF_ASTPRINTER_H
#define CFF_ASTPRINTER_H

#include "ASTNodeVisitor.h"
#include "BinaryExpression.h"
#include "NumLiteral.h"
#include "AST.h"

namespace CFF {

  class ASTPrinter : public ASTNodeVisitor {
  public:
    void visitBinaryExpression(CFF::BinaryExpression& node) override;

    void visitNumLiteral(CFF::NumLiteral& node) override;

    void print(CFF::AST& ast);

  };

}


#endif //CFF_ASTPRINTER_H
