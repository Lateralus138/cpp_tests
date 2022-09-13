#include "ParsePipe.h"
#include <iostream>
#include <unistd.h>
namespace ParsePipe
{
  const int ARG_MAX = 256;
  const std::vector<std::string>
    PipeToVector(int begin, int end)
  {
    std::vector<std::string> pipeVector;
    std::string input;
    int index = 0;
    end = ((end == 0) ? ARG_MAX : end);
    if (!isatty(fileno(stdin)))
    {
      while (getline(std::cin, input))
      {
        if ((index >= begin) && (index <= end))
        {
          pipeVector.push_back(input);
        }
        index++;
      }
    }
    return pipeVector;
  }
  const std::string
    PipeToString(int begin, int end, std::string delim, int delimInit)
  {
    std::string
      input,
      returnString;
    int index = 0;
    end = ((end == 0) ? 256 : end);
    if (!isatty(fileno(stdin)))
    {
      while (getline(std::cin, input))
      {
        if ((index >= begin) && (index <= end))
        {
          if (index >= delimInit)
          {
            returnString.append(delim);
          }
          returnString.append(input);
        }
        index++;
      }
    }
    return returnString;
  }
};