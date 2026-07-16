#ifndef SCANNER
#define SCANNER

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include "token.h"

class Scanner
{
  std::string_view source;
  std::vector<Token> tokens;
  inline static const std::unordered_map<std::string, TokenType> keywords = {
      {"and", TokenType::AND},     {"class", TokenType::CLASS}, {"else", TokenType::ELSE},
      {"false", TokenType::FALSE}, {"for", TokenType::FOR},     {"fun", TokenType::FUN},
      {"if", TokenType::IF},       {"nil", TokenType::NIL},     {"or", TokenType::OR},
      {"print", TokenType::PRINT}, {"super", TokenType::SUPER}, {"this", TokenType::THIS},
      {"true", TokenType::TRUE},   {"var", TokenType::VAR},     {"while", TokenType::WHILE}};
  int start   = 0;
  int current = 0;
  int line    = 1;

  void scan_token();
  bool match(char match);
  char peek();
  char peek_next();
  void string_literal();
  void number_literal();
  void identifier();
  void add_token(TokenType token);
  void add_token(TokenType token, const std::string& literal);

 public:
  std::vector<Token> scan_tokens();
  Scanner(std::string_view input) : source(input)
  {
  }
};
#endif
