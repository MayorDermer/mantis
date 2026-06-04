#include <mantis/config.h>
#include <mantis/detail/device_manager/device_manager.h>

namespace mantis {

    /**
     * @brief connect and initialize a requested number of SDRs.
     * @param num number of SDRs to connect and initialize, 0 to init all. Alternatively call init_all
     * @param msdr_params parameters to use for finding and initializing the
     * SDRs
     * @note the function will initialize the first SDRs matching the given
     * msdr_params. Users should be as specific as possible if a specific SDR is
     * desired.
     * @return error_code::SUCCESS if the operation succeeded
     */
    mantis::errors::error_code MANTIS_API init(int num, params::msdr_params msdr_params);

    /**
     * @brief init and initialize all supported SDRs connected to the system.
     * @param msdr_params parameters to use for finding and initializing the
     * SDRs.
     * @return error_code::SUCCESS if the operation was successful
     */
    mantis::errors::error_code MANTIS_API init_all(params::msdr_params msdr_params);

    /**
     * @brief get a mtx_channel matching the given msdr_params and channel_num.
     * @param msdr_params parameters used to init the relevanr SDR
     * @param channel_num the desired tx channel number of the relevant SDR
     * @note the function will attempt to get a tx channel from the FIRST SDR
     * matching the given parameters. It is recommended users pass as many
     * details as possible in the msdr_params
     * @return error_code::SUCCESS and a mtx_channel::sptr if the operation was
     * successful
     * @return error_code::NO_SDRS_CONNECTED and a nullptr if no SDRs are
     * connected
     * @return error_code::INVALID_SDR and a nullptr if the requested SDR was
     * found but invalidated for some reason (disconnected, failed healthcheck,
     * etc...)
     * @return error_code::NO_MATCHING_SDR and a nullptr if no matching SDR was
     * found
     * @return error_code::NO_TX_CHANNELS and a nullptr if the matching SDR has
     * no tx channels available
     * @return error_code::INSUFFICIENT_TX_CHANNELS and a nullptr if the
     * matching SDR has insufficient tx channels available (total channels <
     * channel_num + 1)
     */
    std::pair<errors::error_code, go::mtx_channel::sptr>
        MANTIS_API get_tx_channel(const params::msdr_params& msdr_params, size_t channel_num);

    /**
     * @brief get a mrx_channel matching the given msdr_params and channel_num.
     * @param msdr_params parameters used to init the relevanr SDR
     * @param channel_num the desired rx channel number of the relevant SDR
     * @note the function will attempt to get a rx channel from the FIRST SDR
     * matching the given parameters. It is recommended users pass as many
     * details as possible in the msdr_params
     * @return error_code::SUCCESS and a mrx_channel::sptr if the operation was successful
     * @return error_code::NO_SDRS_CONNECTED and a nullptr if no SDRs are
     * connected
     * @return error_code::INVALID_SDR and a nullptr if the requested SDR was
     * found but invalidated for some reason (disconnected, failed healthcheck,
     * etc...)
     * @return error_code::NO_MATCHING_SDR and a nullptr if no matching SDR was found
     * @return error_code::INSUFFICIENT_RX_CHANNELS and a nullptr if the
     * requested channel number is greater than the number of rx channels
     * available on the SDR
     * @return error_code::NO_RX_CHANNELS and a nullptr if the matching SDR has
     * no rx channels available
     * @return error_code::INSUFFICIENT_RX_CHANNELS and a nullptr if the
     * matching SDR has insufficient rx channels available (total rx channels <
     * channel_num + 1)
     */
    std::pair<errors::error_code, go::mrx_channel::sptr>
        MANTIS_API get_rx_channel(const params::msdr_params& msdr_params, size_t channel_num);

    /**
     * @brief return vector of params of devices connected to the machine NOT managed by mantis
     * @param params parameters to search by
     */
    std::vector<params::msdr_params> MANTIS_API find(params::msdr_params params);

    /**
     * @brief return vector of params of devices being managed by mantis
     */
    std::vector<params::msdr_params> MANTIS_API get_connected();

} // namespace mantis
