#include "ArgParser.h"
#include <vector>
#include <iostream>
void NextArgTest(int index, const std::vector<std::string>& args, int iferror)
{
  try
  {
    if ((index + 1) > (int)args.size())
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
    std::exit(iferror);
  }
}
void ArgParser(int argc, const char* argv[], Parameters& params)
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
      std::exit(0);
    }
    if (std::regex_match(args[index], regex.frequency))
    {
      params.error_value = 1;
      NextArgTest(index, args, params.error_value);
      int next_index = index + 1;
      std::string next_arg = args[next_index];
      params.error_value = 2;
      if (!std::regex_match(next_arg, regex.integer))
      {
        std::cerr << next_arg << " is not an integer.\n";
        std::exit(params.error_value);
      }
      params.beep_frequency =
        std::stoi(next_arg);
      skip = true;
      continue;
    }
    if (std::regex_match(args[index], regex.duration))
    {
      params.error_value = 3;
      NextArgTest(index, args, params.error_value);
      int next_index = index + 1;
      std::string next_arg = args[next_index];
      params.error_value = 4;
      if (!std::regex_match(next_arg, regex.integer))
      {
        std::cerr << next_arg << " is not an integer.\n";
        std::exit(params.error_value);
      }
      params.beep_duration =
        std::stoi(next_arg);
      skip = true;
      continue;
    }
  }
  params.error_value = 0;
}