#ifndef CFF_LEXER_H
#define CFF_LEXER_H

#include "Token.h"
#include "utils/FileUtils.h"

#include <unicode/unistr.h>

#include <string_view>
#include <vector>

namespace CFF {

  class Lexer {

  public:
    static std::vector<std::shared_ptr<CFF::Token>> lex(const icu::UnicodeString& lexemes);

  };

}


#endif //CFF_LEXER_H
