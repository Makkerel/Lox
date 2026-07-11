#ifndef LOX
#define LOX

#include <string>
class Lox
{
 public:
  static bool had_error;
  static void error(int line, const std::string& message);
};

#endif
