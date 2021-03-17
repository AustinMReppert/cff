#include "utils/FileUtils.h"

#include "Lexer.h"
#include "Parser.h"
#include "ASTPrinter.h"

#include <unicode/locid.h>
#include <unicode/brkiter.h>
#include <unicode/ustream.h>

namespace fs = std::filesystem;

int main() {
  const auto mainFile = fs::current_path().append("main.cff");
  const auto main = CFF::load(mainFile);

  CFF::Lexer lexer(main);
  auto tokens = lexer.lex();

  std::cout << "Tokens:" << std::endl;
  std::size_t tokenIndex = 0;
  for(const auto& token : tokens) {
    std::cout << "\t" << tokenIndex++ << ": " << token->getName() << " raw token: " << token->raw << std::endl;
  }

  CFF::Parser parser(&tokens);
  CFF::AST ast = parser.parse();

  CFF::ASTPrinter astPrinter;
  astPrinter.print(ast);

  return 0;
}
