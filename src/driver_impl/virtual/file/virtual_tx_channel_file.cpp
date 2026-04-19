#include "mantis/driver_impl/virtual/file/virtual_tx_channel_file.h"
#include "mantis/config.h"
#include <thread>

mantis::driver_impl::virtual_i::virtual_tx_channel_file::virtual_tx_channel_file(params::msdr_params _params,
                                                                                 params::mchannel_params _channel_params)
        : virtual_channel<interfaces::i_tx_channel>(std::move(_params), _channel_params) {

    this->output_file.open(this->get_params().filename, std::ios::binary | std::ios::out);
    if (!this->output_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + this->get_params().filename);
    }
}

void mantis::driver_impl::virtual_i::virtual_tx_channel_file::send(const char *data, size_t sample_size,
                                                                   size_t num_samples,
                                                                   go::mtx_metadata &tx_metadata) {
    if (!tx_metadata.has_time_spec) {
        this->output_file.write(data, sample_size * num_samples);
        tx_metadata.start_of_burst = false;
        return;
    }

    double time_to_wait_ms = (tx_metadata.time_spec.get_full_secs() * MICRO_FACTOR  + tx_metadata.time_spec.get_frac_secs() * MICRO_FACTOR) - UNIX_TIME_NOW_US_COUNT;

    if (time_to_wait_ms < 0) {
        std::cerr << "L" << std::flush;
    } else {
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<uint64_t>(time_to_wait_ms)));
    }

    this->output_file.write(data, sample_size * num_samples);

    tx_metadata.has_time_spec = false;
    tx_metadata.start_of_burst = false;
}


mantis::errors::error_code
mantis::driver_impl::virtual_i::virtual_tx_channel_file::recv_async_message(go::async_mtx_metadata &message,
                                                                            double timeout) {
    return errors::error_code::SUCCESS;
}