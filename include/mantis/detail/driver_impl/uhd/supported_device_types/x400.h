#pragma once

#include "i_uhd_supported_device.h"

namespace mantis::supported_devices {
    /**
     * @brief make for the x400 series
     * if no mcr is provided will use 250e6
     * ensures mcr is either 250e6 or 245.76e6
     */
    class x400 : public interfaces::i_uhd_supported_device<x400> {
    public:

        static mantis::go::msdr::sptr make(uhd::device_addr_t address,
                                           params::msdr_params &params);

        [[nodiscard]] static mantis::errors::error_code validate(const params::msdr_params& params);

    private:
        static std::vector<double> valid_mcrs;
    };
}
