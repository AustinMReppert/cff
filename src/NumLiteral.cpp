#include "NumLiteral.h"

CFF::NumLiteral::NumLiteral(std::shared_ptr<Token> token, double val) : Expression(token) {
  this->val = val;
}
