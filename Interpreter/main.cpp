#include <exception>
#include <iostream>
#include <fstream>
#include <string>

#include "parser.h"
#include "runner.h"
#include "exceptions.h"

//#define DEBUG

int main(int argc, char** argv) {

  if (argc != 2) {
    exit(1);
  }

  std::ifstream file;
  try {
    file.open(argv[1]);
  } catch (std::exception e) {
    std::cerr << "did not find file " << argv[1] << std::endl;
    exit(1);
  }

  std::string source;
  std::getline(file, source, '\0');
  parser parser;
  std::vector<Instruction> program;

  try {
    program = parser.parse_bin(source);
  } catch (syntax_error e) {
    std::cerr << "Syntax error: " << e.error_message << std::endl;
    exit(1);
  }

#ifdef DEBUG
  for (auto & i : program) std::cerr << char(i);
  std::cerr << std::endl;
#endif

  Runner runner(program);
  try {
    runner.run();
  } catch (runtime_error e) {
    std::cerr << "Runtime error: " << e.error_message << std::endl;
    exit(1);
  }
}