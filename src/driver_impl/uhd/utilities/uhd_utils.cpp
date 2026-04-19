//
// Created by Jon Kler on 4/15/25.
//

#include "mantis/driver_impl/uhd/interface_impl/uhd_rx_channel.h"
#include "mantis/driver_impl/uhd/interface_impl/uhd_tx_channel.h"
#include "mantis/driver_impl/uhd/utilities/uhd_utils.h"

bool mantis::driver_impl::uhd_i::healthcheck(uhd::usrp::multi_usrp::sptr sdr_ptr) {
    try {
        sdr_ptr->get_time_now();
    } catch (const std::runtime_error &err) {
        return false;
    }
    return true;
}

void mantis::driver_impl::uhd_i::initialize_tx_channels_independent(const params::msdr_params params,
                                                                    const uhd::usrp::multi_usrp::sptr &sdr_ptr,
                                                                    std::vector<mantis::go::mtx_channel::sptr> &tx_channels,
                                                                    const uhd::device_addr_t device_address) {
    uhd::stream_args_t stream_args{config::CPU_SAMPLE_FORMAT, config::OTW_SDR_FORMAT};

    // TODO consider the init function for this, id the address in the msdr params enough? might be (as in init by channel not sdr)
    size_t total_tx_channels = sdr_ptr->get_tx_num_channels();
    for (size_t curr_channel = 0; curr_channel < total_tx_channels; curr_channel++) {
        stream_args.channels = {curr_channel};
        tx_channels.emplace_back(
                std::make_shared<uhd_tx_channel>(params, params::mchannel_params{.channel_num=curr_channel}, sdr_ptr,
                                                 sdr_ptr->get_tx_stream(stream_args),
                                                 device_address));
    }
}

void mantis::driver_impl::uhd_i::initialize_rx_channels_independent(const params::msdr_params params,
                                                                    const uhd::usrp::multi_usrp::sptr &sdr_ptr,
                                                                    std::vector<mantis::go::mrx_channel::sptr> &rx_channels,
                                                                    const uhd::device_addr_t device_address) {
    uhd::stream_args_t stream_args{config::CPU_SAMPLE_FORMAT, config::OTW_SDR_FORMAT};

    // TODO consider the init function for this, id the address in the msdr params enough? might be (as in init by channel not sdr)
    size_t total_rx_channels = sdr_ptr->get_rx_num_channels();
    for (size_t curr_channel = 0; curr_channel < total_rx_channels; curr_channel++) {
        stream_args.channels = {curr_channel};
        rx_channels.emplace_back(
                std::make_shared<uhd_rx_channel>(params, params::mchannel_params{.channel_num=curr_channel}, sdr_ptr,
                                                 sdr_ptr->get_rx_stream(stream_args),
                                                 device_address));
    }
}


void mantis::driver_impl::uhd_i::initialize_single_tx_channel(const params::msdr_params params,
                                                              const uhd::usrp::multi_usrp::sptr &sdr_ptr,
                                                              std::vector<mantis::go::mtx_channel::sptr> &tx_channels,
                                                              const uhd::device_addr_t device_address,
                                                              size_t channel_num) {
    uhd::stream_args_t stream_args{config::CPU_SAMPLE_FORMAT, config::OTW_SDR_FORMAT};
    stream_args.channels = {channel_num};

    tx_channels.emplace_back(
            std::make_shared<uhd_tx_channel>(params, params::mchannel_params{.channel_num=channel_num}, sdr_ptr,
                                             sdr_ptr->get_tx_stream(stream_args),
                                             device_address));


}

void mantis::driver_impl::uhd_i::initialize_single_rx_channel(const params::msdr_params params,
                                                              const uhd::usrp::multi_usrp::sptr &sdr_ptr,
                                                              std::vector<mantis::go::mrx_channel::sptr> &rx_channels,
                                                              const uhd::device_addr_t device_address,
                                                              size_t channel_num) {
    uhd::stream_args_t stream_args{config::CPU_SAMPLE_FORMAT, config::OTW_SDR_FORMAT};
    stream_args.channels = {channel_num};

    rx_channels.emplace_back(
            std::make_shared<uhd_rx_channel>(params, params::mchannel_params{.channel_num=0}, sdr_ptr,
                                             sdr_ptr->get_rx_stream(stream_args),
                                             device_address));
}

uhd::usrp::multi_usrp::sptr mantis::driver_impl::uhd_i::init(uhd::device_addr_t address, params::msdr_params &params) {
    uhd::device_addr_t final_make_address(address.to_string() + "," + params.get_config_args());
    auto usrp = uhd::usrp::multi_usrp::make(final_make_address);

    usrp->set_clock_source(params.clock_source);
    usrp->set_time_source(params.time_source);

    params = mantis::params::msdr_params::from_uhd_device_addr(address, params);

    return usrp;
}