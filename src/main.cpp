#include "utils/FileUtils.h"
#include "Lexer.h"
#include "Parser.h"
#include "BinaryExpression.h"
#include "NumLiteral.h"

#include <unicode/locid.h>
#include <unicode/brkiter.h>
#include <unicode/ustream.h>

namespace fs = std::filesystem;

int main() {
  const auto mainFile = fs::current_path().append("main.cff");
  const auto main = CFF::load(mainFile);

  const auto tokens = CFF::Lexer::lex(main);

  std::cout << "Tokens:" << std::endl;

  std::size_t tokenIndex = 0;
  for(const auto& token : tokens) {
    std::cout << "\t" << tokenIndex++ << ": " << token->getName() << " raw token: " << token->raw << std::endl;
  }


  CFF::Parser parser(tokens);
  CFF::AST ast = parser.parse();
  for(std::size_t i = 0; i < ast.getChildren()->size(); ++i) {
    std::shared_ptr<CFF::ASTNode> node = (*ast.getChildren())[i];
    if(CFF::BinaryExpression* a = dynamic_cast<CFF::BinaryExpression*>(node.get())) {
      std::cout << "bin expr" << std::endl;
    } else if(CFF::Expression* a = dynamic_cast<CFF::Expression*>(node.get())) {
      std::cout << "expr" << std::endl;
    } else if(CFF::NumLiteral* a = dynamic_cast<CFF::NumLiteral*>(node.get())) {
      std::cout << "lit" << std::endl;
      std::cout << a->val << std::endl;
    }
  }

  CFF::BinaryExpression* x = dynamic_cast<CFF::BinaryExpression *>((*ast.getChildren())[0].get());
  CFF::BinaryExpression* y = dynamic_cast<CFF::BinaryExpression *>(x->getRight().get());
  CFF::NumLiteral* z = dynamic_cast<CFF::NumLiteral *>(y->getRight().get());
  std::cout << z->getToken()->raw << std::endl;
  return 0;
}
