//
// Created by Jon Kler on 5/21/25.
//

#ifndef MANTIS_SPIN_LOCK_H
#define MANTIS_SPIN_LOCK_H

#include <atomic>

namespace mantis::utils {
    /**
     * @brief basic spin lock implementation, used by device_manager to ensure thread safety
     */
    class MANTIS_API spin_lock {
    public:
        spin_lock() = default;

        void lock() {
            bool expected = false;
            while (!lock_.compare_exchange_weak(expected, true)) {
                expected = false;
            }
        }

        void unlock() {
            this->lock_.store(false);
        }

        std::atomic_bool lock_{false};
    };
}
#endif //MANTIS_SPIN_LOCK_H
