//
// Created by Jon Kler on 6/3/25.
//

#include <mantis/driver_impl/virtual/file/virtual_rx_channel_file.h>
#include <mantis/driver_impl/virtual/file/virtual_tx_channel_file.h>
#include <mantis/driver_impl/virtual/socket/virtual_rx_channel_socket.h>
#include <mantis/driver_impl/virtual/socket/virtual_tx_channel_socket.h>
#include <mantis/driver_impl/virtual/utilities/virtual_utils.h>
#include <mantis/lib/errors/exceptions.h>

mantis::go::mrx_channel::sptr
mantis::driver_impl::virtual_i::virtual_mrx_channel_from_json(json data, size_t channel_num, size_t curr_init) {
    params::msdr_params channel_init_params;
    std::string operating_mode = data["MODE"].get<std::string>();
    if (operating_mode == "FILE") {
        if (data.contains("FILENAME")) {
            channel_init_params.filename = data["FILENAME"].get<std::string>();
        } else {
            channel_init_params.filename = config::BASE_FILENAME + get_formatted_filename("rx", channel_num, curr_init);
        }

        return std::make_shared<virtual_rx_channel_file>(channel_init_params,
                                                         params::mchannel_params{.channel_num=channel_num});
    } else if (operating_mode == "SOCKET") {
        if (data.contains("HOST")) {
            channel_init_params.socket_params.host = data["HOST"].get<std::string>();
        } else {
            channel_init_params.socket_params.host = config::DEFAULT_VIRTUAL_HOST;
        }
        if (data.contains("PORT")) {
            channel_init_params.socket_params.port = data["PORT"].get<int>();
        } else {
            channel_init_params.socket_params.port = config::DEFAULT_VIRTUAL_PORT++; // increment port for next time
        }

        return std::make_shared<virtual_rx_channel_socket>(channel_init_params,
                                                           params::mchannel_params{.channel_num=channel_num});
    } else {
        throw mantis::runtime_error("Unsupported Rx operating mode: " + operating_mode);
    }
}

mantis::go::mtx_channel::sptr
mantis::driver_impl::virtual_i::virtual_mtx_channel_from_json(json data, size_t channel_num, size_t curr_init) {
    params::msdr_params channel_init_params;
    std::string operating_mode = data["MODE"].get<std::string>();
    if (operating_mode == "FILE") {
        if (data.contains("FILENAME")) {
            channel_init_params.filename = data["FILENAME"].get<std::string>();
        } else {
            channel_init_params.filename = config::BASE_FILENAME + get_formatted_filename("tx", channel_num, curr_init);
        }
        return std::make_shared<virtual_tx_channel_file>(channel_init_params,
                                                         params::mchannel_params{.channel_num=channel_num});
    } else if (operating_mode == "SOCKET") {
        if (data.contains("HOST")) {
            channel_init_params.socket_params.host = data["HOST"].get<std::string>();
        } else {
            channel_init_params.socket_params.host = config::DEFAULT_VIRTUAL_HOST;
        }
        if (data.contains("PORT")) {
            channel_init_params.socket_params.port = data["PORT"].get<int>();
        } else {
            channel_init_params.socket_params.port = config::DEFAULT_VIRTUAL_PORT++; // increment port for next time
        }

        return std::make_shared<virtual_tx_channel_socket>(channel_init_params,
                                                           params::mchannel_params{.channel_num=channel_num});
    } else {
        throw mantis::runtime_error("Unsupported Tx operating mode: " + operating_mode);
    }
}


