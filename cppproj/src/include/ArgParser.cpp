#include "ArgParser.h"
#include <vector>
#include <iostream>
bool Regex::IsOption(std::string &option)
{
  return  std::regex_match(option, help) ||
          std::regex_match(option, main) ||
          std::regex_match(option, prebuild) ||
          std::regex_match(option, class_) ||
          std::regex_match(option, directory);
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
bool ArgParser(int argc, const char* argv[], Parameters& params, Switches &switches)
{
  Regex regex;
  const std::vector<std::string> args(argv + 1, argv + argc);
  argc--;
  bool skip = false;
  for (int index = 0; index < argc; index++)
  {
    if (skip)
    {
      skip = false;
      continue;
    }
    if (std::regex_match(args[index], regex.help))
    {
      // TODO Change HELP message
      const std::string HELPMESSAGE =
        "\n"
        "Beep Frequency  - A wrapper for the Beep function\n"
        "                  from the Windows API.\n"
        "\n"
        "beepgreq  [/? | /h | /help] |\n"
        "          [[/f | /frequency] <HERTZ>]\n"
        "          [[/d | /duration] <DURATION>]\n"
        "\n"
        "  HERTZ     Hertz integer value of the beep.\n"
        "  DURATION  Duration integer value of the beep.\n"
        "\n"
        "  /?, /h, /help   This help screen.\n"
        "  /f, /frequency  The beep's frequency in hertz\n"
        "  /d, /duration   The duration of the beep in\n"
        "                  milliseconds.\n"
        "\n";
      std::cout << HELPMESSAGE;
      switches.is_help = true;
      return true;
    }
    if (std::regex_match(args[index], regex.main))
    {
      bool HASARG = NextArgTest(index, args);
      if (!HASARG)
      {
        params.error_value = 1;
        return false;
      }
      int next_index = index + 1;
      std::string next_arg = args[next_index];
      if (regex.IsOption(next_arg))
      {
        std::string message = "Invalid option for [";
        message.append(args[index]);
        message.append("]\n");
        std::cerr << message;
        params.error_value = 2;
        return false;
      }
      params.main_name = next_arg;
      skip = true;
      continue;
    }
    if (std::regex_match(args[index], regex.class_))
    {
      bool HASARG = NextArgTest(index, args);
      if (!HASARG)
      {
        params.error_value = 3;
        return false;
      }
      int next_index = index + 1;
      std::string next_arg = args[next_index];
      if (regex.IsOption(next_arg))
      {
        std::string message = "Invalid option for [";
        message.append(args[index]);
        message.append("]\n");
        std::cerr << message;
        params.error_value = 4;
        return false;
      }
      params.class_names.push_back(next_arg);
      skip = true;
      continue;
    }
    if (std::regex_match(args[index], regex.directory))
    {
      bool HASARG = NextArgTest(index, args);
      if (!HASARG)
      {
        params.error_value = 5;
        return false;
      }
      int next_index = index + 1;
      std::string next_arg = args[next_index];
      if (regex.IsOption(next_arg))
      {
        std::string message = "Invalid option for [";
        message.append(args[index]);
        message.append("]\n");
        std::cerr << message;
        params.error_value = 6;
        return false;
      }
      params.path_name = next_arg;
      skip = true;
      continue;
    }
    if (std::regex_match(args[index], regex.prebuild))
    {
      switches.prebuild_script = true;
      continue;
    }
  }
  return true;
}
