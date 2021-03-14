#include "ASTNode.h"

CFF::ASTNode::ASTNode(std::shared_ptr<Token> token) {
  this->token = token;
}

std::shared_ptr<CFF::Token> CFF::ASTNode::getToken() {
  return token;
}