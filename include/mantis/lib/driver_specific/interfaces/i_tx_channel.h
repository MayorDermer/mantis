//
// Created by Jon Kler on 4/20/25.
//

#pragma once

#include <mantis/lib/classes/metadata/mtx_metadata.h>
#include <mantis/lib/errors/error_codes.h>
#include <mantis/lib/classes/metadata/async_mtx_metadata.h>
#include <complex>
#include <optional>
#include <span>

namespace mantis::interfaces {
    /**
     * @brief tx channel interface.
     */
    class  i_tx_channel {
    public:
        /**
         * @brief function to transmit data from the data pointer. users should use the templated send instead
         * @param data data ptr to send
         * @param sample_size size of each sample e.g. 8 for complex<float>
         * @param num_samples number of samples to send
         * @param tx_metadata metadata
         */
        virtual void send(const char *data, size_t sample_size, size_t num_samples, go::mtx_metadata &tx_metadata) = 0;

        /**
         * @brief wrapper for send function which auto determines sample size for ease of use
         * @param data data ptr to send
         * @param num_samples number of samples to send
         * @param tx_metadata metadata
         */
        template<typename T>
        void send(T* data, size_t num_samples, go::mtx_metadata &tx_metadata) {
            return send(reinterpret_cast<const char *>(data), sizeof(T), num_samples, tx_metadata);
        }

        /**
         * @brief receive async data from channels (underflows, etc...)
         * @param message metadata to fill
         * @param timeout timeout in seconds to wait
         * @return TIMEOUT if request timed out, SUCCESS if succeeded
         */
        virtual mantis::errors::error_code recv_async_message(go::async_mtx_metadata& message, double timeout) = 0;

    };
}