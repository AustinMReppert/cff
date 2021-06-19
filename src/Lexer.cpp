#include "Lexer.h"

#include <unicode/ustream.h>

#include <utility>
#include <vector>

std::vector<std::shared_ptr<CFF::Token>> CFF::Lexer::lex() {
  std::vector<std::shared_ptr<CFF::Token>> tokens;
  line = 1;
  column = 0;

  while(itr.hasNext()) {
    start = itr.getIndex();
    UChar32 lexeme = itr.next32PostInc();

    if(CFF::isNewline(lexeme)) {
      ++line;
      column = 0;
      continue;
    } else ++column;

    if(lexeme == U'l') {
      if(itr.hasNext()) {
        lexeme = itr.nextPostInc();
        if(lexeme == U'e') {
          if(itr.hasNext()) {
            lexeme = itr.next32PostInc();
            if(lexeme == U't') {
              appendToken(TokenType::LET, tokens);
            } else{
              itr.previous32();
              itr.previous32();
            }
          } else {
            itr.previous32();
            itr.previous32();
          }
        } else{
          itr.previous32();
        }
      } else{
        //itr.previous32();
      }
    } else if(lexeme == U'/') {
      if(itr.hasNext()) {
        lexeme = itr.nextPostInc();
        if(lexeme == U'/') {
          while(itr.hasNext() && !CFF::isNewline(itr.next32PostInc()));
        } else if(lexeme == U'*') {
          while(itr.hasNext()) {
            lexeme = itr.next32PostInc();
            if(lexeme == U'*' && itr.hasNext() && itr.next32PostInc() == U'/') {
              break;
            }
          }
        } else{
          itr.previous32();
          appendToken(TokenType::SLASH, tokens);
        }
      } else{
        appendToken(TokenType::SLASH, tokens);
      }
    } else if(lexeme == U'+') {
      if(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(lexeme == U'=') {
          appendToken(TokenType::PLUS_EQUALS, tokens);
        } else if(lexeme == U'+') {
          appendToken(TokenType::PLUS_PLUS, tokens);
        } else{
          itr.previous32();
          appendToken(TokenType::PLUS, tokens);
        }
      } else{
        appendToken(TokenType::PLUS, tokens);
      }
    } else if(lexeme == U'-') {
      if(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(lexeme == U'=') {
          appendToken(TokenType::MINUS_EQUALS, tokens);
        } else if(lexeme == U'-') {
          appendToken(TokenType::MINUS_MINUS, tokens);
        } else{
          itr.previous32();
          appendToken(TokenType::MINUS, tokens);
        }
      } else{
        appendToken(TokenType::MINUS, tokens);
      }
    } else if(lexeme == U'*') {
      if(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(lexeme == U'=') {
          appendToken(TokenType::ASTERISK_EQUALS, tokens);
        } else{
          itr.previous32();
          appendToken(TokenType::ASTERISK, tokens);
        }
      } else{
        appendToken(TokenType::ASTERISK, tokens);
      }
    } else if(lexeme == U'=') {
      if(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(lexeme == U'=') {
          appendToken(TokenType::EQUALS_EQUALS, tokens);
        } else{
          itr.previous32();
          appendToken(TokenType::EQUALS, tokens);
        }
      } else{
        appendToken(TokenType::EQUALS, tokens);
      }
    } else if(CFF::isNumeric(lexeme)) {
      bool shouldExit = false;
      while(itr.hasNext() && !shouldExit) {
        lexeme = itr.next32PostInc();
        if(CFF::isNumeric(lexeme));
        else if(lexeme == U'.') {
          if(itr.hasNext() && CFF::isNumeric(itr.next32PostInc())) {
            while(itr.hasNext()) {
              lexeme = itr.next32PostInc();
              if(CFF::isNumeric(lexeme));
              else{
                itr.previous32();
                shouldExit = true;
                break;
              }
            }
          } else{
            throw std::runtime_error("Expected number after decimal place");
          }
        } else{
          itr.previous32();
          shouldExit = true;
        }
      }
      appendToken(TokenType::NUM, tokens);
    } else if(CFF::isAlphabetic(lexeme) || lexeme == U'_') {
      while(itr.hasNext()) {
        lexeme = itr.next32PostInc();
        if(!(CFF::isAlphabetic(lexeme) || CFF::isNumeric(lexeme) || lexeme == U'_')) {
          itr.previous32();
          break;
        }
      }
      appendToken(TokenType::IDENTIFIER, tokens);
    } else if(lexeme == U'(') {
      appendToken(TokenType::LEFT_PARENTHESIS, tokens);
    } else if(lexeme == U';') {
      appendToken(TokenType::SEMICOLON, tokens);
    } else if(lexeme == U')') {
      appendToken(TokenType::RIGHT_PARENTHESIS, tokens);
    } else if(CFF::isWhitespace(lexeme)) {
    } else{
      std::cerr << icu::UnicodeString(lexemes) << std::endl;
      throw std::runtime_error("unknown lexeme in file");
    }
  }
  tokens.emplace_back(std::make_shared<CFF::Token>(TokenType::END_OF_FILE, icu::UnicodeString("")));
  return tokens;
}


void CFF::Lexer::appendToken(CFF::TokenType tokenType, std::vector<std::shared_ptr<CFF::Token>>& tokens) {
  tokens.emplace_back(
      std::make_shared<CFF::Token>(tokenType, icu::UnicodeString(lexemes, start, itr.getIndex() - start)));
}

CFF::Lexer::Lexer(icu::UnicodeString lexemes) {
  this->lexemes = std::move(lexemes);
  itr = this->lexemes;
}
