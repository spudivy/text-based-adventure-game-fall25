#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <stdexcept>

/**
 * @class bad_input Exceptions.hpp "Exceptions.hpp"
 * @brief Unusable input from user.
 */
class bad_input: public std::runtime_error {
 public:
  /**
  * @brief Unusable input from user.
  * @param errMessage An error message.
  */
  explicit bad_input(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

#endif // EXCEPTIONS_H_INCLUDED
