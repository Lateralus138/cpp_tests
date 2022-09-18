#pragma once
#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <string>
struct Options
{
  bool logStdout;
  bool logStderr;
  bool isQuiet;
  std::string optionString;
};
namespace ParseArgs
{
  extern void Parse(int argc, const char * argv[], Options & opts_);
};
#endif
