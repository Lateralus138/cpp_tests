#include "ParseArgs.h"
#include <iostream>
namespace ParseArgs
{
  void Parse(int argc, const char * argv[], Options & options_)
  {
    options_.isQuiet      = false;
    options_.logStderr    = false;
    options_.logStdout    = false;
    options_.optionString = "default";
  }
};