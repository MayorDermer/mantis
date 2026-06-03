#pragma once

#include <unordered_map>
#include <mantis/lib/driver_specific/interfaces/i_device_finder.h>

using virtual_builder_function_t =
        mantis::go::msdr::sptr (*)(const mantis::params::msdr_params);

namespace mantis::driver_impl::virtual_i {
    class virtual_device_finder
            : public interfaces::i_device_finder<virtual_device_finder> {
    public:
        [[nodiscard]] static mantis::errors::error_code init(
                unsigned int required_num,
                std::vector<mantis::go::msdr::sptr> &o_initialized_sdrs,
                const params::msdr_params params = {});

        static size_t get_num_connected_unused(const params::msdr_params& params);

    private:
        static std::unordered_map<std::string, virtual_builder_function_t> builders;
        static std::vector<params::msdr_params> initialized_devices;
    };
}  // namespace mantis::driver_impl::virtual_i
