#include <iostream>
#include <mantis/mantis.h>
#include <sched.h>
#include <pthread.h>

static constexpr size_t TX_BUFF_SIZE = 8e6;

void print_timetag(mantis::time_tag& tag) {
    std::cout << "full = " << tag.get_full_secs() << " frac = " << tag.get_frac_secs() << std::endl;
}

int main() {

    mantis::time_tag a(0.0);  // full = 0 frac = 0
    print_timetag(a);

    auto b = a + std::chrono::seconds(1);  // full = 1 frac = 0
    print_timetag(b);

    b += std::chrono::milliseconds(539);  // full = 1 frac = 0.539
    print_timetag(b);

    b -= std::chrono::nanoseconds(240000);  // full = 1 frac = 0.53876
    print_timetag(b);

    auto c = b + std::chrono::minutes(1);  // full = 61 frac = 0.53876
    print_timetag(c);

//    cpu_set_t cpuset;
//    CPU_ZERO(&cpuset);
//    CPU_SET(12, &cpuset);
//
//    std::thread::id o = std::this_thread::get_id();
//    auto nh = *reinterpret_cast<std::thread::native_handle_type*>(&o);
//    int affs = pthread_setaffinity_np(nh, sizeof(cpu_set_t ), &cpuset);
//    if(affs != 0) {
//        std::cout << "UH OH" << std::endl;
//    }
    mantis::utils::pinfo("START");
    auto &manager = mantis::device_manager::get_instance();
    manager.init_all({});

    char *tx_buff = (char *) malloc(9e6);
    char *rx_buff = (char *) malloc(9e6);
    memset(tx_buff, 1, 9e6);
    mantis::params::msdr_params p{};
    p.fpga = "XG";
//    p.socket_params.host;
//    p.filename = "aaa.32fc";

//    std::thread a = std::thread([&]() {
//        cpu_set_t cpuset;
//        CPU_ZERO(&cpuset);
//        CPU_SET(13, &cpuset);
//        int affs = pthread_setaffinity_np(a.native_handle(), sizeof(cpu_set_t ), &cpuset);
//        if(affs != 0) {
//            std::cout << "UH OH" << std::endl;
//        }
//        auto [error_code, tx_channel] = manager.get_tx_channel(p, 0);
//        tx_channel->set_rate(200e6);
//        if (error_code == mantis::errors::error_code::SUCCESS && tx_channel) {
//            (void) tx_channel->sync(UNIX_TIME_NOW_US_COUNT);
//            mantis::go::mtx_metadata g{};
//            g.set_time_spec((UNIX_TIME_NOW_S_COUNT + 2) * 1e6 + 27);
//            std::cout << "Successfully retrieved TX channel." << std::endl;
//            while (true) {
//                if (tx_channel->is_valid()) tx_channel->send(tx_buff, 8, 1e6, g);
//                g.has_time_spec = false;
////            std::cout << *(std::complex<float>*)(tx_buff) << std::flush;
//            }
//        }
//    });

//    std::thread b;
//    b = std::thread([&]() {
////        cpu_set_t cpuset;
////        CPU_ZERO(&cpuset);
////        CPU_SET(14, &cpuset);
////        int affs = pthread_setaffinity_np(b.native_handle(), sizeof(cpu_set_t ), &cpuset);
////        if(affs != 0) {
////            std::cout << "UH OH" << std::endl;
////        }
//        auto [error_code, rx_channel] = manager.get_rx_channel(p, 0);
//        rx_channel->set_rate(100e6);
//        if (error_code == mantis::errors::error_code::SUCCESS && rx_channel) {
//            (void) rx_channel->sync(UNIX_TIME_NOW_US_COUNT);
//            mantis::go::mrx_metadata g{};
//            g.set_time_spec((UNIX_TIME_NOW_S_COUNT + 5) * 1e6 + 27);
//            std::cout << "Successfully retrieved RX channel." << std::endl;
//            while (true) {
//                if (rx_channel->is_valid()) rx_channel->receive(rx_buff, 8, 1e6, g);
//                g.has_time_spec = false;
////            std::cout << *(std::complex<float>*)(tx_buff) << std::flush;
//            }
//        }
//    });
    auto [error_code, rx_channel] = manager.get_rx_channel(p, 0);
    rx_channel->set_rate(100e6);
    if (error_code == mantis::errors::error_code::SUCCESS && rx_channel) {
        (void) rx_channel->sync(UNIX_TIME_NOW_S_COUNT);
        mantis::go::mrx_metadata g{};
        auto st =  UNIX_TIME_NOW_MS_COUNT;
        g.set_time_spec({UNIX_TIME_NOW_S_COUNT + 5, 0.5555});
        bool r{true};
        while (r) {
            if (rx_channel->is_valid()) rx_channel->receive(rx_buff, 8, 1e6, g);
            g.has_time_spec = false;
            r = false;
//            std::cout << *(std::complex<float>*)(tx_buff) << std::flush;
        }
        auto dt =  UNIX_TIME_NOW_MS_COUNT;
        std::cout << "DELTA: " << dt - st << std::endl;

    }
//    while(true) {
//        std::this_thread::sleep_for(std::chrono::seconds(10));
//    }
}
