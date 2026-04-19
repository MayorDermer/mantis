//
// Created by Jon Kler on 5/4/25.
//

#pragma once

#include <chrono>
#include <mantis/driver_impl/uhd/utilities/uhd_utils.h>
#include <mantis/lib/driver_specific/interfaces/i_channel.h>
#include <thread>
#include <uhd/usrp/multi_usrp.hpp>
#include <utility>
#include <mantis/lib/classes/time_tag.h>


namespace mantis::driver_impl::uhd_i {
    /**
     * @brief generic channel uhd implementation
     */
    template<typename ChannelT>
    class uhd_channel : public interfaces::i_channel<ChannelT> {
    public:
        uhd_channel(params::msdr_params params, params::mchannel_params channel_params,
                    uhd::usrp::multi_usrp::sptr _source,
                    uhd::device_addr_t _address) : interfaces::i_channel<ChannelT>(params, channel_params),
                                                   source(std::move(_source)), address(std::move(_address)) {}
        //! get uhd source ptr
        [[nodiscard]] uhd::usrp::multi_usrp::sptr get_source() { return this->source; }

        //! healthcheck
        bool healthcheck() override {
            return uhd_i::healthcheck(this->source);
        }

        //! returns sdr time in microseconds since epoch (assuming user has set it properly)
        time_tag get_time_now() override {
            auto current_sdr_time = source->get_time_now();
            return {current_sdr_time.get_full_secs(), current_sdr_time.get_frac_secs()};
        }

        /**
         * @brief sets sdr time to given timestamp. If time source is "internal" set time now, otherwise, set time next_pps and wait a second to ensure success
         * @param time_stamp timestamp to set sdr time to
         * @return SUCCESS if succeeded INVALID_TIME_SOURCE if time source of sdr and params do not match
         */
        mantis::errors::error_code
        sync(time_tag time_stamp) override {
            int64_t seconds = time_stamp.get_full_secs();
            double partial = time_stamp.get_frac_secs();

            if (this->get_params().time_source == "internal") {
                source->set_time_now({seconds, partial});
                return errors::error_code::SUCCESS;
            }

            if (this->source->get_time_source(0) != this->get_params().time_source) {
                return errors::error_code::INVALID_TIME_SOURCE;
            }

            source->set_time_next_pps({seconds, partial});
            std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep a second to ensure set on next pps

            return errors::error_code::SUCCESS;
        }

        //! set clock source to clock_source
        void set_clock_source(const std::string &clock_source) override {
            this->source->set_clock_source(clock_source);
            this->get_params().clock_source = clock_source;

        }

        //! set time source to time_source
        void set_time_source(const std::string &time_source) override {
            this->source->set_time_source(time_source);
            this->get_params().time_source = time_source;
        }

    private:
        uhd::usrp::multi_usrp::sptr source;
        uhd::device_addr_t address;
    };
}
