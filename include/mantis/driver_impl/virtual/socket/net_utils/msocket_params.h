#pragma once

#include <mantis/config.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace mantis::params {
    /**
     * @brief struct to hold params relevant for socket
     */
    struct MANTIS_API msocket_params {
        //! hostname i.e 0.0.0.0
        std::string host;
        //! ipv4/v6\n @note only ipv4 is supported atm
        int domain = AF_INET;  // default to IPv4
        //! tcp(SOCK_STREAM)/ udp(SOCK_DGRAM)
        int type = config::SOCKET_TYPE;
        //! protocol
        int protocol = 0;  // auto determine
        //! port
        int port = config::DEFAULT_VIRTUAL_PORT;   // default port
        //! socket flags
        int flags = 0;

        /**
         * @brief compare params in a similar fashion to msdr_params and virtual_msdr_params.
         * Will find a match for specific. General may contain more but not less info
         */
        static bool compare(const msocket_params& specific, const msocket_params& general);
    };
}  // namespace mantis::params