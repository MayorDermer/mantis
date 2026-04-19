//
// Created by Jon Kler on 4/14/25.
//

#pragma once

#include "i_uhd_supported_device.h"

namespace mantis::supported_devices {
    /**
     * @brief make for the x300 series
     * if no mcr is provided will use 200e6
     * ensures mcr is either 200e6 or 184.32e6
     */
    class x300 : public interfaces::i_uhd_supported_device<x300> {
    public:

        static mantis::go::msdr::sptr make(uhd::device_addr_t address,
                                           params::msdr_params &params);

        [[nodiscard]] static mantis::errors::error_code validate(const params::msdr_params& params);

    private:
        static std::vector<double> valid_mcrs;
    };
}