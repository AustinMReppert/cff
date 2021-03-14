#ifndef CFF_NUMLITERAL_H
#define CFF_NUMLITERAL_H

#include "Expression.h"

namespace CFF {

  class NumLiteral : public Expression {
  public:
    NumLiteral(std::shared_ptr<Token> token, double val);
    double val;

  };

}


#endif //CFF_NUMLITERAL_H
