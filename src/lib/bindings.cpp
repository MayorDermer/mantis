#include "mantis/lib/bindings.h"
#include "mantis/detail/device_manager/device_manager.h"

#define GET_D_MAN auto& d_man = mantis::device_manager::get_instance()

mantis::errors::error_code MANTIS_API mantis::init(int num, params::msdr_params msdr_params) {
    GET_D_MAN;
    return d_man.init(num, msdr_params);
}

mantis::errors::error_code MANTIS_API mantis::init_all(params::msdr_params msdr_params) {
    GET_D_MAN;
    return d_man.init_all(msdr_params);
}

std::pair<mantis::errors::error_code, mantis::go::mtx_channel::sptr>
    MANTIS_API mantis::get_tx_channel(const params::msdr_params& msdr_params, size_t channel_num) {
    GET_D_MAN;
    return d_man.get_tx_channel(msdr_params, channel_num);
}

std::pair<mantis::errors::error_code, mantis::go::mrx_channel::sptr>
    MANTIS_API mantis::get_rx_channel(const params::msdr_params& msdr_params, size_t channel_num) {
    GET_D_MAN;
    return d_man.get_rx_channel(msdr_params, channel_num);
}

std::vector<mantis::params::msdr_params> MANTIS_API mantis::find(params::msdr_params params) {
    GET_D_MAN;
    return d_man.find(params);
}

std::vector<mantis::params::msdr_params> MANTIS_API mantis::get_connected() {
    GET_D_MAN;
    return d_man.get_connected();
}
