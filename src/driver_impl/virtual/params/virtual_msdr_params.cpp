#include "mantis/driver_impl/virtual/params/virtual_msdr_params.h"

bool mantis::params::virtual_msdr_params::compare(const virtual_msdr_params &specific, const virtual_msdr_params& generic) {
    if (!(specific.filename == generic.filename || specific.filename.empty())) { return false; }

    if (!msocket_params::compare(specific.socket_params, generic.socket_params)) { return false; }

    if (specific.tx_channel_count != generic.tx_channel_count && specific.tx_channel_count != -1) {return false;}

    if (specific.rx_channel_count != generic.rx_channel_count && specific.rx_channel_count != -1) {return false;}


    return true;
}