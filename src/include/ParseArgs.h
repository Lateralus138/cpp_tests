#pragma once
#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <vector>
#include <string>
namespace ParseArgs
{
  extern const std::vector<std::string>
    ArgsToVector(int argc_, const char * argv_[], int begin, int end);
  extern const std::string
    ArgsToString(int argc_, const char * argv_[], int begin, int end, std::string delim, int delimInit);
};
#endif
