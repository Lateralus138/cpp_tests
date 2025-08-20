#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <concepts>

class ArgsParser {
public:
    ArgsParser(int argc, char** argv);
    void add_argument(const std::string& name, const std::string& description);
    void parse();
    template<typename T>
    T get_value(const std::string& name) const;

private:
    std::vector<std::string> args;
    std::map<std::string, std::string> arg_map;
    std::map<std::string, std::string> arg_descriptions;
};