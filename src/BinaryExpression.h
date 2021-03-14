#ifndef CFF_BINARYEXPRESSION_H
#define CFF_BINARYEXPRESSION_H

#include <memory>
#include "Expression.h"
#include "Token.h"

namespace CFF {

  class BinaryExpression : public Expression {
  private:
    std::shared_ptr<Token> op;
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

  public:
    BinaryExpression(std::shared_ptr<Token> op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);

    const std::shared_ptr<Expression>& getLeft() const;

    const std::shared_ptr<Expression>& getRight() const;
  };

}


#endif //CFF_BINARYEXPRESSION_H
