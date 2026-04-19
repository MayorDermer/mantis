#include "mantis/driver_impl/virtual/socket/virtual_rx_channel_socket.h"
#include "mantis/lib/utilities/prints.h"
#include "mantis/lib/errors/exceptions.h"
#include <thread>

mantis::driver_impl::virtual_i::virtual_rx_channel_socket::virtual_rx_channel_socket(const params::msdr_params &_params,
                                                                                     params::mchannel_params _channel_params)
        : virtual_channel<interfaces::i_rx_channel>(_params, _channel_params), sock(net::msocket(_params.socket_params)) {

    auto err = this->sock.bind();
    if (!errors::succeeded(err)) {
        utils::perror(errors::mantis_errno(err));
        throw mantis::runtime_error(errors::mantis_errno(err));
    }
}


void mantis::driver_impl::virtual_i::virtual_rx_channel_socket::receive(char *data, size_t sample_size,
                                                                        size_t num_samples,
                                                                        go::mrx_metadata &rx_metadata) {

    if (!rx_metadata.has_time_spec) {
        auto err = this->sock.recv(data, sample_size * num_samples);
        if (!mantis::errors::succeeded(err)) {
            utils::pwarn(errors::mantis_errno(err));
        }
        return;
    }

    double time_to_wait_ms = (rx_metadata.time_spec.get_full_secs() * MICRO_FACTOR  + rx_metadata.time_spec.get_frac_secs() * MICRO_FACTOR) - UNIX_TIME_NOW_US_COUNT;

    if (time_to_wait_ms < 0) {
        std::cerr << "L" << std::flush;
    } else {
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<uint64_t>(time_to_wait_ms)));
    }

    auto err = this->sock.recv(data, sample_size * num_samples);
    if (!errors::succeeded(err)) {
        utils::pwarn(errors::mantis_errno(err));
    }

    rx_metadata.has_time_spec = false;
}