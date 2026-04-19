//
// Created by Jon Kler on 4/16/25.
//

#include "mantis/driver_impl/uhd/supported_device_types/x400.h"
#include "mantis/driver_impl/uhd/utilities/uhd_utils.h"


mantis::go::msdr::sptr mantis::supported_devices::x400::make(uhd::device_addr_t address, params::msdr_params &params) {
    auto usrp = driver_impl::uhd_i::init(address, params);

    go::msdr::sptr msdr = std::make_shared<go::msdr>(params);
    driver_impl::uhd_i::initialize_tx_channels_independent(params, usrp, msdr->get_tx_channels(), address);
    driver_impl::uhd_i::initialize_rx_channels_independent(params, usrp, msdr->get_rx_channels(), address);

    return msdr;
}


std::vector<double> mantis::supported_devices::x400::valid_mcrs = {250e6, 245.76e6};

mantis::errors::error_code mantis::supported_devices::x400::validate( const params::msdr_params& params) {

    // validate MCR
    bool is_mcr_valid = false;
    double requested_mcr = params.master_clock_rate.empty() ? 250e6 : std::stod(params.master_clock_rate); // use 250Mhz as default
    for (const auto &mcr: x400::valid_mcrs) {
        if (mcr == requested_mcr) {
            is_mcr_valid = true;
            break;
        }
    }

    if (!is_mcr_valid) {
        return errors::error_code::INVALID_MCR;
    }

    return errors::error_code::SUCCESS;
}