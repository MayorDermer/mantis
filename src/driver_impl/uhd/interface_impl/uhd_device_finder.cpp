//
// Created by Jon Kler on 4/14/25.
//

#include "mantis/driver_impl/uhd/interface_impl/uhd_device_finder.h"
#include "mantis/driver_impl/uhd/supported_device_types/x300.h"
#include "mantis/driver_impl/uhd/supported_device_types/x400.h"
#include "mantis/driver_impl/uhd/supported_device_types/b200.h"
#include "mantis/driver_impl/uhd/supported_device_types/unknown.h"

#include <uhd/usrp/multi_usrp.hpp>

template<typename T>
using device = mantis::interfaces::i_uhd_supported_device<T>;

std::unordered_map<std::string, uhd_builder_function_t>
        mantis::driver_impl::uhd_i::uhd_device_finder::builders = {
        {"x300",    device<supported_devices::x300>::make},
        {"b200",    device<supported_devices::b200>::make},
        {"x400",    device<supported_devices::x400>::make},
        {"unknown", device<supported_devices::unknown>::make}
};

std::unordered_map<std::string, bool> mantis::driver_impl::uhd_i::uhd_device_finder::initialized_devices = {};

mantis::errors::error_code mantis::driver_impl::uhd_i::uhd_device_finder::init(
        unsigned int required_num, std::vector<mantis::go::msdr::sptr> &o_initialized_sdrs,
        const params::msdr_params params) {

    // lookup address
    uhd::device_addr_t device_address(params.get_find_args());

    // init all sdrs
    auto all_found_devices = uhd::device::find(device_address);

    //if no sdrs at all
    if (all_found_devices.empty()) {
        return errors::error_code::NO_SDRS_FOUND;
    }

    // init sdrs we havent already used
    std::vector<uhd::device_addr_t> relevant_found_devices{};
    // pretty inefficient if so
    for (const auto &device_addr: all_found_devices) {
        if (!initialized_devices.contains(device_addr.to_string())) {
            relevant_found_devices.emplace_back(device_addr);
        }
    }

    if (relevant_found_devices.size() < required_num) {
        return errors::error_code::INSUFFICIENT_SDRS_FOUND;
    }

    size_t i = 0;
    while (i < ((required_num == 0) ? relevant_found_devices.size() : required_num)) {
        uhd::device_addr_t current_address = relevant_found_devices.at(i);
        std::string device_type = current_address.get("type");
        auto build_func = builders.contains(device_type) ? builders.at(device_type) : builders.at("unknown");

        params::msdr_params device_params = params::msdr_params::from_uhd_device_addr(current_address, params);

        const go::msdr::sptr sdr_ptr = build_func(current_address, device_params);

        if (sdr_ptr == nullptr) continue;

        o_initialized_sdrs.emplace_back(sdr_ptr);
        initialized_devices[current_address.to_string()] = true;
        i++;
    }

    return errors::error_code::SUCCESS;
}


size_t mantis::driver_impl::uhd_i::uhd_device_finder::get_num_connected_unused(const params::msdr_params& params) {
    // lookup address
    size_t uninitialized{0};
    uhd::device_addr_t device_address(params.get_find_args());
    auto found_devices = uhd::device::find(device_address);

    for(const auto& device_addr: found_devices) {
        if(!initialized_devices.contains(device_addr.to_string())) {
            uninitialized++;
        }
    }

    return uninitialized;
}