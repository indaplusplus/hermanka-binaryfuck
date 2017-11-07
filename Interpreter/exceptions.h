//
// Created by Herman Karlsson on 2017-11-07.
//

#ifndef INTERPRETER_EXCEPTIONS_H
#define INTERPRETER_EXCEPTIONS_H

#include <exception>
#include <string>

class syntax_error : std::exception {
public:
  std::string error_message;
  syntax_error(std::string message = "") : error_message(message) {}
};

class runtime_error : std::exception {
public:
  std::string error_message;
  runtime_error(std::string message = "") : error_message(message) {}
};

class argument_error : std::exception {
public:
  std::string error_message;
  argument_error(std::string message = "") : error_message(message) {}
};

#endif //INTERPRETER_EXCEPTIONS_H
