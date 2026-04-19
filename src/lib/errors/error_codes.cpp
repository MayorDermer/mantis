//
// Created by Jon Kler on 3/23/25.
//
#include "mantis/lib/errors/error_codes.h"

const std::unordered_map<mantis::errors::error_code, const std::string>
mantis::errors::get_error_map() {
    static const std::unordered_map<mantis::errors::error_code,
            const std::string>
            error_code_map = {
            {error_code::SUCCESS, "Operation Successful"},
            {error_code::NO_SDRS_CONNECTED, "No SDRS connected"},
            {error_code::NO_SDRS_FOUND, "No SDRS found"},
            {error_code::NO_MATCHING_SDR, "No Matching SDRS found"},
            {error_code::INSUFFICIENT_SDRS_FOUND, "Insufficient SDR num"},
            {error_code::INVALID_SDR, "SDR failed healthcheck"},
            {error_code::INVALID_MCR, "Invalid Master Clock Rate"},
            {error_code::NO_TX_CHANNELS, "No Tx channels found on msdr"},
            {error_code::NO_RX_CHANNELS, "No Rx channels found on msdr"},
            {error_code::INSUFFICIENT_TX_CHANNELS, "Insufficient Tx channels"},
            {error_code::INSUFFICIENT_RX_CHANNELS, "Insufficient Rx channels"},
            {error_code::POWER_REF_UNAVAILABLE, "Power ref unavailable"},
            {error_code::SOCKET_CONECTION_FAILURE, "Failed to connnect to socket with given params"},
            {error_code::TOTAL_SOCKET_SEND_FAILURE, "Failed to send data over socket"},
            {error_code::TOTAL_SOCKET_RECV_FAILURE, "Failed to recv data over socket"},
            {error_code::PARTIAL_SOCKET_SEND_FAILURE, "Failed to send some data over socket"},
            {error_code::PARTIAL_SOCKET_RECV_FAILURE, "Failed to recv some data over socket"},
            {error_code::CHANNEL_IN_USE, "Requested channel already issued"},
            {error_code::TIMEOUT, "Operation timed out"},
            {error_code::INVALID_ARGUMENT, "Invalid argument"},
            {error_code::INVALID_TIME_SOURCE, "Device time source does not match expected"},
            {error_code::FAILED_TO_ACCEPT_CLIENT, "Failed to accept socket client"},
            {error_code::FAILED_TO_GET_SOCKET_FD, "Failed to get a socket fd"},
            {error_code::FAILED_TO_BIND, "Failed to bind socket to given port"},
            {error_code::FAILED_TO_LISTEN, "Failed to acquire listener"}
    };
    return error_code_map;
}

std::string mantis::errors::mantis_errno(mantis::errors::error_code code) {
    return get_error_map().at(code);
}