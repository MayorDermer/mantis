//
// Created by Jon Kler on 5/6/25.
//

#include "mantis/driver_impl/uhd/interface_impl/uhd_rx_channel.h"
#include "mantis/driver_impl/uhd/utilities/uhd_utils.h"
#include "mantis/lib/utilities/time_utils.h"

void mantis::driver_impl::uhd_i::uhd_rx_channel::receive(char *data, size_t sample_size, size_t num_samples,
                                                         go::mrx_metadata &rx_metadata) {
    uhd::rx_metadata_t rx_md = rx_metadata.convert_to_uhd_md_rx();

    uhd::stream_cmd_t stream_cmd{uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE};
    stream_cmd.num_samps = num_samples;
    if (rx_md.has_time_spec) {
        stream_cmd.stream_now = false;
        stream_cmd.time_spec = rx_md.time_spec;
    }
    this->stream->issue_stream_cmd(stream_cmd);

    size_t samples_received = 0;
    while (samples_received < num_samples) {
        size_t offset = samples_received * sample_size;
        samples_received += this->stream->recv(data + offset, num_samples - offset, rx_md, rx_metadata.timeout,
                                               rx_metadata.one_packet);
    }

    go::mrx_metadata::from_uhd_md_rx(rx_metadata, rx_md);
}

double mantis::driver_impl::uhd_i::uhd_rx_channel::set_rate(double rate) {
    this->get_source()->set_rx_rate(rate, this->get_channel_num());
    return this->get_rate();
}

double mantis::driver_impl::uhd_i::uhd_rx_channel::set_freq(double freq, std::optional<double> lo) {
    uhd::tune_request_t tune_req = {freq};
    if (lo.has_value()) {
        tune_req = {freq, lo.value() - freq};
    }
    this->get_source()->set_rx_freq(tune_req, this->get_channel_num());

    return this->get_freq();
}

double mantis::driver_impl::uhd_i::uhd_rx_channel::set_gain(double gain) {
    this->get_source()->set_rx_gain(gain, this->get_channel_num());
    return this->get_gain();
}

double mantis::driver_impl::uhd_i::uhd_rx_channel::get_rate() {
    return this->get_source()->get_rx_rate(this->get_channel_num());
}


double mantis::driver_impl::uhd_i::uhd_rx_channel::get_freq() {
    return this->get_source()->get_rx_freq(this->get_channel_num());
}

double mantis::driver_impl::uhd_i::uhd_rx_channel::get_gain() {
    return this->get_source()->get_rx_gain(this->get_channel_num());
}

std::vector<double> mantis::driver_impl::uhd_i::uhd_rx_channel::get_valid_sample_rates() {
    std::vector<uhd::range_t> uhd_range_rates = this->get_source()->get_rx_rates(
            this->get_channel_num()); // unclear why the range_t is needed, using first value
    std::vector<double> rates;
    rates.resize(uhd_range_rates.size());

    for (const auto &range: uhd_range_rates) {
        rates.emplace_back(range.start());
    }

    return rates;
}

std::pair<double, mantis::errors::error_code>
mantis::driver_impl::uhd_i::uhd_rx_channel::set_power_ref(double power_dbm) {
    if (!this->can_set_power_ref()) {
        return {0, errors::error_code::POWER_REF_UNAVAILABLE};
    }
    this->get_source()->set_rx_power_reference(power_dbm, this->get_channel_num());
    return this->get_power_ref();
}

std::pair<double, mantis::errors::error_code> mantis::driver_impl::uhd_i::uhd_rx_channel::get_power_ref() {
    if (!this->can_set_power_ref()) {
        return {0, errors::error_code::POWER_REF_UNAVAILABLE};
    }
    return {this->get_source()->get_rx_power_reference(this->get_channel_num()), errors::error_code::SUCCESS};
}

bool mantis::driver_impl::uhd_i::uhd_rx_channel::can_set_power_ref() {
    return this->get_source()->has_rx_power_reference(this->get_channel_num());
}