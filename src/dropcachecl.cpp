// -----------------------------------------------
// 'dropcachecl' - Edit "drop-caches" file
// Copyright © 2022
// Ian Pride @ New Pride Software/Services
// Sat 17 Sep 2022 13:03:04 CST
// -----------------------------------------------
#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include "Globals.h"
#include <pwd.h>
// namespace filesys = std::std::filesystemtem;
int main(int argc, const char *argv[])
{
  // TODO Add switches
  // -h,--help          // This HELP message
  // -l,--logoutput     // enable stdout logging
  // -L,--logerrors     // enable stderr logging
  // -q,--quiet         // Non-verbose output
  // -x,--logdelete     // Delete '/var/log/dropcachecl.log'
  // -d,--default       // 0
  // -p,--pagecache     // 1
  // -s,--slabobjects   // 2
  // -f,--fullcache     // 3
  // -m,--mode          // specify mode by name or int from the option_map
  bool logStdout  = false;
  bool logStderr  = false;
  bool isQuiet    = false;
  std::string optionString = "fullcache";

  std::ofstream logger("/var/log/dropcachecl.log", std::ios_base::app);
  const std::filesystem::path dropCachesPath("/proc/sys/vm/drop_caches");
  Globals::Structs::ExitCodes genericCode;
  std::map<std::string, int> option_map =
  {
    {"default",     0}, {"0", 0},
    {"pagecache",   1}, {"1", 1},
    {"slabobjects", 2}, {"2", 2},
    {"fullcache",   3}, {"3", 3}
  };
  std::ofstream ofile(dropCachesPath.native().c_str());
  if (ofile.is_open())
  {
    ofile << option_map[optionString];
    if (logStdout && logger.is_open())
    {
      std::string logMessage
      (
        "Drop Cache set to [" + std::to_string(option_map[optionString]) +
        ":" + optionString + "] @ " + Globals::Functions::time_utc() + "\n"
      );
      logger << logMessage;
    }
    ofile.close();
  }
  else
  {
    try
    {
      genericCode.value = 2;
      genericCode.message =
        std::string
        (
          "Could not open '" +
          dropCachesPath.native() +
          "' for writing.\nDo you have root privileges?"
        );
      throw genericCode;
    }
    catch(Globals::Structs::ExitCodes & code)
    {
      std::cerr << code.message << '\n';
      if (logStderr && logger.is_open())
      {
        const std::string logMessage =
          "Could not open'" +
          dropCachesPath.native() + "' for writing @ " +
          Globals::Functions::time_utc() + "\n";
        logger << logMessage;
        logger.close();
      }
      std::exit(code.value);
    }
  }
  if (logger.is_open())
  {
    logger.close();
  }
  return genericCode.value;
}
