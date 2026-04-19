#pragma once

#include <mantis/driver_impl/virtual/params/virtual_transceiver_properties.h>
#include <mantis/lib/driver_specific/interfaces/i_channel.h>
#include <mantis/lib/utilities/time_utils.h>

constexpr size_t MICRO_FACTOR = 1e6;

namespace mantis::driver_impl::virtual_i {
    /**
     * @brief generic virtual channel implementation
     * @tparam ChannelT Channel type (I-rx/i_tx_channel
     */
    template<typename ChannelT>
    class virtual_channel : public interfaces::i_channel<ChannelT> {
    public:
        virtual_channel(params::msdr_params _params, params::mchannel_params _channel_params)
                : interfaces::i_channel<ChannelT>(_params, _channel_params) {}

        ~virtual_channel() override = default;

        //! since virtual channel isn't tied to any device, it always returns healthy
        [[nodiscard]] bool healthcheck() override {
            return true;
        }

        /**
         * @brief virtual channel time is system-time, so always synced
         * @param time_stamp doesn't actually do anything since the channel only uses system time.
         * The argument is there just to keep the API
         * @return SUCCESS
         */
        mantis::errors::error_code sync(time_tag time_stamp) override {
            return errors::error_code::SUCCESS;
        }

        //! return system time now in microseconds
        [[nodiscard]] time_tag get_time_now() override {
            int64_t seconds = UNIX_TIME_NOW_S_COUNT * MICRO_FACTOR;
            double partials = (UNIX_TIME_NOW_MS_COUNT - seconds) / MICRO_FACTOR;
            return {seconds, partials};
        }

        //! simulated setting rate, doesn't actually do anything
        double set_rate(double rate) override {
            this->properties.rate = rate;
            return rate;
        }

        //! simulated setting freq, doesn't actually do anything
        double set_freq(double freq, std::optional<double> lo) override {
            this->properties.frequency = freq;
            return freq;
        }

        //! simulated setting gain, doesn't actually do anything
        double set_gain(double gain) override {
            this->properties.gain = gain;
            return gain;
        }

        //! returns current rate saved in properties
        [[nodiscard]] double get_rate() override { return this->properties.rate; }

        //! returns current freq saved in properties
        [[nodiscard]] double get_freq() override { return this->properties.frequency; }

        //! returns current gain saved in properties
        [[nodiscard]] double get_gain() override { return this->properties.gain; }

        //! returns -1, everything is valid so not applicable
        [[nodiscard]] std::vector<double> get_valid_sample_rates() override {
            return {-1};  // virtual returns some valid sample rates
        }

        //! returns channel properties
        [[nodiscard]] params::virtual_transceiver_properties get_properties() const {
            return this->properties;
        }

        //! "sets" clock source
        void set_clock_source(const std::string &clock_source) override {
            this->get_params().clock_source = clock_source;
        }

        //! sets time source
        void set_time_source(const std::string &time_source) override {
            this->get_params().time_source = time_source;
        }


        /**
         * @brief "sets" power ref, doesnt actually do anything other than update the params
         * @return {power set, SUCCESS}
         */
        std::pair<double, mantis::errors::error_code> set_power_ref(double power_dbm) override {
            this->properties.power_ref = power_dbm;
            return {this->properties.power_ref,
                    errors::error_code::SUCCESS};
        }

        //! returns current power ref from params
        std::pair<double, mantis::errors::error_code> get_power_ref() override {
            return {this->properties.power_ref,
                    errors::error_code::SUCCESS};
        }

        //! virtual channel so can always set ref
        bool can_set_power_ref() override { return true; }

    protected:
        params::virtual_transceiver_properties properties;
    };
}  // namespace mantis::driver_impl::virtual_i