//
// Created by Jon Kler on 6/5/25.
//

#include "mantis/lib/utilities/prints.h"
#include "mantis/version.h"
#include <iostream>

void mantis::utils::pwarn(const std::string& warning) {
    std::cerr << "\033[33m[WARNING] [MANTIS] " << warning << "\033[0m" << std::endl;
}

void mantis::utils::perror(const std::string& error) {
    std::cerr << "\033[31m[ERROR] [MANTIS] " << error << "\033[0m" << std::endl;
}

void mantis::utils::pinfo(const std::string& message) {
    /// no flush needed, let system handle it
    std::cout << "\033[32m[INFO] [MANTIS] " << message << "\033[0m\n";
}

void mantis::utils::pversion() {
    /// flushing since you typically want this to show up right away
    std::cout << "\033[32m[MANTIS VERSION] " << MANTIS_VERSION << "\033[0m" << std::endl;
}