//
// Created by Jon Kler on 6/9/25.
//

#include <mantis/driver_impl/uhd/supported_device_types/b200.h>
#include <mantis/lib/utilities/prints.h>
#include "mantis/driver_impl/uhd/utilities/uhd_utils.h"

static constexpr double lowest_valid_mcr = 5e6; // from uhd website
static constexpr double highest_valid_mcr = 61.44e6;

mantis::errors::error_code mantis::supported_devices::b200::validate(const params::msdr_params params) {
    /// b200 series allows auto mcr;
    if (params.master_clock_rate.empty()) {
        mantis::utils::pwarn("Using Auto MCR");
        return errors::error_code::SUCCESS;
    }

    double requested_mcr = std::stod(params.master_clock_rate);
    if (requested_mcr < lowest_valid_mcr || requested_mcr > highest_valid_mcr) {
        return errors::error_code::INVALID_MCR;
    }

    return errors::error_code::SUCCESS;
}

mantis::go::msdr::sptr mantis::supported_devices::b200::make(uhd::device_addr_t address,
                                                             params::msdr_params &params) {

    auto usrp = driver_impl::uhd_i::init(address, params);

    go::msdr::sptr msdr = std::make_shared<go::msdr>(params);
    driver_impl::uhd_i::initialize_single_tx_channel(params, usrp, msdr->get_tx_channels(), address, 0);
    driver_impl::uhd_i::initialize_single_rx_channel(params, usrp, msdr->get_rx_channels(), address, 0);

    return msdr;
}