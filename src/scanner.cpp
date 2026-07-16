#include "scanner.h"
#include <cctype>
#include <string>
#include <utility>
#include <vector>
#include "lox.h"
#include "token.h"

std::vector<Token> Scanner::scan_tokens()
{
  while (current < source.length()) {
    start = current;
    scan_token();
  }
  tokens.emplace_back(TokenType::T_EOF, "", "", line);
  return std::move(tokens);
}

bool Scanner::match(char match)
{
  if (current >= source.length())
    return false;
  if (source[current] != match)
    return false;

  current++;
  return true;
}

char Scanner::peek()
{
  if (current >= source.length()) {
    return '\0';
  } else {
    return source[current];
  }
}

char Scanner::peek_next()
{
  if (current + 1 >= source.length()) {
    return '\0';
  } else {
    return source[current + 1];
  }
}

void Scanner::string_literal()
{
  while (peek() != '"' && current < source.length()) {
    if (peek() == '\n') {
      line++;
    }
    current++;
  }

  if (current >= source.length()) {
    Lox::error(line, "Unterminated string.");
    return;
  }
  current++;
  add_token(TokenType::STRING, std::string(source.substr(start + 1, current - start - 2)));
}

void Scanner::number_literal()
{
  while (std::isdigit(static_cast<unsigned char>(peek()))) {
    current++;
  }
  if (peek() == '.' && std::isdigit(static_cast<unsigned char>(peek_next()))) {
    current++;
    while (std::isdigit(static_cast<unsigned char>(peek()))) {
      current++;
    }
  }

  add_token(TokenType::NUMBER, std::string(source.substr(start, current - start)));
}

void Scanner::identifier()
{
  auto isalpha_numeric = [](char c) -> bool {
    return static_cast<bool>(std::isalpha(static_cast<unsigned char>(c))) ||
           std::isdigit(static_cast<unsigned char>(c)) || c == '_';
  };
  while (isalpha_numeric(peek())) {
    current++;
  }
  std::string text(source.substr(start, current - start));
  auto keyword   = keywords.find(text);
  TokenType type = TokenType::IDENTIFIER;
  if (keyword != keywords.end()) {
    type = keyword->second;
  }
  add_token(type);
}

void Scanner::scan_token()
{
  using enum TokenType;
  char c = source[current++];
  switch (c) {
    case '(': add_token(LEFT_PAREN); break;
    case ')': add_token(RIGHT_PAREN); break;
    case '{': add_token(LEFT_BRACE); break;
    case '}': add_token(RIGHT_BRACE); break;
    case ',': add_token(COMMA); break;
    case '.': add_token(DOT); break;
    case '-': add_token(MINUS); break;
    case '+': add_token(PLUS); break;
    case ';': add_token(SEMICOLON); break;
    case '*': add_token(STAR); break;
    case '!': add_token(match('=') ? BANG_EQUAL : BANG); break;
    case '=': add_token(match('=') ? EQUAL_EQUAL : EQUAL); break;
    case '<': add_token(match('=') ? LESS_EQUAL : LESS); break;
    case '>': add_token(match('=') ? GREATER_EQUAL : GREATER); break;
    case '/':
      if (match('/')) {
        while (peek() != '\n' && current < source.length()) {
          current++;
        }
      } else {
        add_token(SLASH);
      }
      break;
    case ' ':  break;
    case '\r': break;
    case '\t': break;
    case '\n': line++; break;
    case '"':  string_literal(); break;
    default:
      if (std::isdigit(static_cast<unsigned char>(c))) {
        number_literal();
      } else if (static_cast<bool>(std::isalpha(static_cast<unsigned char>(c))) || c == '_') {
        identifier();
      } else {
        Lox::error(line, "Unexpected character.");
      }
      break;
  }
}

void Scanner::add_token(TokenType token)
{
  std::string text(source.substr(start, current - start));
  tokens.emplace_back(token, text, "", line);
}

void Scanner::add_token(TokenType token, const std::string& literal)
{
  std::string text(source.substr(start, current - start));
  tokens.emplace_back(token, text, literal, line);
}
