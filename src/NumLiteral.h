#ifndef CFF_NUMLITERAL_H
#define CFF_NUMLITERAL_H

#include "ASTNode.h"

namespace CFF {

  class NumLiteral : public ASTNode {
  public:
    NumLiteral(std::shared_ptr<Token> token, double val);

    void accept(CFF::ASTNodeVisitor& visitor) override;

    double val;

  };

}


#endif //CFF_NUMLITERAL_H
