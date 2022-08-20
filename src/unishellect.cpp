// -----------------------------------------------
// 'unishellect' - CPP Edition
// Ian Pride @ New Pride Software/Services
// Copyright © 2022
// Tue 12 Jul 2022 07:37:13 PM UTC
// -----------------------------------------------
#include "Bench.h"
#include "globals.h"
#include "ParseArgs.h"
#include <iostream>
#include <fstream>
#include "json.h"
#include <map>

using json = nlohmann::json;
using namespace Bench;
using namespace Globals::Functions;
using namespace Globals::Variables::Errors;
using namespace Globals::Variables::Values;
using namespace Globals::Variables::Messages;
using namespace Globals::Variables::Regex;

int getIntegerInput()
{
  std::string input;
  bool isMatch = false;
  while (!isMatch)
  {
    getline(std::cin, input);
    isMatch = std::regex_match(input, R_UINT);
    if (!isMatch)
    {
      std::cerr << "\r\'" << input << "\' is not an integer, please try again (Ctrl+C to cancel): ";
    }
  }
  return std::stoi(input);
}

int main(int argc, char *argv[])
{
  std::map<int, Shell> shellMap;

  // std::string mapMessage(int index, shellMap)
  // TODO : Not done parsing args
  // TODO : Deal with mono txt after complete.

  // check_arg_max may seem redundant, but may have an impact on
  // a future recursive feature where multiple config files
  // may be used consecutively.
  check_arg_max(argc, argv);

  args.isDefaultConfig = true;

  if (argc > 1)
  {
    ParseArgs args(argc, argv);
    args.parse(1, argc);
  }

  if (args.isDefaultConfig)
  {
    args.configFile = defaultPathOrThrow();
  }

  try
  {
    std::ifstream confFileStream(args.configFile.c_str());
    if (((int)errno) == 0)
    {
      try
      {
        const json data = json::parse(confFileStream);
        for (auto shells : data)
        {
          for (auto const shellIndex : shells)
          {
            Shell tempShell;
            tempShell.Title = shellIndex["Title"];
            tempShell.Path = shellIndex["Path"];
            tempShell.Args = shellIndex["Args"];
            if ((int)tempShell.Title.length() > 0)
            {
              shellMap[shellMap.size()] = tempShell;
            }
          }
        }
        confFileStream.close();
      }
      catch (json::exception &err)
      {
        std::cerr << err.what() << '\n';
        return err.id; // 101
      }
    }
    else
    {
      throw std::runtime_error(strerror(errno));
    }
  }
  catch (std::runtime_error &fail)
  {
    std::cerr << fail.what() << ":\n[" << args.configFile << "]\n";
    return ((int)errno);
  }

  const int SHELLMAPSZ = (int)shellMap.size();

  if (SHELLMAPSZ > 0)
  {
    const bool isMono = args.ioIsMono;
    auto formattedListMESSAGE = [&isMono, &shellMap](int index)
    {
      std::string MESSAGE;
      MESSAGE.append("[");
      if (!isMono)
      {
        MESSAGE.append("\x1b[");
        MESSAGE.append(std::to_string(random_color_int(false)));
        MESSAGE.append("m");
      }
      MESSAGE.append(std::to_string(index));
      if (!isMono)
      {
        MESSAGE.append("\x1b[m");
      }
      MESSAGE.append("] ");
      MESSAGE.append(shellMap[index].Title);
      MESSAGE.append("\n");
      return MESSAGE;
    };
    auto formattedSelectionMESSAGE = [&isMono, &SHELLMAPSZ]()
    {
      std::string MESSAGE = "Make your selection [";
      if (!isMono)
      {
        MESSAGE.append("\x1b[");
        MESSAGE.append(std::to_string(random_color_int(false)));
        MESSAGE.append("m");
      }
      MESSAGE.append("0");
      if (!isMono)
      {
        MESSAGE.append("\x1b[m");
      }
      MESSAGE.append("-");
      if (!isMono)
      {
        MESSAGE.append("\x1b[");
        MESSAGE.append(std::to_string(random_color_int(false)));
        MESSAGE.append("m");
      }
      MESSAGE.append(std::to_string(SHELLMAPSZ - 1));
      if (!isMono)
      {
        MESSAGE.append("\x1b[m");
      }
      MESSAGE.append("]: ");
      return MESSAGE;
    };
    // auto getInput = []()
    // {

    // };
    for (auto index = 0; index < SHELLMAPSZ; index++)
    {
      std::cout << formattedListMESSAGE(index);
    }
    // TODO : unsigned int selection;
    std::cout << formattedSelectionMESSAGE();
    const int INPUT = getIntegerInput();
    // std::string input;
    // bool isMatch = false;
    // while (!isMatch)
    // {
    //   getline(std::cin, input);
    //   isMatch = std::regex_match(input, R_UINT);
    //   if (!isMatch)
    //   {
    //     std::cerr << "\r\'" << input << "\' is not an integer, please try again (Ctrl+C to cancel): ";
    //   }
    // }
  }
  else
  {
    std::cerr << "No entries found.\n";
    return 128;
  }
  return EXIT_SUCCESS;
}