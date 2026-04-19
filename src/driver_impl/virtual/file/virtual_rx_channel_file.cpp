#include "mantis/driver_impl/virtual/file/virtual_rx_channel_file.h"
#include <thread>

mantis::driver_impl::virtual_i::virtual_rx_channel_file::virtual_rx_channel_file(params::msdr_params _params,
                                                                                 params::mchannel_params _channel_params)
        : virtual_channel<interfaces::i_rx_channel>(std::move(_params), _channel_params) {

    this->input_file.open(this->get_params().filename, std::ios::binary | std::ios::in);
    if (!this->input_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + this->get_params().filename);
    }
}


void mantis::driver_impl::virtual_i::virtual_rx_channel_file::receive(char *data, size_t sample_size,
                                                                      size_t num_samples,
                                                                      go::mrx_metadata &rx_metadata) {

    double time_to_wait_ms = (rx_metadata.time_spec.get_full_secs() * MICRO_FACTOR  + rx_metadata.time_spec.get_frac_secs() * MICRO_FACTOR) - UNIX_TIME_NOW_US_COUNT;

    if (time_to_wait_ms < 0) {
        std::cerr << "L" << std::flush;
    } else {
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<uint64_t>(time_to_wait_ms)));
    }

    size_t bytes_left = sample_size * num_samples;
    size_t bytes_read = 0;
    char *read_ptr = data;
    while(bytes_left) {
        this->input_file.read(read_ptr, bytes_left);
        bytes_read = this->input_file.gcount();
        if(bytes_read < bytes_left) {
            this->input_file.clear();
            this->input_file.seekg(0, std::ios::beg);
        }
        bytes_left -= bytes_read; // subtract bytes read from total
        read_ptr += bytes_read; // update ptr to new position
    }
}
