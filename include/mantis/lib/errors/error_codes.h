//
// Created by Jon Kler on 3/23/25.
//

#ifndef MANTIS_ERROR_CODES_H
#define MANTIS_ERROR_CODES_H

#include <mantis/config.h>
#include <string>
#include <unordered_map>
#include <map>

namespace mantis {
    /**
     * @brief class containing common mantis error functionality --  codes, errno, success checks
     */
    class MANTIS_API errors {
    public:
        //! general mantis error codes
        enum class error_code {
            //! general success
            SUCCESS,
            //! no sdrs connected to system
            NO_SDRS_CONNECTED,
            //! no sdrs found mathcing param
            NO_SDRS_FOUND,
            //! couldn't init matching sdr num
            INSUFFICIENT_SDRS_FOUND,
            //! couldn't init matching sdr
            NO_MATCHING_SDR,
            //! invalid sdr
            INVALID_SDR,
            //! invalid master clock rate
            INVALID_MCR,
            //! invalid argument
            INVALID_ARGUMENT,
            //! no tx channels detected in msdr
            NO_TX_CHANNELS,
            //! no rx channels detected in msdr
            NO_RX_CHANNELS,
            //! insufficient tx channels detected in msdr.
            INSUFFICIENT_TX_CHANNELS,
            //! insufficient tx channels detected in msdr.
            INSUFFICIENT_RX_CHANNELS,
            //!power ref unavailable (no cal data, not available, etc...)
            POWER_REF_UNAVAILABLE,
            //! failed to connect to socket
            SOCKET_CONECTION_FAILURE,
            //! failed to send data over socket
            TOTAL_SOCKET_SEND_FAILURE,
            //! failed to recv data over socket
            TOTAL_SOCKET_RECV_FAILURE,
            //! failed to send data over socket
            PARTIAL_SOCKET_SEND_FAILURE,
            //! failed to recv some data over socket
            PARTIAL_SOCKET_RECV_FAILURE,
            //! failed to accept client
            FAILED_TO_ACCEPT_CLIENT,
            //! failed to get socket fd
            FAILED_TO_GET_SOCKET_FD,
            //! failed to get socket fd
            FAILED_TO_BIND,
            //! failed to get socket fd
            FAILED_TO_LISTEN,
            //! Channel already issued and not returned
            CHANNEL_IN_USE,
            //! operation timed out
            TIMEOUT,
            //! could not init relevant time_sync
            INVALID_TIME_SOURCE,
        };



        //! get detailed error string for mantis error code
        [[maybe_unused]] static std::string mantis_errno(error_code code);

        //! returns true as long as SUCCEEDED or template arguments (other error codes)
        template<error_code... AdditionalAllowedCodes>
        [[maybe_unused]] static bool succeeded(error_code result) {
            return result == error_code::SUCCESS || ((result == AdditionalAllowedCodes) || ...);
        }

        //! returns true as long error code is NOT one of the template arguments
        template<error_code... NotAllowedCodes>
        [[maybe_unused]] static bool succeeded_as_long_as_not(error_code result) {
            return ((result !=  NotAllowedCodes) && ...);
        }

    private:
        static const std::unordered_map<mantis::errors::error_code, const std::string> get_error_map();
    };
}



#endif //MANTIS_ERROR_CODES_H
