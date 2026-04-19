#pragma once

#include <optional>

namespace mantis::params {
    /**
     * @brief struct used to hold virtual channel params.
     * Don't actually impact anything, just used for simulations
     */
    struct virtual_transceiver_properties {
        //! Sample rate in Hz
        double rate{};
        //! Frequency in Hz
        double frequency{};
        //! Gain in dB
        double gain{};
        //! Power reference in dBm
        double power_ref{};
        //! Optional, LO freq in Hz
        std::optional<double> lo{std::nullopt};
    };
}  // namespace mantis::params