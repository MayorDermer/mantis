//
// Created by Jon Kler on 4/17/25.
//

#pragma once

#include <mantis/lib/driver_specific/interfaces/i_channel.h>
#include <mantis/lib/driver_specific/interfaces/i_rx_channel.h>

namespace mantis::go {
/**
 * @brief generic, non driver-specific rx channel
 * see interfaces::i_channel and interfaces::i_rx_channel for more details
 */
using mrx_channel = interfaces::i_channel<interfaces::i_rx_channel>;
}  // namespace mantis::go
