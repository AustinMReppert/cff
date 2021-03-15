#ifndef CFF_LEXER_H
#define CFF_LEXER_H

#include "Token.h"
#include "utils/FileUtils.h"

#include <unicode/unistr.h>

#include <string_view>
#include <vector>
#include <unicode/schriter.h>

namespace CFF {

  class Lexer {

  private:
    icu::UnicodeString lexemes;
    icu::StringCharacterIterator itr{icu::UnicodeString()};
    std::size_t line{};
    std::size_t column{};
    std::size_t start{};

    void appendToken(TokenType tokenType, std::vector<std::shared_ptr<CFF::Token>>& tokens);

  public:
    std::vector<std::shared_ptr<CFF::Token>> lex();
    explicit Lexer(icu::UnicodeString lexemes);
  };

}


#endif //CFF_LEXER_H
