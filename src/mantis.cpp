#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <mantis/mantis.h>

namespace po = boost::program_options;

static std::string program_description = "Mantis Utils. Use with --help to see available options.";

int main(int argc, char** argv) {

    bool version;
    bool find;
    bool tx_from_file;
    bool rx_to_file;
    std::string args;
    std::string filename;
    size_t channel_num;
    size_t reps;
    bool repeat;

    po::options_description desc(program_description + "\nOptions");
    auto opts = desc.add_options();
    opts("help,h", "produce help message");
    opts("find,f", po::bool_switch(&find)->default_value(false),
         "find connected devices. may be used with the 'args' option to find specific devices");
    opts("version,v", po::bool_switch(&version)->default_value(false), "print mantis version");
    opts("args", po::value<std::string>(&args)->default_value(""), "device args str. Leave empty to find all");
    opts("tx_from_file,t", po::bool_switch(&tx_from_file)->default_value(false), "transmit from file");
    opts("rx_to_file,r", po::bool_switch(&rx_to_file)->default_value(false), "receive to file");
    opts("filename,F", po::value<std::string>(&filename)->default_value(""),
         "absolute path of file to transmit/receive from");
    opts("channel_num,c", po::value<size_t>(&channel_num)->default_value(0), "channel number for tx/rx. default 0");
    opts("reps,n", po::value<size_t>(&reps)->default_value(1),
         "Number of repetitions for tx_from_file. default 1. Alternatively, use --repeat/-R to repeat indefinitely");
    opts("repeat,R", po::bool_switch(&repeat)->default_value(false),
         "used with tx_from_file/t, repeat tx indefinetly. Alternatively, use --reps/-n to specify a number of "
         "repetitions");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return EXIT_SUCCESS;
    }

    po::notify(vm);

    if (version) {
        std::cout << MANTIS_VERSION << std::endl;
        return EXIT_SUCCESS;
    }

    auto& d_manager = mantis::device_manager::get_instance();

    mantis::params::msdr_params params{};
    if (!args.empty()) {
        if (!mantis::errors::succeeded(mantis::params::msdr_params::from_str(args, params))) {
            throw mantis::runtime_error("Could not parse arg string: " + args);
        }
    }

    if (find) {
        auto found_devices = d_manager.find(params);

        if (found_devices.empty()) {
            std::cout << "No Devices Found\n";
            return EXIT_SUCCESS;
        }

        static int i = 0;
        for (const auto& device_params : found_devices) {
            std::cout << "=================================\n";
            std::cout << "Mantis Device " << std::to_string(i++) << "\n";
            std::cout << "=================================\n";
            std::cout << device_params << std::endl;
            std::cout << "\n\n";
        }

        return EXIT_SUCCESS;
    }

    if (tx_from_file && rx_to_file) {
        mantis::utils::perror("Cannot use --tx_from_file/-t and --rx_to_file/-r at the same time");
        return EXIT_FAILURE;
    }

    if (filename.empty() && (tx_from_file || rx_to_file)) {
        mantis::utils::perror(
            "File path must be provided with --filename/-F when using --tx_from_file/-t or --rx_to_file/-r");
        return EXIT_FAILURE;
    }

    int sample_size;
    if (mantis::config::CPU_SAMPLE_FORMAT == "fc32") {
        sample_size = 8;
    } else if (mantis::config::CPU_SAMPLE_FORMAT == "fc64") {
        // should also not be mantis api, consider compiling with diff library target for these
        sample_size = 16;
    } else {
        mantis::utils::perror("Unknown sample formant");
        return EXIT_FAILURE;
    }
    (void)sample_size; // TODO: this just for unused code warning

    if (tx_from_file) {
        /// try to open file
        std::ifstream file(filename, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            mantis::utils::perror("Failed to open file: " + filename);
            return EXIT_FAILURE;
        }
        auto [err, channel] = d_manager.get_tx_channel(params, channel_num);
        if (!mantis::errors::succeeded(err)) {
            mantis::utils::perror("Failed to Acquire Tx Channel: " + mantis::errors::mantis_errno(err));
            return EXIT_FAILURE;
        }

        std::cout << "Transmitting from file...\n";
    }

    if (rx_to_file) {
        /// try opening file
        std::ofstream file(filename, std::ios::out | std::ios::binary);
        if (!file.is_open()) {
            mantis::utils::perror("Failed to open file: " + filename);
            return EXIT_FAILURE;
        }
        
        auto [err, channel] = d_manager.get_rx_channel(params, channel_num);
        if (!mantis::errors::succeeded(err)) {
            mantis::utils::perror("Failed to Acquire Rx Channel: " + mantis::errors::mantis_errno(err));
            return EXIT_FAILURE;
        }

        std::cout << "Receiving to file...\n";
    }
    return EXIT_SUCCESS;
}
