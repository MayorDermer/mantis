//
// Created by Jon Kler on 6/3/25.
//

#pragma once

#include <nlohmann/json.hpp>
#include <mantis/lib/classes/mchannel/mrx_channel.h>
#include <mantis/lib/classes/mchannel/mtx_channel.h>

using json = nlohmann::json;

namespace mantis::driver_impl::virtual_i {

    /**
     * @brief create vmtx_channel from json
     * @param data nlohmann::json to use
     * @param channel_num channel num
     * @param curr_init current msdr init
     */
    mantis::go::mtx_channel::sptr virtual_mtx_channel_from_json(json data, size_t channel_num, size_t curr_init);

    /**
     * @brief create vmrx_channel from json
     * @param data nlohmann::json to use
     * @param channel_num channel num
     * @param curr_init current msdr init
     */
    mantis::go::mrx_channel::sptr virtual_mrx_channel_from_json(json data, size_t channel_num, size_t curr_init);

    /**
     * @brief create virtual tx channel from given parameters
     * @param params parameters to use, will also determine whether vmtx_channel is socket/file based
     * @param channel_num channel num
     * @param curr_init current msdr init
     */
    mantis::go::mtx_channel::sptr make_virtual_mtx_channel(params::msdr_params params, size_t channel_num, size_t curr_init);

    /**
     * @brief create virtual rx channel from given parameters
     * @param params parameters to use, will also determine whether vmrx_channel is socket/file based
     * @param channel_num channel num
     * @param curr_init current msdr init
     */
    mantis::go::mrx_channel::sptr make_virtual_mrx_channel(params::msdr_params params, size_t channel_num, size_t curr_init);


    /**
     * @brief returns a filename ending formatted to mantis.\n
     * format is <name>_rx/tx_channel_<channel_num>_init_<curr_init>.config::FILE_EXTENSION\n
     * curr_init is the current msdr(virtuals included) being created.
     * @param rx_tx string "rx" or "tx"
     * @param channel_num current channel num
     * @param curr_init current msdr init
     */
    std::string get_formatted_filename(const std::string& rx_tx, size_t channel_num, size_t curr_init);
}
