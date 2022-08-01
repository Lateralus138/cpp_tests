// -----------------------------------------------
// 'unishellect' - CPP Edition
// Ian Pride @ New Pride Software/Services
// Copyright © 2022
// Tue 12 Jul 2022 07:37:13 PM UTC
// -----------------------------------------------
#include "Bench.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include "json.h"
#include <map>

int main(int argc, char *argv[])
{
  using json = nlohmann::json;
  using namespace Bench;
  using namespace Globals::Functions;
  
  // TODO Voids are temporary, always
  (void) argc; (void) argv;
  
  std::map<int, Shell> shellMap;
  
  // TODO Parse args here.
  try
  {
    std::ifstream confFileStream("/home/flux/.config/UniShellect/unishellect.json");
    if (((int) errno) == 0)
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
            tempShell.Path  = shellIndex["Path"];
            tempShell.Args  = shellIndex["Args"];
            if ((int) tempShell.Title.length() > 0)
            {
              shellMap[shellMap.size()] = tempShell;
            }
          }
        }
        confFileStream.close(); 
      }
      catch (json::exception & err)
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
  catch (std::runtime_error & fail)
  {
    std::cerr << fail.what() << '\n';     
    return (int) errno;
  }
  const int SHELLMAPSZ = (int) shellMap.size();
  if (SHELLMAPSZ > 0)
  {
    for (auto index = 0; index < SHELLMAPSZ; index++)
    {
      const std::string MESSAGE =
        "[\x1b[" + std::to_string(random_color_int(false)) + "m" +
        std::to_string(index) + "\x1b[m] " + shellMap[index].Title + "\n";
      std::cout << MESSAGE;
    }
  }
  else
  {
    std::cerr << "No entries found.\n";
    return 127;
  }
  return EXIT_SUCCESS;
}