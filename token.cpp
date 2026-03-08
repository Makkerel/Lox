#include "token.h"
#include <string>

std::string Token::to_string() {
  std::string token_string;
  token_string.append(get_token_type(type));
  token_string += " " + lexeme + " " + literal;
  return token_string;
}
