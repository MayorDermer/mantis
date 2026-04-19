#pragma once

template<typename TChrono, typename>
mantis::time_tag mantis::time_tag::operator+(TChrono rep) const {
    time_tag tag(rep);
    return *this + tag;
}

template<typename TChrono, typename>
mantis::time_tag mantis::time_tag::operator-(TChrono rep) const {
    time_tag tag(rep);
    return *this - tag;
}

template<typename TChrono, typename>
mantis::time_tag &mantis::time_tag::operator+=(TChrono rep) {
    time_tag tag(rep);

    *this += tag;
    return *this;
}

template<typename TChrono, typename>
mantis::time_tag &mantis::time_tag::operator-=(TChrono rep) {
    time_tag tag(rep);

    *this -= tag;
    return *this;
}
