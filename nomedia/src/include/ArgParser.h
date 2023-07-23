#pragma once
#ifndef ARGPARSER_H
#define ARGPARSER_H
#include <regex>
#include <vector>
#include <filesystem>
struct Parameters
{
  std::vector<std::filesystem::path> paths;
  int error_value;
  Parameters(std::vector<std::filesystem::path> &paths, int &error_value) :
    paths(paths),
    error_value(error_value) {}
  Parameters()
  {
    error_value = 0;
  }
  bool operator==(const Parameters& other) const
  {
    return  paths == other.paths &&
            error_value == other.error_value;
  }
};
extern Parameters params;
struct Switches
{
  bool isHelp;
  bool isForce;
  bool isRecurse;
  Switches(bool &isHelp, bool &isForce, bool &isRecurse) :
    isHelp(isHelp),
    isForce(isForce),
    isRecurse(isRecurse) {}
  Switches()
  {
    isHelp = false;
    isForce = false;
    isRecurse = false;
  }
  bool operator==(const Switches &other) const
  {
    return  isHelp == other.isHelp &&
            isForce == other.isForce &&
            isRecurse == other.isRecurse;
  }
};
extern Switches switches;
struct Regex
{
  std::regex help;
  std::regex force;
  std::regex recurse;
  Regex(const std::regex& help, const std::regex& force, const std::regex &recurse) :
    help(help),
    force(force),
    recurse(recurse) {}
  Regex()
  {
    help =
      std::regex("^-([hH]|-[hH][eE][lL][pP])$");
    force =
      std::regex("^-([fF]|-[fF][oO][rR][cC][eE])$");
    recurse =
      std::regex("^-([rR]|-[rR][eE][cC][uU][rR][sS][eE])$");
  }
  bool IsOption(std::string &option);
};
bool ArgParser(int argc, const char* argv[], Parameters& params, Switches &switches);
bool NextArgTest(int index, const std::vector<std::string>& args);
#endif // !ARGPARSER_H
