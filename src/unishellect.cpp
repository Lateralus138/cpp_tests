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
#include <random>

using json = nlohmann::json;
using namespace Bench;

int random_in_range(int begin, int end)
{
  std::random_device rdev;
  std::mt19937 generator(rdev());
  std::uniform_int_distribution<> distribute(begin, end);
  return distribute(generator);
}

int main(int argc, char *argv[])
{
  (void) argc; (void) argv;
  std::map<int, Shell> shellMap;
  
  // TODO Parse args here.
//  start();
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

//      std::cout << "HERE\n";   
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
//  stop();
//  print_duration("\nExecution duration of try-catch ", "\n", Start, Stop);
  const int SHELLMAPSZ = (int) shellMap.size();
  if (SHELLMAPSZ > 0)
  {
    for (auto index = 0; index < SHELLMAPSZ; index++)
    {
      const int RANDOMCOLOR =
      (
        random_in_range(0,1)?
        random_in_range(91, 96):
        random_in_range(31, 36)
      );
      std::cout
        << "[" << "\x1b[" << RANDOMCOLOR << "m" << index << "\x1b[m] " 
        << shellMap[index].Title << '\n';
    }
  }
  else
  {
    std::cerr << "No entries found.\n";
    return 127;
  }
  return EXIT_SUCCESS;
}