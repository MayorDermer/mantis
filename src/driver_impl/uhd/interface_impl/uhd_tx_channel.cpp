//
// Created by Jon Kler on 4/20/25.
//

#include "mantis/driver_impl/uhd/interface_impl/uhd_tx_channel.h"
#include "mantis/driver_impl/uhd/utilities/uhd_utils.h"

void mantis::driver_impl::uhd_i::uhd_tx_channel::send(const char *data, size_t sample_size, size_t num_samples,
                                                      go::mtx_metadata &tx_metadata) {
    uhd::tx_metadata_t uhd_tx_md = tx_metadata.convert_to_uhd_md_tx();

    // probably a flush
    if (sample_size  == 0 || num_samples == 0) {
        this->stream->send(data, num_samples, uhd_tx_md, tx_metadata.timeout);
        return;
    }

    size_t samples_sent = 0;
    while (samples_sent < num_samples) {
        size_t offset = samples_sent * sample_size;
        samples_sent += this->stream->send(data + offset, num_samples - samples_sent, uhd_tx_md, tx_metadata.timeout);
    }
     go::mtx_metadata::from_uhd_md_tx(tx_metadata, uhd_tx_md);
}

double mantis::driver_impl::uhd_i::uhd_tx_channel::set_rate(double rate) {
    this->get_source()->set_tx_rate(rate, this->get_channel_num());
    return this->get_rate();
}

double mantis::driver_impl::uhd_i::uhd_tx_channel::set_freq(double freq, std::optional<double> lo) {
    uhd::tune_request_t tune_req = {freq};
    if (lo.has_value()) {
        tune_req = {freq, lo.value() - freq};
    }
    this->get_source()->set_tx_freq(tune_req, this->get_channel_num());

    return this->get_freq();
}

double mantis::driver_impl::uhd_i::uhd_tx_channel::set_gain(double gain) {
    this->get_source()->set_tx_gain(gain, this->get_channel_num());
    return this->get_gain();
}

std::pair<double, mantis::errors::error_code>
mantis::driver_impl::uhd_i::uhd_tx_channel::set_power_ref(double power_dbm) {
    if (!this->can_set_power_ref()) {
        return {0, errors::error_code::POWER_REF_UNAVAILABLE};
    }
    this->get_source()->set_tx_power_reference(power_dbm, this->get_channel_num());
    return this->get_power_ref();
}


double mantis::driver_impl::uhd_i::uhd_tx_channel::get_rate() {
    return this->get_source()->get_tx_rate(this->get_channel_num());
}

double mantis::driver_impl::uhd_i::uhd_tx_channel::get_freq() {
    return this->get_source()->get_tx_freq(this->get_channel_num());
}


double mantis::driver_impl::uhd_i::uhd_tx_channel::get_gain() {
    return this->get_source()->get_tx_gain(this->get_channel_num());
}

std::pair<double, mantis::errors::error_code> mantis::driver_impl::uhd_i::uhd_tx_channel::get_power_ref() {
    if (!this->can_set_power_ref()) {
        return {0, errors::error_code::POWER_REF_UNAVAILABLE};
    }
    return {this->get_source()->get_tx_power_reference(this->get_channel_num()), errors::error_code::SUCCESS};
}

bool mantis::driver_impl::uhd_i::uhd_tx_channel::can_set_power_ref() {
    return this->get_source()->has_tx_power_reference(this->get_channel_num());
}

std::vector<double> mantis::driver_impl::uhd_i::uhd_tx_channel::get_valid_sample_rates() {
    std::vector<uhd::range_t> uhd_range_rates = this->get_source()->get_tx_rates(
            this->get_channel_num()); // unclear why the range_t is needed, using first value
    std::vector<double> rates;
    rates.resize(uhd_range_rates.size());

    for (const auto &range: uhd_range_rates) {
        rates.emplace_back(range.start());
    }

    return rates;
}

mantis::errors::error_code
mantis::driver_impl::uhd_i::uhd_tx_channel::recv_async_message(go::async_mtx_metadata &message, double timeout) {
    uhd::async_metadata_t uhd_md = go::async_mtx_metadata::from_async_mtx_md(message);
    if (!this->stream->recv_async_msg(uhd_md, timeout)) {
        return errors::error_code::TIMEOUT;
    }
    message = go::async_mtx_metadata::to_async_mtx_md(uhd_md);
    return errors::error_code::SUCCESS;
}