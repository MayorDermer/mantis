//
// Created by Jon Kler on 3/23/25.
//

#ifndef MANTIS_EXCEPTIONS_H
#define MANTIS_EXCEPTIONS_H

#include <mantis/config.h>
#include <exception>
#include <string>

namespace mantis {
    //! General purpose runtime_error for mantis. All normal operations should be caught and handled with an error code, this is for fatal errors
    class MANTIS_API runtime_error : public std::exception {
    public:
        explicit runtime_error(std::string what = "");
        [[nodiscard]] const char *what() const noexcept override;
    private:
        const std::string message;
    };
}
#endif //MANTIS_EXCEPTIONS_H
