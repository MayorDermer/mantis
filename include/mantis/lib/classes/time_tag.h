#pragma once

#include <chrono>
#include <mantis/config.h>
#include <mantis/lib/utilities/time_utils.h>

/**
 * The amount of nanoseconds in a single second
 */
static constexpr double nanoseconds_in_second = 1e9;

namespace mantis {
    //! mantis time-tag. struct is split into full seconds and fractional for increased accuracy
    class MANTIS_API time_tag {
        //! full seconds
        int64_t full_seconds;
        //! fractional seconds (decimal)
        double frac_secs;

    public:
        time_tag() = default;

        time_tag(int64_t full_secs, double frac_secs);

        time_tag(int64_t full_secs);

        template<typename TChrono, typename = std::enable_if_t<is_chrono_duration<TChrono>::value>>
        time_tag(TChrono rep)  {
            auto full_secs = std::chrono::duration_cast<std::chrono::seconds>(rep).count();
            auto frac_secs = std::chrono::duration_cast<std::chrono::nanoseconds>(rep - std::chrono::seconds(full_secs)).count();
            double frac_secs_d = static_cast<double>(frac_secs) / nanoseconds_in_second;

            this->full_seconds = full_secs;
            this->frac_secs = frac_secs_d;
        }

        [[nodiscard]] int64_t get_full_secs();
        [[nodiscard]] double get_frac_secs();

        time_tag operator+(time_tag other) const;
        time_tag operator-(time_tag other) const;
        time_tag& operator+=(time_tag other);
        time_tag& operator-=(time_tag other);

        template<typename TChrono, typename = std::enable_if_t<is_chrono_duration<TChrono>::value>>
        time_tag operator+(TChrono rep) const;

        template<typename TChrono, typename = std::enable_if_t<is_chrono_duration<TChrono>::value>>
        time_tag operator-(TChrono rep) const;

        template<typename TChrono, typename = std::enable_if_t<is_chrono_duration<TChrono>::value>>
        time_tag& operator+=(TChrono rep);

        template<typename TChrono, typename = std::enable_if_t<is_chrono_duration<TChrono>::value>>
        time_tag& operator-=(TChrono rep);
    };
}

#include "time_tag.tpp"
