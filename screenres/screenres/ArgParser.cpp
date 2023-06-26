#include "ArgParser.h"
#include <vector>
#include <iostream>
void ArgParser(int argc, const char* argv[], Switches &switches)
{
  Regex regex;
  std::vector<std::string> args(argv + 1, argv + argc);
  for (unsigned int index = 0; index < (int)args.size(); index++)
  {
    if (std::regex_match(args[index], regex.help))
    {
      const std::string HELPMESSAGE =
        "\n"
        "Screen Resolution - Get Windows screen resolution\n"
        "                    and/or DPI. The default output\n"
        "                    is width, height, and dpi.\n"
        "\n"
        "Example output:     1920 1080 96\n"
        "\n"
        "screenres [/? | /H | /help] | [[/r | /resolution]\n"
        "          | [/w | /width] | [/h | /height]\n"
        "          | [/d | /dpi]] [/f | /format]\n"
        "\n"
        "  /?, /H, /help   This help screen.\n"
        "  /r, /resolution Output is only width and height.\n"
        "  /w, /width      Output is only width.\n"
        "  /h, /height     Output is only height.\n"
        "  /d, /dpi        Output is only dpi.\n"
        "  /f, /format     Format output. E.g. 1920x1080@96\n"
        "\n";
      std::cout << HELPMESSAGE;
      std::exit(EXIT_SUCCESS);
    }
    if (std::regex_match(args[index], regex.resolution))
    {
      switches.width = true;
      switches.height = true;
      switches.dpi = false;
      continue;
    }
    if (std::regex_match(args[index], regex.width))
    {
      switches.width = true;
      switches.height = false;
      switches.dpi = false;
      continue;
    }
    if (std::regex_match(args[index], regex.height))
    {
      switches.width = false;
      switches.height = true;
      switches.dpi = false;
      continue;
    }
    if (std::regex_match(args[index], regex.dpi))
    {
      switches.width = false;
      switches.height = false;
      switches.dpi = true;
      continue;
    }
    if (std::regex_match(args[index], regex.format))
    {
      switches.formatted = true;
      continue;
    }
  }
}