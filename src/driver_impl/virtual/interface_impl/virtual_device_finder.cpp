#include "mantis/driver_impl/virtual/interface_impl/virtual_device_finder.h"

mantis::errors::error_code mantis::driver_impl::virtual_i::virtual_device_finder::init(
    unsigned int required_num, std::vector<mantis::go::msdr::sptr> &o_initialized_sdrs,
    const params::msdr_params params) {

    if (required_num == 0) {
        return errors::error_code::SUCCESS;  // do nothing
    }

    // since this is a virtual, our initialization should always successful
    for (unsigned int i = 0; i < required_num; ++i) {
        // create a virtual msdr with the params
        mantis::go::msdr::sptr virtual_sdr = std::make_shared<mantis::go::msdr>(params);
        o_initialized_sdrs.push_back(virtual_sdr);
        // this->initialized_devices.push_back(virtual_sdr->params);  // TODO consider virtual desired behavior. need to make sure files and sockets arent inited twice
    }
    return errors::error_code::SUCCESS;
}

size_t mantis::driver_impl::virtual_i::virtual_device_finder::get_num_connected_unused(const params::msdr_params& params) {
    return 0;
}
