
#include "mantis/driver_impl/virtual/socket/net_utils/msocket.h"
#include "mantis/driver_impl/virtual/socket/virtual_tx_channel_socket.h"
#include <mantis/lib/errors/exceptions.h>
#include <mantis/lib/utilities/prints.h>
#include <thread>

static constexpr size_t SLEEP_TIME_ON_NO_CONNECTION_S = 2;

mantis::driver_impl::virtual_i::virtual_tx_channel_socket::virtual_tx_channel_socket(
        const params::msdr_params &_params, const params::mchannel_params &_channel_params)
        : virtual_channel<interfaces::i_tx_channel>(_params, _channel_params), sock(net::msocket(_params.socket_params)) {
    auto err = this->sock.connect();
    while(!errors::succeeded(err)) {
        utils::pwarn("Could not connect to server, Retrying in " + std::to_string(SLEEP_TIME_ON_NO_CONNECTION_S) + "(s) ...");
        std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME_ON_NO_CONNECTION_S));
        err = this->sock.connect();

    }
}

void mantis::driver_impl::virtual_i::virtual_tx_channel_socket::send(
        const char *data, size_t sample_size, size_t num_samples,
        go::mtx_metadata &tx_metadata) {

    if (!tx_metadata.has_time_spec) {
        auto err = this->sock.send(data, sample_size * num_samples);
        if(!errors::succeeded(err)) {
            utils::pwarn(errors::mantis_errno(err));
        }
        tx_metadata.start_of_burst = false;
        return;
    }

    double time_to_wait_ms = (tx_metadata.time_spec.get_full_secs() * MICRO_FACTOR  + tx_metadata.time_spec.get_frac_secs() * MICRO_FACTOR) - UNIX_TIME_NOW_US_COUNT;

    if (time_to_wait_ms < 0) {
        std::cerr << "L" << std::flush;
    } else {
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<uint64_t>(time_to_wait_ms)));
    }

    auto err = this->sock.send(data, sample_size * num_samples);
    if(!errors::succeeded(err)) {
        utils::pwarn(errors::mantis_errno(err));
    }

    tx_metadata.start_of_burst = false;
    tx_metadata.has_time_spec = false;
}

mantis::errors::error_code
mantis::driver_impl::virtual_i::virtual_tx_channel_socket::recv_async_message(go::async_mtx_metadata &message,
                                                                              double timeout) {
    return errors::error_code::SUCCESS;
}
