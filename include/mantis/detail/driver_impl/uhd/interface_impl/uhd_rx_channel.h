//
// Created by Jon Kler on 5/6/25.
//

#pragma once

#include "uhd_channel.h"
#include <mantis/lib/driver_specific/interfaces/i_rx_channel.h>
#include <uhd/usrp/multi_usrp.hpp>
#include <utility>

namespace mantis::driver_impl::uhd_i {
    /**
     * @brief uhd implementation of the mrx_channel (i_channel<i_rx_channel>)
     */
    class uhd_rx_channel : public uhd_channel<interfaces::i_rx_channel> {
    public:
        uhd_rx_channel() = delete;

        uhd_rx_channel(const uhd_rx_channel &other) = delete;

        explicit uhd_rx_channel(params::msdr_params _params, params::mchannel_params _channel_params,
                                uhd::usrp::multi_usrp::sptr _source, uhd::rx_streamer::sptr _stream,
                                uhd::device_addr_t _device_info) : uhd_channel(std::move(_params), _channel_params,
                                                                               std::move(_source),
                                                                               std::move(_device_info)),
                                                                   stream(std::move(_stream)) {}

        void
        receive(char *data, size_t sample_size, size_t num_samples, go::mrx_metadata &rx_metadata) override;

        double set_rate(double rate) override;

        double set_freq(double freq, std::optional<double> lo) override;

        double set_gain(double gain) override;

        double get_rate() override;

        double get_freq() override;

        double get_gain() override;

        std::vector<double> get_valid_sample_rates() override;

        std::pair<double, mantis::errors::error_code> set_power_ref(double power_dbm) override;

        std::pair<double, mantis::errors::error_code> get_power_ref() override;

        bool can_set_power_ref() override;

    private:
        uhd::rx_streamer::sptr stream;
    };
}