#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "ArgParser.h"
#include <filesystem>
bool PathExists(std::filesystem::path path, Parameters &params, int error_code);
void StringAppendIf(bool test, std::string &variable, std::string if_, std::string else_);
bool CreateDirectory(std::filesystem::path path, Parameters &params, int error_code);
bool CreateFile(std::filesystem::path path, std::string content, Parameters &params, int error_code);
#endif // FUNCTIONS_H
