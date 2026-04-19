//
// Created by Jon Kler on 6/5/25.
//

#pragma once

#include "i_uhd_supported_device.h"

namespace mantis::supported_devices {
    /**
     * @brief make for an unknown usrp series
     * will do no checks and only init 1 rx and 1 tx channel since the modularity of the channels is unknown
     */
    class unknown : public interfaces::i_uhd_supported_device<unknown> {
    public:
        static mantis::go::msdr::sptr make(uhd::device_addr_t address,
                                           params::msdr_params &params);

        [[nodiscard]] static mantis::errors::error_code validate(const params::msdr_params& params);
    };
};