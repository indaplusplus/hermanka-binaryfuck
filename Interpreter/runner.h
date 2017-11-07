//
// Created by Herman Karlsson on 2017-11-07.
//

#ifndef INTERPRETER_PROGRAM_H
#define INTERPRETER_PROGRAM_H

#include <vector>
#include <iostream>
#include <exception>
#include <stack>

#include "parser.h"

class Runner {
private:

  std::vector<std::pair<Instruction, int> > instructions;
  std::vector<int> memory;
  std::vector<int> loop_match;
  const int MEM_SIZE;

  void match_loops() {
    std::stack<int> unmatched;
    for (int i = 0; i < instructions.size(); ++i) {
      Instruction inst = instructions[i].first;
      if (inst == START_LOOP) {
        unmatched.push(i);
      }
      if (inst == END_LOOP) {
        if (unmatched.empty()) throw runtime_error("unmatched ]");
        int idx = unmatched.top();
        unmatched.pop();
        loop_match[i] = idx;
        loop_match[idx] = i;
      }
    }
    if (!unmatched.empty()) throw runtime_error("unmatched [");
  }

  void init() {
    match_loops();
  }

  int get_matching_end(int idx) {
    return loop_match[idx];
  }

  int get_matching_start(int idx) {
    return loop_match[idx];
  }

public:

  explicit Runner(std::vector<std::pair<Instruction,int> > program, int mem_size = 256):
      instructions(std::move(program)), MEM_SIZE(mem_size), memory(mem_size, 0),
      loop_match(instructions.size(), -1) {
    init();
  }

  void reset() {
    memory.assign(MEM_SIZE, 0);
  };

  void run() {
    int data_pointer = 0;
    int instruction_pointer = 0;
    while (true) {
      int cnt = instructions[instruction_pointer].second;
      switch (instructions[instruction_pointer].first) {
        case INCREMENT:
          memory[data_pointer] += cnt;
          break;

        case DECREMENT:
          memory[data_pointer] -= cnt;
          break;

        case MOVE_RIGHT:
          data_pointer += cnt;
          break;

        case MOVE_LEFT:
          data_pointer -= cnt;
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
        throw runtime_error("Out of bounds");
      }

      ++instruction_pointer;
    }
  }
};

#endif //INTERPRETER_PROGRAM_H
