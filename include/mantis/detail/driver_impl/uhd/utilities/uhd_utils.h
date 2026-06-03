//
// Created by Jon Kler on 4/15/25.
//

#pragma once

#include <mantis/lib/classes/mchannel/mrx_channel.h>
#include <mantis/lib/classes/mchannel/mtx_channel.h>
#include <uhd/usrp/multi_usrp.hpp>
#include <vector>


namespace mantis::driver_impl::uhd_i {
    /**
     * @brief healthcheck. Checks sdr time, which requires communication with device
     * @return true if healthy, false if not
     */
    bool healthcheck(uhd::usrp::multi_usrp::sptr sdr_ptr);

    /**
     * @brief initializes all tx channels with their own stream.
     * Only use for sdrs that are fully modular. Some sdrs (such as the b200) can't support independent streams on every channel.
     */
    void
    initialize_tx_channels_independent(const params::msdr_params params, const uhd::usrp::multi_usrp::sptr &sdr_ptr,
                                       std::vector<mantis::go::mtx_channel::sptr> &tx_channels,
                                       const uhd::device_addr_t device_address);
    /**
     * @brief initializes all rx channels with their own stream.
     * Only use for sdrs that are fully modular. Some sdrs (such as the b200) can't support independent streams on every channel.
     */
    void
    initialize_rx_channels_independent(const params::msdr_params params, const uhd::usrp::multi_usrp::sptr &sdr_ptr,
                                       std::vector<mantis::go::mrx_channel::sptr> &rx_channels,
                                       const uhd::device_addr_t device_address);

    //! initializes single tx channel with stream from channel_num
    void initialize_single_tx_channel(const params::msdr_params params, const uhd::usrp::multi_usrp::sptr &sdr_ptr,
                                      std::vector<mantis::go::mtx_channel::sptr> &tx_channels,
                                      const uhd::device_addr_t device_address, size_t channel_num);

    //! initializes single rx channel with stream from channel_num
    void initialize_single_rx_channel(const params::msdr_params params, const uhd::usrp::multi_usrp::sptr &sdr_ptr,
                                      std::vector<mantis::go::mrx_channel::sptr> &rx_channels,
                                      const uhd::device_addr_t device_address, size_t channel_num);

    /**
     * @brief inits sdr and return relevant multi_usrp object
     * @param address uhd device addr
     * @param params msdr_params to config by
     */
    [[nodiscard]] uhd::usrp::multi_usrp::sptr init(uhd::device_addr_t address, params::msdr_params &params);
}