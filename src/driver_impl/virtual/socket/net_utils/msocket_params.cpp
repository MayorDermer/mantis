#include "mantis/driver_impl/virtual/socket/net_utils/msocket_params.h"

bool mantis::params::msocket_params::compare(const msocket_params& specific, const msocket_params& general) {

    if (specific.host != general.host && !(specific.host.empty())) {return false;}

    if (specific.port != general.port && specific.port != config::DEFAULT_VIRTUAL_PORT) { return false; }

    return true; // TODO compare other params in the event you allow non-udp or smth
}