//
// Created by Jon Kler on 4/7/25.
//

#pragma once

#include <uhd/usrp/multi_usrp.hpp>
#include <unordered_map>

#include <mantis/lib/driver_specific/interfaces/i_device_finder.h>

using uhd_builder_function_t = mantis::go::msdr::sptr (*)(
        uhd::device_addr_t, mantis::params::msdr_params &);

namespace mantis::driver_impl::uhd_i {
    /**
     * @brief uhd implementation of the i_device_finder class, see i_device_finder for more details
     */
    class uhd_device_finder
            : public interfaces::i_device_finder<uhd_device_finder> {
    public:
        [[nodiscard]] static mantis::errors::error_code init(
                unsigned int required_num,
                std::vector<mantis::go::msdr::sptr> &o_initialized_sdrs,
                const params::msdr_params params = {});

        [[nodiscard]] static size_t get_num_connected_unused(const params::msdr_params &params);

    private:
        static std::unordered_map<std::string, uhd_builder_function_t> builders;
        static std::unordered_map<std::string, bool> initialized_devices;
    };
}  // namespace mantis::driver_impl::uhd_i
