#ifndef CFF_ASSIGNMENT_H
#define CFF_ASSIGNMENT_H


#include "Statement.h"

namespace CFF {

  class Assignment : public Statement {
  public:
    void accept(ASTNodeVisitor& visitor) override;

    Assignment(const icu::UnicodeString& name, std::shared_ptr<ASTNode> value);

    icu::UnicodeString name;
    std::shared_ptr<ASTNode> value;
  };

}


#endif