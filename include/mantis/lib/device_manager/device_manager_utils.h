//
// Created by Jon Kler on 5/22/25.
//

#pragma once

#include "device_manager.h"

////TODO do something with this or get rid of it
//namespace mantis::device_manager_utils {
//    /**
//     swaps channel data and msdr data, preserves channel use count
//     this will invalidate the second ptr
//     */
//    void replace_msdr_sptr_channels_and_data(std::shared_ptr<go::msdr> original, std::shared_ptr<go::msdr> replacement) {
//        for (auto original_channel = original->get_tx_channels().begin(), new_channel = replacement->get_tx_channels().begin();
//             original_channel != original->get_tx_channels().end() &&
//             new_channel != replacement->get_tx_channels().end(); original_channel++, new_channel++) {
//            *(*original_channel) = *(*new_channel);
//            (*original_channel).swap(*new_channel);
//        }
//        for (auto original_channel = original->get_rx_channels().begin(), new_channel = replacement->get_rx_channels().begin();
//             original_channel != original->get_rx_channels().end() &&
//             new_channel != replacement->get_rx_channels().end(); original_channel++, new_channel++) {
//            *(*original_channel) = *(*(new_channel));
//            (*original_channel).swap(*new_channel);
//        }
//        original.swap(replacement);
//    }
//}
