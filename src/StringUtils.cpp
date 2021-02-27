#include "StringUtils.h"

#include <unicode/uchar.h>

bool CFF::isWhitespace(const UChar32 cp) {
  return u_isspace(cp);
}

bool CFF::isNewline(const UChar32 cp) {
  return cp == U'\n';
}

bool CFF::isNumeric(const UChar32 cp) {
  return u_isdigit(cp);
}

bool CFF::isAlphabetic(const UChar32 cp) {
  return u_isalpha(cp);
}

bool CFF::isAlphanumeric(const UChar32 cp) {
  return CFF::isNumeric(cp) || CFF::isAlphabetic(cp);
}
