#include "ArgumentParser.h"
#include "VolumeController.h"
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[]) {
    try {
        argparser::ArgumentParser parser(argc, argv);

        parser.add_switch_pair("h", "help", "Show this help message", argparser::SwitchType::FLAG, argparser::Requirement::OPTIONAL);
        parser.add_switch_pair("m", "mute", "Mute the audio", argparser::SwitchType::FLAG, argparser::Requirement::OPTIONAL);
        parser.add_switch_pair("u", "unmute", "Unmute the audio", argparser::SwitchType::FLAG, argparser::Requirement::OPTIONAL);
        parser.add_switch_pair("x", "max", "Set volume to maximum (100%)", argparser::SwitchType::FLAG, argparser::Requirement::OPTIONAL);
        parser.add_switch_pair("n", "min", "Set volume to minimum (0%)", argparser::SwitchType::FLAG, argparser::Requirement::OPTIONAL);

        parser.parse();

        if (parser.is_switch_set("help")) {
            parser.print_help("Volume Control Tool - A command-line utility for managing audio volume");
            return 0;
        }

        auto controller = create_volume_controller();

        if (parser.is_switch_set("mute")) {
            controller->mute();
            std::cout << "Audio muted\n";
        }
        else if (parser.is_switch_set("unmute")) {
            controller->unmute();
            std::cout << "Audio unmuted\n";
        }
        else if (parser.is_switch_set("max")) {
            controller->set_max_volume();
            std::cout << "Volume set to maximum (100%)\n";
        }
        else if (parser.is_switch_set("min")) {
            controller->set_min_volume();
            std::cout << "Volume set to minimum (0%)\n";
        }

        const auto& arguments = parser.get_arguments();
        if (!arguments.empty()) {
            int last_value = 0;
            bool has_volume_argument = false;

            for (const auto& arg : arguments) {
                try {
                    if (arg[0] == '+' || arg[0] == '-') {
                        int increment = std::stoi(arg);
                        last_value = increment;
                        has_volume_argument = true;
                    }
                    else {
                        int value = std::stoi(arg);
                        if (value >= 0 && value <= 100) {
                            last_value = value;
                            has_volume_argument = true;
                        }
                        else {
                            std::cerr << "Error: Volume value must be between 0 and 100\n";
                            return 1;
                        }
                    }
                }
                catch (const std::exception&) {
                    std::cerr << "Error: Invalid volume argument '" << arg << "'\n";
                    return 1;
                }
            }

            if (has_volume_argument) {
                float current = controller->get_current_volume();
                int current_percent = static_cast<int>(current * 100);

                if (arguments.back()[0] == '+' || arguments.back()[0] == '-') {
                    int new_percent = current_percent + last_value;
                    if (new_percent < 0) new_percent = 0;
                    if (new_percent > 100) new_percent = 100;
                    controller->set_volume_percent(new_percent);
                    std::cout << "Volume changed from " << current_percent << "% to " << new_percent << "%\n";
                }
                else {
                    controller->set_volume_percent(last_value);
                    std::cout << "Volume set to " << last_value << "%\n";
                }
            }
        }

        if (parser.is_switch_set("mute") || parser.is_switch_set("unmute") ||
            parser.is_switch_set("max") || parser.is_switch_set("min") ||
            !parser.get_arguments().empty()) {
            float current = controller->get_current_volume();
            int current_percent = static_cast<int>(current * 100);
            std::cout << "Current volume: " << current_percent << "%";
            if (controller->is_muted()) {
                std::cout << " (muted)";
            }
            std::cout << "\n";
        }
        else {
            float current = controller->get_current_volume();
            int current_percent = static_cast<int>(current * 100);
            std::cout << "Current volume: " << current_percent << "%";
            if (controller->is_muted()) {
                std::cout << " (muted)";
            }
            std::cout << "\n";
            std::cout << "Use --help for usage information\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
