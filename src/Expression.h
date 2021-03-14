#ifndef CFF_EXPRESSION_H
#define CFF_EXPRESSION_H

#include "ASTNode.h"

namespace CFF {

  class Expression : public ASTNode {
  public:
    Expression(std::shared_ptr<Token> token);
  };

}


#endif //CFF_EXPRESSION_H
