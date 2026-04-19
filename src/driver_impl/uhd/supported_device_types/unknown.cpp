//
// Created by Jon Kler on 6/5/25.
//
//
#include "mantis/driver_impl/uhd/supported_device_types/unknown.h"
#include "mantis/lib/utilities/prints.h"
#include "mantis/driver_impl/uhd/utilities/uhd_utils.h"

mantis::errors::error_code mantis::supported_devices::unknown::validate(const params::msdr_params& params) {

    utils::pwarn("Using unsupported UHD device. Skipping config arg validation");

    return errors::error_code::SUCCESS;
}

mantis::go::msdr::sptr mantis::supported_devices::unknown::make(uhd::device_addr_t address, params::msdr_params &params) {

    auto usrp = driver_impl::uhd_i::init(address, params);

    go::msdr::sptr msdr = std::make_shared<go::msdr>(params);
    utils::pwarn("Using unsupported UHD device, attempting to initialize 1 Tx and rx channel");
    driver_impl::uhd_i::initialize_single_tx_channel(params, usrp, msdr->get_tx_channels(), address, 0);
    driver_impl::uhd_i::initialize_single_rx_channel(params, usrp, msdr->get_rx_channels(), address, 0);

    return msdr;
}