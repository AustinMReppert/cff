#include "Lexer.h"

#include <unicode/schriter.h>
#include <unicode/ustream.h>

#include <vector>

std::vector<CFF::Token> CFF::Lexer::lex(const icu::UnicodeString& lexemes) {
  std::vector<Token> tokens;
  std::size_t line = 1;
  std::size_t column = 0;

  icu::StringCharacterIterator itr = lexemes;

  while(itr.hasNext()) {
    int32_t start = itr.getIndex();
    UChar32 lexeme = itr.next32PostInc();

    if(CFF::isNewline(lexeme)) {
      ++line;
      column = 0;
      continue;
    } else ++column;

    if(lexeme == U'/') {
      if(itr.hasNext()) {
        lexeme = itr.nextPostInc();
        if(lexeme == U'/') {
          while(itr.hasNext() && !CFF::isNewline(itr.next32PostInc()))
            ;
        } else if(lexeme == U'*') {
          while(itr.hasNext()) {
            lexeme = itr.next32PostInc();
            if(lexeme == U'*' && itr.hasNext() && itr.next32PostInc() == U'/') {
              break;
            }
          }
        } else {
          itr.previous32();
          tokens.emplace_back(TokenType::SLASH, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        }
      } else {
        tokens.emplace_back(TokenType::SLASH, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
      }
    } else if(lexeme == U'+') {
      if(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(lexeme == U'=') {
          tokens.emplace_back(TokenType::PLUS_EQUALS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        } else if(lexeme == U'+') {
          tokens.emplace_back(TokenType::PLUS_PLUS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        } else {
          itr.previous32();
          tokens.emplace_back(TokenType::PLUS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        }
      } else {
        tokens.emplace_back(TokenType::PLUS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
      }
    } else if(lexeme == U'-') {
      if(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(lexeme == U'=') {
          tokens.emplace_back(TokenType::MINUS_EQUALS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        } else if(lexeme == U'-') {
          tokens.emplace_back(TokenType::MINUS_MINUS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        } else {
          itr.previous32();
          tokens.emplace_back(TokenType::MINUS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        }
      } else {
        tokens.emplace_back(TokenType::MINUS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
      }
    } else if(lexeme == U'*') {
      if(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(lexeme == U'=') {
          tokens.emplace_back(TokenType::ASTERISK_EQUALS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        } else {
          itr.previous32();
          tokens.emplace_back(TokenType::ASTERISK, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        }
      } else {
        tokens.emplace_back(TokenType::ASTERISK, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
      }
    } else if(lexeme == U'=') {
      if(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(lexeme == U'=') {
          tokens.emplace_back(TokenType::EQUALS_EQUALS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        } else {
          itr.previous32();
          tokens.emplace_back(TokenType::EQUALS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
        }
      } else {
        tokens.emplace_back(TokenType::EQUALS, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
      }
    } else if(CFF::isNumeric(lexeme)) {
      bool shouldExit = false;
      while(itr.hasNext() && !shouldExit) {
        lexeme = itr.next32PostInc();
        if(CFF::isNumeric(lexeme)) ;
        else if(lexeme == U'.') {
          if(itr.hasNext() && CFF::isNumeric(itr.next32PostInc())) {
            while(itr.hasNext()) {
              lexeme = itr.next32PostInc();
              if(CFF::isNumeric(lexeme));
              else {
                itr.previous32();
                shouldExit = true;
                break;
              }
            }
          } else {
            throw std::runtime_error("Expected number after decimal place");
          }
        } else {
          itr.previous32();
          shouldExit = true;
        }
      }
      tokens.emplace_back(TokenType::NUM, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
    } else if(CFF::isAlphabetic(lexeme) || lexeme == U'_') {
      while(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(!(CFF::isAlphabetic(lexeme) || CFF::isNumeric(lexeme) || lexeme == '_')) {
          itr.previous32();
          break;
        }
      }
      tokens.emplace_back(TokenType::IDENTIFIER, icu::UnicodeString(lexemes, start, itr.getIndex() - start));
    } else if(CFF::isWhitespace(lexeme)) {
    } else {
      std::cerr << icu::UnicodeString(lexemes) << std::endl;
      throw std::runtime_error("unknown lexeme in file");
    }
  }
  return tokens;
}