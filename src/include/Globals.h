#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
#include <string>
namespace Globals::Functions
{
  extern std::string to_lower(std::string anyCaseString);
  extern std::string time_utc();
};
namespace Globals::Structs
{
  struct ExitCodes
  {
    int value = EXIT_SUCCESS;
    std::string message = "Success.";
  };
};
#endif
