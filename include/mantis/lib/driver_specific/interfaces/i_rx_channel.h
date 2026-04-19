//
// Created by Jon Kler on 5/6/25.
//

#pragma once

#include <mantis/lib/classes/metadata/mrx_metadata.h>
#include <mantis/lib/errors/error_codes.h>
#include <optional>
#include <span>
#include <vector>

namespace mantis::interfaces {
    /**
     * @brief rx channel interface.
     */
    class i_rx_channel {
    public:
        /**
         * @brief function to receive rx data into the data pointer. users should use the templated receive instead
         * @param data data ptr to read to
         * @param sample_size size of each sample e.g 8 for complex<float>
         * @param num_samples number of samples to receive
         * @param rx_metadata metadata
         */
        virtual void receive(char* data, size_t sample_size, size_t num_samples, go::mrx_metadata &rx_metadata) = 0;

        /**
         * @brief wrapper for receive function which auto determine sample size
         * @param data data ptr to read to
         * @param num_samples number of samples to receive
         * @param rx_metadata metadata
         */
        template<typename T>
        void receive(T* data, size_t num_samples, go::mrx_metadata &rx_metadata) {
            receive(reinterpret_cast<char*>(data),  sizeof(T), num_samples, rx_metadata);
        }
    };
}
