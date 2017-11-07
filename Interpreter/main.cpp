#include <exception>
#include <iostream>
#include <fstream>
#include <string>

#include "parser.h"
#include "runner.h"
#include "exceptions.h"

//#define DEBUG

std::string source_file = "";
int source_type = 2;
int mem_size = 256;

void parse_args(int argc, char** argv) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg[0] == '-') {
      if (arg == "--bin" || arg == "-2") source_type = 2;
      if (arg == "--oct" || arg == "-8") source_type = 8;
      if (arg == "--hex" || arg == "-16") source_type = 16;
      if (arg == "--b32" || arg == "-32") source_type = 32;
      if (arg == "--memory" || arg == "-m") {
        if (i+1 == argc)
          throw argument_error("expected integer argument after -m flag");
        arg = argv[++i];
        try {
          mem_size = std::stoi(arg);
        } catch (std::exception) {
          throw argument_error("expected integer argument after -m flag");
        }
      }
    } else {
      if (source_file != "")
        throw argument_error("too many source files specified");
      source_file = arg;
    }
  }
  if (source_file == "") throw argument_error("No source file specified");
}

int main(int argc, char** argv) {
  try {
    parse_args(argc, argv);
  } catch (argument_error e) {
    std::cerr << "Error while parsing arguments: " << e.error_message << std::endl;
    exit(1);
  }

  std::ifstream file(source_file.c_str());
  if (!file.good()) {
    std::cerr << "did not find file: " << source_file << std::endl;
    exit(1);
  }

  std::string source;
  std::getline(file, source, '\0');
  parser parser;
  std::vector<Instruction> program;

  try {
    if (source_type == 2) program = parser.parse_bin(source);
    if (source_type == 8) program = parser.parse_oct(source);
    if (source_type == 16) program = parser.parse_hex(source);
    if (source_type == 32) program = parser.parse_32(source);
  } catch (syntax_error e) {
    std::cerr << "Syntax error: " << e.error_message << std::endl;
    exit(1);
  }

#ifdef DEBUG
  for (auto & i : program) std::cerr << char(i);
  std::cerr << std::endl;
#endif

  Runner runner(program, mem_size);
  try {
    runner.run();
  } catch (runtime_error e) {
    std::cerr << "Runtime error: " << e.error_message << std::endl;
    exit(1);
  }
}