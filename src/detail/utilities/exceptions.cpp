#include "mantis/detail/utilities/exceptions.h"
#include <utility>

mantis::runtime_error::runtime_error(std::string what) : message(std::move(what)) {}

const char *mantis::runtime_error::what() const noexcept { return this->message.c_str(); }
