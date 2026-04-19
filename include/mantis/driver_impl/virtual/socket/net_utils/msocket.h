#pragma once

#include "msocket_params.h"
#include <arpa/inet.h>
#include <mantis/config.h>
#include <mantis/lib/errors/error_codes.h>

namespace mantis::net {
    /**
     * @brief standard socket wrapper tailored for mantis
     */
    class MANTIS_API msocket {
    public:
        msocket(params::msocket_params _sock_params);

        ~msocket();

        /**
         * @brief Abstraction of the standard socket connect function
         * @return SOCKET_CONNECTION failure if couldn't connect
         * @return SUCCESS if succeeded
         * @throw mantis::runtime_error if invalid host used
         */
        errors::error_code connect();

        /**
         * @brief Abstraction of the standard socket send function this call is BLOCKING
         * until data is sent or something goes wrong
         * @param data data to send
         * @param size size of data in bytes
         * @return SUCCESS if succeeded
         * @return TOTAL_SOCKET_SEND_FAILURE if no bytes sent
         * @return PARTIAL_SOCKET_SEND_FAILURE if some bytes sent
         */
        errors::error_code send(const char *data, size_t size);

        /**
         * @brief Creates and binds socket. Also tries to listen to a single client if relevant
         * @return SUCCESS on success
         * @return FAILED_TO_GET_SOCKET_FD if could not create socket
         * @return FAILED_TO_BIND if could not bind
         * @return FAILED_TO_LISTEN if could not listen
         * @throw mantis::runtime_error if given bad socket params and cant convert to valid net address
         */
        errors::error_code bind();

        /**
         * @brief Abstraction of standard socket recv. On failure, will either attempt to accept() another client if 0 bytes received
         * this call is BLOCKING until data is received or something went wrong
         * @param data buffer to receive into
         * @param size buffer size
         * @return SUCCESS on success
         * @return TOTAL_SOCKET_RECV_FAILURE if no bytes received
         * @return PARTIAL_SOCKET_RECV_FAILURE if some bytes received
         */
        errors::error_code recv(char *data, size_t size);

        /**
         * @brief Abstraction of standard socket accept() function. Updates this->client_fd (or sets this->clien_fd to server fd when in SOCK_DGRAM)
         * @return SUCCESS on success
         * @return FAILED_TO_ACCEPT if could not except
         */
        errors::error_code accept();

    private:
        int sockfd;
        int client_fd;
        sockaddr_in sockaddr;
        sockaddr_in client_sockaddr;
        params::msocket_params sock_params;
    };
}  // namespace mantis