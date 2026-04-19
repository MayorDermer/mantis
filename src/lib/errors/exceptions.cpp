//
// Created by Jon Kler on 3/23/25.
//

#include "mantis/lib/errors/exceptions.h"
#include <utility>

mantis::runtime_error::runtime_error(std::string what) : message(std::move(what)) {}

const char *mantis::runtime_error::what() const noexcept { return this->message.c_str(); }