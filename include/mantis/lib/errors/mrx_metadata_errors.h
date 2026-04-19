//
// Created by Jon Kler on 6/8/25.
//

#pragma once

#include <mantis/config.h>
#include <unordered_map>

namespace mantis::metadata_errors {

    enum class MANTIS_API mrx_metadata_error_codes {
        //! No error
        NO_ERROR = 0x0,
        //! No data received by timeout
        TIMEOUT = 0x1,
        //! Stream command issued in past
        LATE = 0x2,
        //! Expected another stream command
        BROKEN_CHAIN = 0x4,
        //! Internal buffer full and not being emptied fast enough
        OVERFLOW = 0x8,
        //! Multi-channel alignment failed
        ALIGNMENT = 0xc,
        //! Packet could not be parsed
        BAD_PACKET = 0xf,
    };

    std::unordered_map<mrx_metadata_error_codes, std::string> get_mrx_metadata_err_code_map();

    //! get detailed error string
    [[maybe_unused]] std::string MANTIS_API mantis_errno(mrx_metadata_error_codes &err);

}