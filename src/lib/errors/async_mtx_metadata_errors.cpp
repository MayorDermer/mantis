//
// Created by Jon Kler on 6/8/25.
//

#include <mantis/lib/errors/async_mtx_metadata_errors.h>
#include <iostream>

std::unordered_map<mantis::metadata_errors::async_mtx_metadata_error_codes, std::string>
mantis::metadata_errors::get_mtx_metadata_err_code_map() {

    static std::unordered_map<mantis::metadata_errors::async_mtx_metadata_error_codes, std::string> err_map = {
            {async_mtx_metadata_error_codes::BURST_ACK, "Burst Successfully transmitted"},
            {async_mtx_metadata_error_codes::UNDERFLOW, "Underflow, Not receiving samples fast enough"},
            {async_mtx_metadata_error_codes::SEQ_ERROR, "Packet loss between host and device"},
            {async_mtx_metadata_error_codes::LATE, "Packet was Late, expired timespec"},
            {async_mtx_metadata_error_codes::UNDERFLOW_IN_PACKET, "Underflow in packet"},
            {async_mtx_metadata_error_codes::SEQ_ERROR_IN_BURST, "Packet loss in burst"},
            {async_mtx_metadata_error_codes::USER_PAYLOAD, "Custom user payload"}
    };
    return err_map;
}

std::string mantis::metadata_errors::mantis_errno(async_mtx_metadata_error_codes &err) {
    if (!get_mtx_metadata_err_code_map().contains(err)) {
        std::cout << "Unrecognized enum: " << static_cast<int>(err) << ". have you de-masked?\n";
    }
    return get_mtx_metadata_err_code_map().at(err);
}
