#ifndef CFF_STRINGUTILS_H
#define CFF_STRINGUTILS_H

#include <unicode/umachine.h>

#include <iostream>
#include <string>

namespace CFF {

  bool isWhitespace(UChar32 cp);

  bool isNewline(UChar32 cp);

  bool isNumeric(UChar32 cp);

  bool isAlphabetic(UChar32 cp);

  bool isAlphanumeric(UChar32 cp);
}

#endif // CFF_STRINGUTILS_H
