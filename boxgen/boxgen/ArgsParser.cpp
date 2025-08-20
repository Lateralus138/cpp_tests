#include "ArgsParser.h"
#include "stdafx.h"

ArgsParser::ArgsParser(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
}

void ArgsParser::add_argument(const std::string& name, const std::string& description) {
    arg_descriptions[name] = description;
}

void ArgsParser::parse() {
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i].rfind("--", 0) == 0) {
            std::string name = args[i].substr(2);
            if (arg_descriptions.count(name)) {
                if (i + 1 < args.size() && args[i + 1].rfind("--", 0) != 0) {
                    arg_map[name] = args[i + 1];
                    i++;
                } else {
                    arg_map[name] = "";
                }
            }
        } else if (args[i].rfind("-", 0) == 0) {
          std::string name = args[i].substr(1);
          if (arg_descriptions.count(name)) {
            if (i + 1 < args.size() && args[i + 1].rfind("-", 0) != 0) {
              arg_map[name] = args[i + 1];
              i++;
            }
            else {
              arg_map[name] = "";
            }
          }
        }
    }
}

template<typename T>
T ArgsParser::get_value(const std::string& name) const {
    if (arg_map.count(name)) {
        if constexpr (std::is_same_v<T, std::string>) {
            return arg_map.at(name);
        } else if constexpr (std::is_integral_v<T>) {
            return static_cast<int>(std::stoll(arg_map.at(name)));
        } else if constexpr (std::is_floating_point_v<T>) {
            return static_cast<float>(std::stold(arg_map.at(name)));
        }
    }
    throw std::runtime_error("Argument not found: " + name);
}

template int ArgsParser::get_value<int>(const std::string& name) const;
template float ArgsParser::get_value<float>(const std::string& name) const;
template double ArgsParser::get_value<double>(const std::string& name) const;
template std::string ArgsParser::get_value<std::string>(const std::string& name) const;
