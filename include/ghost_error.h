#pragma once

#include "utils.h"

namespace ghost {

  /**
   * error exception class for ghost
   **/
  class ghost_error : public std::exception {
   public:
    explicit ghost_error(const std::string& msg) : msg_(msg) {}

    const char* what() const throw() override { return msg_.c_str(); }

   private:
    std::string msg_;
  };

}  // namespace ghost
