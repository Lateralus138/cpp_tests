#pragma once
#ifndef PARSEPIPE_H
#define PARSEPIPE_H
#include <vector>
#include <string>
namespace ParsePipe
{
  extern const int ARG_MAX;
  extern const std::vector<std::string>
    PipeToVector(int begin, int end);
  extern const std::string
    PipeToString(int begin, int end, std::string delim, int delimInit);
};
#endif
