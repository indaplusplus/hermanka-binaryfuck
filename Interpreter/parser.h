//
// Created by Herman Karlsson on 2017-11-07.
//

#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#include <vector>
#include <string>
#include <exception>
#include <sstream>

#include "exceptions.h"

enum Instruction : char {
  INCREMENT = '+',
  DECREMENT = '-',
  MOVE_RIGHT = '>',
  MOVE_LEFT = '<',
  OUTPUT = '.',
  INPUT = ',',
  START_LOOP = '[',
  END_LOOP = ']',
  START = '\1',
  END = '\0'
};

class parser {
public:

  //converts string to runner instructions
  std::vector<Instruction> parse_bin(std::string source) {


    if (source.empty() || source[0] != '1') {
      throw syntax_error("Invalid program: no leading 1");
    }

    std::vector<Instruction> instructions {START};
    std::stringstream ss(source);

    ss.ignore();

    while (true) {
      Instruction next = get_next_instruction(ss);
      instructions.push_back(next);
      if (next == END) break;
    }

    return instructions;
  }

  std::vector<Instruction> parse_oct(std::string source) {
    return {END};
  }

  std::vector<Instruction> parse_hex(std::string source) {
    return {END};
  }

  std::vector<Instruction> parse_32(std::string source) {
    return {END};
  }

private:

  Instruction get_next_instruction(std::stringstream & ss) {

    while (!ss.eof() && ss.peek() != '1' && ss.peek() != '0')
      ss.ignore();

    if (ss.eof()) return END;

    std::string cmd;
    while (cmd.size() < 3) {
      if (ss.eof()) throw syntax_error("incomplete command");
      char c;
      ss >> c;
      if (c != '0' && c != '1') continue;
      cmd += c;
    }

    if (cmd == "000") return INCREMENT;
    if (cmd == "001") return DECREMENT;
    if (cmd == "010") return MOVE_RIGHT;
    if (cmd == "011") return MOVE_LEFT;
    if (cmd == "100") return OUTPUT;
    if (cmd == "101") return INPUT;
    if (cmd == "110") return START_LOOP;
    if (cmd == "111") return END_LOOP;

    return END;
  }
};

#endif //INTERPRETER_PARSER_H
