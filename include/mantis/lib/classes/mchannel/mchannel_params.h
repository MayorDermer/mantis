//
// Created by Jon Kler on 6/8/25.
//

#pragma once

#include <cstddef>

namespace mantis::params {
    /**
     * @brief Struct to hold mchannel parameters
     * @param channel_num sdr channel num, starting from 0
     * @param is_valid flag which indicates whether channel can be used
     */
    struct mchannel_params {

        size_t channel_num;
        bool is_valid{true};

    };
}