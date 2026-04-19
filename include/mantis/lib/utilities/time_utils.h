//
// Created by Jon Kler on 5/11/25.
//

#ifndef MANTIS_TIME_UTILS_H
#define MANTIS_TIME_UTILS_H

#include <chrono>
#include <mantis/lib/classes/time_tag.h>

#define UNIX_TIME_NOW std::chrono::system_clock::now().time_since_epoch()

#define UNIX_TIME_NOW_S std::chrono::duration_cast<std::chrono::seconds>(UNIX_TIME_NOW)
#define UNIX_TIME_NOW_MS std::chrono::duration_cast<std::chrono::milliseconds>(UNIX_TIME_NOW)
#define UNIX_TIME_NOW_US std::chrono::duration_cast<std::chrono::microseconds>(UNIX_TIME_NOW)

#define UNIX_TIME_NOW_S_COUNT UNIX_TIME_NOW_S.count()
#define UNIX_TIME_NOW_MS_COUNT UNIX_TIME_NOW_MS.count()
#define UNIX_TIME_NOW_US_COUNT UNIX_TIME_NOW_US.count()

template<typename T>
using is_chrono_duration =
    std::is_base_of<std::chrono::duration<typename T::rep, typename T::period>, T>;

#endif //MANTIS_TIME_UTILS_H
