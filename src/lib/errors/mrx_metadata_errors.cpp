//
// Created by Jon Kler on 6/8/25.
//

#include <mantis/config.h>
#include <mantis/lib/errors/mrx_metadata_errors.h>
#include <unordered_map>

std::unordered_map<mantis::metadata_errors::mrx_metadata_error_codes, std::string>
mantis::metadata_errors::get_mrx_metadata_err_code_map() {
    static std::unordered_map<mrx_metadata_error_codes, std::string> err_map = {
            {mrx_metadata_error_codes::NO_ERROR,     "No error"},
            {mrx_metadata_error_codes::TIMEOUT,      "No data received by timeout"},
            {mrx_metadata_error_codes::LATE,         "Stream command issued in past"},
            {mrx_metadata_error_codes::BROKEN_CHAIN, "Expected another stream command"},
            {mrx_metadata_error_codes::OVERFLOW,     "Internal buffer full and not being emptied fast enough"},
            {mrx_metadata_error_codes::ALIGNMENT,    "Multi-channel alignment failed"},
            {mrx_metadata_error_codes::BAD_PACKET,   "Packet could not be parsed"}
    };

    return err_map;
}

std::string mantis::metadata_errors::mantis_errno(mrx_metadata_error_codes& err) {
    return get_mrx_metadata_err_code_map().at(err);
}

