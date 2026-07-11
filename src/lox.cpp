#include "lox.h"
#include <iostream>
#include <string>

bool Lox::had_error = false;

void Lox::error(int line, const std::string& message)
{
  std::cout << "[line " << line << "] Error: " << message;
  had_error = true;
}
