#ifndef CFF_TOKEN_H
#define CFF_TOKEN_H

#include "utils/StringUtils.h"

#include <unicode/unistr.h>

#include <utility>

namespace CFF {

  enum class TokenType {
    LET,
    EQUALS,
    EQUALS_EQUALS,
    PLUS,
    PLUS_EQUALS,
    PLUS_PLUS,
    ASTERISK,
    ASTERISK_EQUALS,
    NUM,
    MINUS,
    MINUS_EQUALS,
    MINUS_MINUS,
    SLASH,
    SLASH_EQUALS,
    PERIOD,
    IDENTIFIER,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    END_OF_FILE,
    SEMICOLON
  };

  static std::string toString(const TokenType token) {
    switch(token) {
      case TokenType::LET:
        return std::string("let");
      case TokenType::EQUALS:
        return std::string("=");
      case TokenType::EQUALS_EQUALS:
        return std::string("==");
      case TokenType::PLUS:
        return std::string("+");
      case TokenType::PLUS_PLUS:
        return std::string("++");
      case TokenType::PLUS_EQUALS:
        return std::string("+=");
      case TokenType::ASTERISK:
        return std::string("*");
      case TokenType::ASTERISK_EQUALS:
        return std::string("*=");
      case TokenType::NUM:
        return std::string("NUM");
      case TokenType::MINUS:
        return std::string("-");
      case TokenType::MINUS_EQUALS:
        return std::string("-=");
      case TokenType::MINUS_MINUS:
        return std::string("--");
      case TokenType::SLASH:
        return std::string("/");
      case TokenType::SLASH_EQUALS:
        return std::string("/=");
      case TokenType::PERIOD:
        return std::string(".");
      case TokenType::IDENTIFIER:
        return std::string("IDENTIFIER");
      case TokenType::LEFT_PARENTHESIS:
        return std::string("(");
      case TokenType::RIGHT_PARENTHESIS:
        return std::string(")");
      case TokenType::END_OF_FILE:
        return std::string("EOF");
      case TokenType::SEMICOLON:
          return std::string(";");
    }
    return std::string("unknown");
  }

  class Token {
  public:
    explicit Token(TokenType type, icu::UnicodeString raw) : type(type), raw(raw) {
    }

    TokenType type;
    icu::UnicodeString raw;

    [[nodiscard]] std::string getName() const {
      return toString(type);
    }

  };

}


#endif // CFF_TOKEN_H
