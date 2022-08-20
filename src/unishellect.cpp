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
#include <csignal>

using json = nlohmann::json;
using namespace Bench;
using namespace Globals::Functions;
using namespace Globals::Variables::Errors;

int main(int argc, char *argv[])
{
  signal(SIGINT, signal_handler);
  std::cout << "\x1b]0;UniShellect\007" << std::flush;
  std::map<int, Shell> shellMap;
  int userInput;
  // std::string mapMessage(int index, shellMap)
  // TODO : Not done parsing args
  // TODO : Edit HELP message
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
  
  Shell exitShell;
  exitShell.Title = "Exit";
  exitShell.Path = "echo";
  exitShell.Args = "\"Exiting UniShellect\"";
  shellMap[(int)shellMap.size()] = exitShell;

  const int SHELLMAPSZ = (int)shellMap.size();
  const bool isMono = args.ioIsMono;

  if (SHELLMAPSZ > 0)
  {
    for (auto index = 0; index < SHELLMAPSZ; index++)
    {
      std::cout << formattedListMESSAGE(isMono, index, shellMap);
    }
    std::cout << formattedSelectionMESSAGE(isMono, SHELLMAPSZ);
    userInput = getIntegerInput();
  }
  else
  {
    std::cerr << "No entries found.\n";
    return 128;
  }
  const auto tMap = shellMap[userInput];
  const std::string command = tMap.Path + " " + tMap.Args;
  const int command_return = system(command.c_str()) / 256;
  return ((command_return > 0)?command_return:EXIT_SUCCESS);
}