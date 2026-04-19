#pragma once

#include <fstream>
#include <mantis/lib/driver_specific/interfaces/i_tx_channel.h>
#include <mantis/driver_impl/virtual/interface_impl/virtual_channel.h>

namespace mantis::driver_impl::virtual_i {
    /**
     * @brief virtual tx channel to file
     * "send" all data into file. file is opened in write mode
     * @note file data will be overwritten if initialized witt he same filename twice
     */
    class virtual_tx_channel_file : public virtual_channel<interfaces::i_tx_channel> {
    public:
        virtual_tx_channel_file(params::msdr_params _params, params::mchannel_params _channel_params);

        ~virtual_tx_channel_file() override = default;

        void send(const char *data, size_t sample_size, size_t num_samples,
                  go::mtx_metadata &tx_metadata) override;

        //! just returns success
        mantis::errors::error_code recv_async_message(go::async_mtx_metadata& message, double timeout) override;

    private:
        std::ofstream output_file;
    };
}  // namespace mantis::driver_impl::virtual_i