mantis::go::mtx_channel::sptr
mantis::driver_impl::virtual_i::make_virtual_mtx_channel(params::msdr_params params, size_t channel_num,
                                                         size_t curr_init) {
    if (!params.filename.empty()) { //filename overrides everything
        return std::make_shared<driver_impl::virtual_i::virtual_tx_channel_file>(params,
                                                                                 params::mchannel_params{.channel_num=channel_num});
    }

    if (!params.socket_params.host.empty()) { // next is custom socket host
        if (params.socket_params.port == config::DEFAULT_VIRTUAL_PORT) config::DEFAULT_VIRTUAL_PORT++;
        return std::make_shared<driver_impl::virtual_i::virtual_tx_channel_socket>(params,
                                                                                   params::mchannel_params{.channel_num=channel_num});
    }

    if (params.socket_params.port != config::DEFAULT_VIRTUAL_PORT) { // next default host, custom port
        params.socket_params.host = config::DEFAULT_VIRTUAL_HOST;
        return std::make_shared<driver_impl::virtual_i::virtual_tx_channel_socket>(params,
                                                                                   params::mchannel_params{.channel_num=channel_num});

    }

    // use defaults
    if (config::DEFAULT_VIRTUAL_TX_MODE == "FILE") {
        params.filename = config::BASE_FILENAME + get_formatted_filename("tx", channel_num, curr_init);
        return std::make_shared<driver_impl::virtual_i::virtual_tx_channel_file>(params,
                                                                                 params::mchannel_params{.channel_num=channel_num});
    }

    if (config::DEFAULT_VIRTUAL_TX_MODE == "SOCKET") {
        params.socket_params.host = config::DEFAULT_VIRTUAL_HOST; // increment port for next time
        params.socket_params.port = config::DEFAULT_VIRTUAL_PORT++; // increment port for next time
        return std::make_shared<driver_impl::virtual_i::virtual_tx_channel_socket>(params,
                                                                                   params::mchannel_params{.channel_num=channel_num});
    }

    throw mantis::runtime_error("Unsupported DEFAULT_VIRTUAL_TX_MODE: " + config::DEFAULT_VIRTUAL_TX_MODE);
}

mantis::go::mrx_channel::sptr
mantis::driver_impl::virtual_i::make_virtual_mrx_channel(params::msdr_params params, size_t channel_num,
                                                         size_t curr_init) {
    if (!params.filename.empty()) { //filename overrides everything
        return std::make_shared<driver_impl::virtual_i::virtual_rx_channel_file>(params,
                                                                                 params::mchannel_params{.channel_num=channel_num});
    }

    if (!params.socket_params.host.empty()) { // next is custom socket host
        if (params.socket_params.port == config::DEFAULT_VIRTUAL_PORT) config::DEFAULT_VIRTUAL_PORT++;
        return std::make_shared<driver_impl::virtual_i::virtual_rx_channel_socket>(params,
                                                                                   params::mchannel_params{.channel_num=channel_num});
    }

    if (params.socket_params.port != config::DEFAULT_VIRTUAL_PORT) { // next default host, custom port
        params.socket_params.host = config::DEFAULT_VIRTUAL_HOST;
        return std::make_shared<driver_impl::virtual_i::virtual_rx_channel_socket>(params,
                                                                                   params::mchannel_params{.channel_num=channel_num});

    }

    // use defaults
    if (config::DEFAULT_VIRTUAL_RX_MODE == "FILE") {
        params.filename = config::BASE_FILENAME + get_formatted_filename("rx", channel_num, curr_init);
        return std::make_shared<driver_impl::virtual_i::virtual_rx_channel_file>(params,
                                                                                 params::mchannel_params{.channel_num=channel_num});
    }

    if (config::DEFAULT_VIRTUAL_RX_MODE == "SOCKET") {
        params.socket_params.host = config::DEFAULT_VIRTUAL_HOST; // increment port for next time
        params.socket_params.port = config::DEFAULT_VIRTUAL_PORT++; // increment port for next time
        return std::make_shared<driver_impl::virtual_i::virtual_rx_channel_socket>(params,
                                                                                   params::mchannel_params{.channel_num=channel_num});
    }

    throw mantis::runtime_error("Unsupported DEFAULT_VIRTUAL_TX_MODE: " + config::DEFAULT_VIRTUAL_TX_MODE);
}

std::string
mantis::driver_impl::virtual_i::get_formatted_filename(const std::string &rx_tx, size_t channel_num, size_t curr_init) {
    return "_" + rx_tx + "_channel_" + std::to_string(channel_num) + "_init_" + std::to_string(curr_init) +
           config::FILE_EXTENSION;
}