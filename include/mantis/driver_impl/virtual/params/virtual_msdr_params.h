#pragma once

#include <iostream>
#include <mantis/config.h>
#include <mantis/driver_impl/virtual/socket/net_utils/msocket_params.h>

namespace mantis::params {

/**
 * @brief added parameters for virtual SDR device.
 * @param filename The file to read/write data from/to. Rx/Tx channels will add
 * RX/TX_<channel_num> to given filename. Will use socket params if left empty
 * @param socket_params The base socket parameters for the sdr.
 * + TX socket nums + RX socket nums
 * @param tx_channel_count The number of TX channels to create. Default is 1.
 * @param rx_channel_count The number of RX channels to create. Default is 1.
 */
struct MANTIS_API virtual_msdr_params {
    std::string filename;

    mantis::params::msocket_params socket_params{};

    int tx_channel_count = -1;  // Default TX channels
    int rx_channel_count = -1;  // Default RX channels

    [[nodiscard]] static bool compare(const virtual_msdr_params &specific, const virtual_msdr_params& generic);
};
}  // namespace mantis::params