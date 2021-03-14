#include "FileUtils.h"
#include "Lexer.h"
#include "Parser.h"

#include <unicode/locid.h>
#include <unicode/brkiter.h>
#include <unicode/ustream.h>

namespace fs = std::filesystem;

int main() {
  const auto mainFile = fs::current_path().append("main.cff");
  const auto main = CFF::load(mainFile);

  const auto tokens = CFF::Lexer::lex(main);

  std::cout << "Tokens:" << std::endl;

  std::size_t i = 0;
  for(const auto& token : tokens) {
    std::cout << "\t" << i++ << ": " << token.getName() << " raw token: " << token.raw << std::endl;
  }
  CFF::Parser::parse(tokens);

  return 0;
}
