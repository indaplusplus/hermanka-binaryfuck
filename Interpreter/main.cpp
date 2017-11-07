#include <iostream>
#include <string>

#include "parser.h"

int main() {

  std::string source;
  Parser parser;
  auto program = parser.parse_bin(source);
  
}