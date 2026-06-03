//
// Created by Jon Kler on 6/9/25.
//

#pragma once

#include "i_uhd_supported_device.h"

namespace mantis::supported_devices {
    /**
     * @brief make for the b200 series
     * if no mcr is provided will use auto mcr
     * otherwise, will ensure mcr is between 5e6 and 61.44e6 MHz
     */
    class b200 : public interfaces::i_uhd_supported_device<b200> {
    public:

        static mantis::go::msdr::sptr make(uhd::device_addr_t address, params::msdr_params &params);

        [[nodiscard]] static mantis::errors::error_code validate(params::msdr_params params);

    };
}