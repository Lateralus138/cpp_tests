#pragma once
#include <string>
#include <vector>
#include "Options.h"      // For Options struct
#include "ProgramError.h" // For ProgramError class

class ArgumentParser
{
private:
  std::vector<std::string> tokens;
public:
  ArgumentParser(int& argc, const char** argv, int start);
  bool optionExists(const std::string& option) const;
  bool optionsExist(const std::vector<std::string>& options) const;
  const std::string& getOption(const std::string& option) const;
  const std::string& getOptions(const std::vector<std::string>& options) const;
};

// Declaration of ParseArguments function
unsigned int ParseArguments(ArgumentParser &argumentParser, Options& options, ProgramError &perror);