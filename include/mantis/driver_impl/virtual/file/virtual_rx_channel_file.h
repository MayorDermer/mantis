#pragma once

#include <fstream>
#include <mantis/driver_impl/virtual/interface_impl/virtual_channel.h>
#include <mantis/lib/driver_specific/interfaces/i_rx_channel.h>


namespace mantis::driver_impl::virtual_i {
    /**
     * @brief virtual rx channel from file.
     * "receives" buffers from the file and loops back to the start upon file completion
     */
    class virtual_rx_channel_file : public virtual_channel<interfaces::i_rx_channel> {
    public:
        virtual_rx_channel_file(params::msdr_params _params, params::mchannel_params _channel_params);

        ~virtual_rx_channel_file() override = default;

        void receive(char *data, size_t sample_size, size_t num_samples, go::mrx_metadata &rx_metadata) override;

    private:
        std::ifstream input_file;
    };
}