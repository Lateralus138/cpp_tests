#pragma once
#include <string>
#include <vector>
#include "Options.h" // Include Options.h for PrintMessage

const std::string GetWindowsDirectoryAsString(ProgramError &perror, int errorValue, std::string errorMessage);
std::string ColorString(std::string string, int color, Options& options); // Declaration for ColorString
void PrintMessage(std::string message, Options& options);
void PrintMessage(std::vector<std::string> strings, Options& options);