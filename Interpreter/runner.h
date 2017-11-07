//
// Created by Herman Karlsson on 2017-11-07.
//

#ifndef INTERPRETER_PROGRAM_H
#define INTERPRETER_PROGRAM_H

#include <vector>
#include <iostream>
#include <exception>

#include "parser.h"

class Runner {
private:

  std::vector<Instruction> instructions;
  std::vector<int> memory;
  const int MEM_SIZE;

  void init() {

  }

  int get_matching_end(int idx) {
    int cnt = 1;
    while (cnt) {
      Instruction inst = instructions[++idx];
      if (inst == END) throw runtime_error("unmatched [");
      if (inst == START_LOOP) ++cnt;
      if (inst == END_LOOP) --cnt;
    }
    return idx;
  }

  int get_matching_start(int idx) {
    int cnt = 1;
    while (cnt) {
      Instruction inst = instructions[--idx];
      if (inst == START) throw runtime_error("unmatched ]");
      if (inst == START_LOOP) --cnt;
      if (inst == END_LOOP) ++cnt;
    }
    return idx;
  }

public:

  explicit Runner(std::vector<Instruction> program, int memsize = 256):
      instructions(std::move(program)), MEM_SIZE(memsize), memory(memsize, 0) {
    init();
  }

  void reset() {
    memory.assign(MEM_SIZE, 0);
  };

  void run() {
    int data_pointer = 0;
    int instruction_pointer = 0;
    while (true) {
      switch (instructions[instruction_pointer]) {
        case INCREMENT:
          ++memory[data_pointer];
          break;

        case DECREMENT:
          --memory[data_pointer];
          break;

        case MOVE_RIGHT:
          ++data_pointer;
          break;

        case MOVE_LEFT:
          --data_pointer;
          break;

        case OUTPUT:
          std::cout.put(memory[data_pointer]);
          break;

        case INPUT:
          memory[data_pointer] = std::cin.get();
          break;

        case START_LOOP:
          if (memory[data_pointer] != 0) break;
          instruction_pointer = get_matching_end(instruction_pointer);
          break;

        case END_LOOP:
          if (memory[data_pointer] == 0) break;
          instruction_pointer = get_matching_start(instruction_pointer);
          break;

        case START: break;
        case END: return;
      }

      if (data_pointer < 0 || data_pointer >= MEM_SIZE) {
        throw syntax_error("Out of bounds");
      }

      ++instruction_pointer;
    }
  }

};


#endif //INTERPRETER_PROGRAM_H
