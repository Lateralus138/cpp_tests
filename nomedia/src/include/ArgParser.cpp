#include "ArgParser.h"
#include <vector>
#include <iostream>
#include "Functions.h"
bool Regex::IsOption(std::string &option)
{
  return  std::regex_match(option, help) ||
          std::regex_match(option, force) ||
          std::regex_match(option, recurse);
}
bool NextArgTest(int index, const std::vector<std::string>& args)
{
  try
  {
    if ((index + 1) > ((int)args.size() - 1))
    {
      std::string rtmsg = "No argument provided for [";
      rtmsg.append(args[index]);
      rtmsg.append("].\n");
      throw std::runtime_error(rtmsg);
    }
  }
  catch (std::runtime_error& rerr)
  {
    std::cerr << rerr.what();
    return false;
  }
  return true;
}
Parameters params;
Switches switches;
bool ArgParser(int argc, const char* argv[], Parameters& params, Switches &switches)
{
  Regex regex;
  const std::vector<std::string> args(argv + 1, argv + argc);
  argc--;
  for (int index = 0; index < argc; index++)
  {
    if (args[index].empty()) continue;
    if (std::regex_match(args[index], regex.help))
    {
      // TODO Change Help message
      const std::string HELPMESSAGE =
        "\n"
        "CPP Project - Create a custom Linux C++ tree and\n"
        "              files project from the command line.\n"
        "              Customn project style developed by\n"
        "              Ian Pride using a normal (but custom\n"
        "              ) Makefile system (no CMAKE) with a\n"
        "              possible prebuild file to help build\n"
        "              the precompiled header, objects, and\n"
        "              library archive.\n"
        "\n"
        "USAGE:\n"
        "  cppproj [-h | --help] |\n"
        "          [-d | --directory] <DIRECTORY PATH>\n"
        "          [-m | --main] <MAIN FILE NAME>\n"
        "          [-c | --class] <CLASS FILE NAME>\n"
        "          [-p | --prebuild]\n"
        "\n"
        "PARAMETERS:\n"
        "  DIRECTORY PATH:   Parent path to the project.\n"
        "  MAIN FILE NAME:   Name of the main source file\n"
        "                    without the extension.\n"
        "  CLASS FILE NAME:  Create class files by name.\n"
        "                    Each different file name must\n"
        "                    be preceeded by the switch:\n"
        "                    e.g: -c ClassOne -c ClassTwo.\n"
        "\n"
        "SWITCHES:\n"
        "  -h, --help      This help screen.\n"
        "  -d, --directory Project path location.\n"
        "  -m, --main      Main source file name.\n"
        "  -c, --class     Class file name.\n"
        "  -p, --prebuild  Create a prebuild file to build\n"
        "                  precompiled header, object files\n"
        "                  , and library archive file.\n"
        "\n";
      std::cout << HELPMESSAGE;
      switches.isHelp = true;
      return true;
    }
    if (std::regex_match(args[index], regex.force))
    {
      switches.isForce = true;
      continue;
    }
    if (std::regex_match(args[index], regex.recurse))
    {
      switches.isRecurse = true;
      continue;
    }
    std::filesystem::path path(args[index]);
    const bool exists = PathExists(path, params, 5, true);
    if (!exists)
    {
      params.error_value = 6;
      return false;
    }
    const bool isDirectory = IsDirectory(path, params, 7, true);
    if (!isDirectory)
    {
      params.error_value = 8;
      return false;
    }
    params.paths.push_back(std::filesystem::path(args[index]));
  }
  return true;
}
