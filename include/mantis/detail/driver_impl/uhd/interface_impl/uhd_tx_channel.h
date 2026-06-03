//
// Created by Jon Kler on 4/20/25.
//

#pragma once

#include <mantis/lib/driver_specific/interfaces/i_tx_channel.h>
#include "uhd_channel.h"
#include <uhd/usrp/multi_usrp.hpp>
#include <utility>

namespace mantis::driver_impl::uhd_i {
    /**
    * @brief uhd implementation of the mrx_channel (i_channel<i_rx_channel>)
    */
    class uhd_tx_channel : public uhd_channel<interfaces::i_tx_channel> {
    public:
        uhd_tx_channel() = delete;

        uhd_tx_channel(const uhd_tx_channel &other) = delete;


        explicit uhd_tx_channel(params::msdr_params _params, params::mchannel_params _channel_params,
                                uhd::usrp::multi_usrp::sptr _source, uhd::tx_streamer::sptr _stream, uhd::device_addr_t _device_info) : uhd_channel(_params,
                                                                                                    _channel_params,
                                                                                                    std::move(_source),
                                                                                                    std::move(
                                                                                                            _device_info)),
                                                                                        stream(std::move(_stream)) {}

        void send(const char *data, size_t sample_size, size_t num_samples,
                  go::mtx_metadata &tx_metadata) override;

        double set_rate(double rate) override;

        double set_freq(double freq, std::optional<double> lo) override;

        double set_gain(double gain) override;

        std::pair<double, errors::error_code> set_power_ref(double power_ref) override;

        double get_rate() override;

        double get_freq() override;

        double get_gain() override;

        std::pair<double, errors::error_code> get_power_ref() override;

        std::vector<double> get_valid_sample_rates() override;

        bool can_set_power_ref() override;

        mantis::errors::error_code recv_async_message(go::async_mtx_metadata& message, double timeout) override;

    private:
        uhd::tx_streamer::sptr stream;
    };
}