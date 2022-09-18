#pragma once
#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <string>
namespace Structs
{
  struct Switches
  {
    bool logStdout            = false;
    bool logStderr            = false;
    bool isQuiet              = false;
    std::string optionString  = "fullcache";
  };
};
#endif
