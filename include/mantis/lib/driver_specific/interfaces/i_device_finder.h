//
// Created by Jon Kler on 4/7/25.
//

#pragma once

#include <mantis/lib/classes/msdr/msdr.h>
#include <mantis/lib/classes/msdr/msdr_params.h>
#include <mantis/lib/errors/error_codes.h>
#include <vector>

namespace mantis::interfaces {
    /**
     * @brief class to find and initialize sdrs. To be implemented by all driver types
     * crtp used to allow for static inheritance-like behavior
     */
    template<typename DriverDeviceFinder>
    class i_device_finder {
    public:
        /**
         * @brief finds requested number of sdrs and initializes them before placing in the provided vector.
         * @param required_num num sdrs to init, use 0 to init all, alternatively use the provided init_all function
         * @param o_initialized_sdrs  vector which will be filled with initialized msdr objects
         * @param params msdr params to search for/use for init
         */
        static int
        init(unsigned int required_num, std::vector<mantis::go::msdr::sptr> &o_initialized_sdrs,
             const params::msdr_params params);


        /**
         * @brief return number of sdrs available for connection
         * @param params params to search/filter by
         */
        static size_t get_num_connected_unused(const params::msdr_params& params);

    };

    template<typename DriverDeviceFinder>
    int i_device_finder<DriverDeviceFinder>::init(unsigned int required_num,
                                                  std::vector<mantis::go::msdr::sptr> &o_initialized_sdrs,
                                                  const params::msdr_params params) {
        return DriverDeviceFinder::init(required_num, o_initialized_sdrs, params);
    }

    template<typename DriverDeviceFinder>
    size_t i_device_finder<DriverDeviceFinder>::get_num_connected_unused(const params::msdr_params& params) {
        return DriverDeviceFinder::get_num_connected_unused();
    }
}