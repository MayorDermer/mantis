//
// Created by Jon Kler on 4/15/25.
//

#pragma once

#include <mantis/lib/errors/error_codes.h>
#include <mantis/lib/classes/msdr/msdr.h>
#include <mantis/lib/classes/msdr/msdr_params.h>
#include <uhd/usrp/multi_usrp.hpp>

namespace mantis::interfaces {
    /**
     * @brief helper class used to validate certain params (mainly master_clock_rate) when configuring a known sdr type
     * so we dont, for example, try to configure a b200 with a 200MHz MCR.
     * Uses crtp for static virtual-function-like behavior
     */
    template<typename Device>
    class i_uhd_supported_device {
    public:
        /**
         * returns msdr pointer
         * @param address uhd device address
         * @param params params to configure by
         * @note calls validate() before attempting initialization
         * @return ptr if success, nullptr if validation failed
         */
        static mantis::go::msdr::sptr make(uhd::device_addr_t address,
                                           params::msdr_params &params);

        /**
         * @brief validates configuration per type
         * @param msdr_params params used to init/configure
         */
        static mantis::errors::error_code validate(const params::msdr_params&);
    };

    template<typename Device>
    mantis::go::msdr::sptr i_uhd_supported_device<Device>::make(uhd::device_addr_t address,
                                                                params::msdr_params &params) {
        if (!errors::succeeded(i_uhd_supported_device<Device>::validate(params))) return nullptr;
        return Device::make(address, params);
    }

    template<typename Device>
    mantis::errors::error_code
    i_uhd_supported_device<Device>::validate(const params::msdr_params& params) {
        return Device::validate(params);
    }
}