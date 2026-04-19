//
// Created by Jon Kler on 6/5/25.
//

#include "mantis/lib/utilities/prints.h"
#include <iostream>

void mantis::utils::pwarn(const std::string& warning) {
    std::cerr << "\033[33m[WARNING] [MANTIS] " << warning << "\033[0m\n";
}

void mantis::utils::perror(const std::string& error) {
    std::cerr << "\033[31m[ERROR] [MANTIS] " << error << "\033[0m\n";
}

void mantis::utils::pinfo(const std::string& message) {
    std::cout << "\033[32m[INFO] [MANTIS] " << message << "\033[0m\n";
}