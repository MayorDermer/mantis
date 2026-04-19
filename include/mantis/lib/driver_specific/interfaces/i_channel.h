//
// Created by Jon Kler on 4/20/25.
//

#pragma once

#include <mantis/config.h>
#include <mantis/lib/classes/mchannel/mchannel_params.h>
#include <mantis/lib/classes/time_tag.h>
#include <mantis/lib/classes/msdr/msdr_params.h>
#include <mantis/lib/errors/error_codes.h>
#include <memory>
#include <optional>
#include <utility>


namespace mantis::interfaces {
    /**
     * @brief basic channel interface. Uses CRTP to determine if rx/tx channel to add respective functionality
     */
    template<typename ChannelT>
    class MANTIS_API i_channel : public ChannelT {
    public:
        using sptr = std::shared_ptr<i_channel<ChannelT>>;

        explicit i_channel(params::msdr_params _params, params::mchannel_params _channel_params) : params(std::move(_params)),
                                                                                                   channel_params(
                                                                                                           _channel_params) {}

        virtual ~i_channel() = default;

        /**
         * @brief healthcheck to be implemented by various drivers
         */
        [[nodiscard]] virtual bool healthcheck() = 0;

        /**
         * @brief Syncs SDR to given timestamp. If relevant (passed in msdr_params), will wait for given timeout to check if sdr has a time source, and a clock source.
         * @param unix_timestamp_micro timestamp to sync sdr time to in micro seconds from unix time
         * @return SUCCESS if succeeded, INVALID_TIME_SOURCE if time source of sdr and params do not match
         */
        [[nodiscard]] virtual mantis::errors::error_code sync(time_tag time_stamp) = 0;

        /**
         * @brief get sdr time in microseconds since epoch
         */
        [[nodiscard]] virtual time_tag get_time_now() = 0;

        /**
         * @return channel num
         */
        [[nodiscard]] size_t get_channel_num() const { return this->channel_params.channel_num; }

        /**
         * @brief returns whether or not the sdr is valid (invalidation occurs when an sdr disconnects/ for user defined reasons)
         */
        [[nodiscard]] bool is_valid() const { return this->channel_params.is_valid; }

        /**
         * @return msdr_params belonging to the channel's source
         */
        [[nodiscard]] params::msdr_params& get_params() { return this->params; }

        /**
         * @brief invalidates channel. Doesn't actually do anything if you don't check is_valid() before use
         */
        void invalidate() {
            this->channel_params.is_valid = false;
        }

        /**
         * @brief sets channel rate
         * @param rate new rate
         * @return actual channel rate
         */
        virtual double set_rate(double rate) = 0;

        /**
         * @brief sets channel freq
         * @param freq frequency to set to
         * @param lo lo frequency. Use nullopt to let sdr auto-determine
         * @return actual channel freq
         */
        virtual double set_freq(double freq, std::optional<double> lo) = 0;

        /**
         * @brief sets channel gain
         * @param gain gain to set to
         * @return actual channel gain
         */
        virtual double set_gain(double gain) = 0;

        /**
         * @brief gets channel rate
         * @return actual channel rate
         */
        [[nodiscard]] virtual double get_rate() = 0;

        /**
         * @brief gets channel freq
         * @return actual channel freq
         */
        [[nodiscard]] virtual double get_freq() = 0;

        /**
         * @brief gets channel gain
         * @return actual channel gain
         */
        [[nodiscard]] virtual double get_gain() = 0;


        /**
         * @brief returns list of valid sample rates for channel
         */
        virtual std::vector<double> get_valid_sample_rates() = 0;

        /**
         * @brief sets sdr clock source
         * @param clock_source new clock source
         */
        virtual void set_clock_source(const std::string& clock_source) = 0;

        /**
         * @brief sets sdr time source
         * @param time_source new time source
         */
        virtual void set_time_source(const std::string& time_source) = 0;

         /**
          * @brief attempts to set power ref and returns actual power_ref and an error code indicating whether or not number is valid. it is recommended to use the can_set_power_ref()
          * function before attempting
          * @return {power_ref, SUCCESS} on success
          * {0, POWER_REF_UNAVAILABLE} if cannot set power ref
          * @param power_dbm desired power in dbm
          */
        virtual std::pair<double, errors::error_code> set_power_ref(double power_dbm) = 0;

        /**
         * @brief gets power ref and error code indicating whether or not number is valid
         * @return {power_ref, SUCCESS} on success
         * {0, POWER_REF_UNAVAILABLE} if has no power ref
         */
        [[nodiscard]] virtual std::pair<double, errors::error_code> get_power_ref() = 0;

        /**
         * @brief returns whether or not channel can set power_ref
         */
        [[nodiscard]] virtual bool can_set_power_ref() = 0;


    private:
        params::msdr_params params;
        params::mchannel_params channel_params;
    };
}