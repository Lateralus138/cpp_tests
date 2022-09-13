#include "ParseArgs.h"
  namespace ParseArgs
  {
    const std::vector<std::string>
      ArgsToVector(int argc_, const char * argv_[], int begin, int end)
      {
        const std::vector<std::string>
            args_(argv_ + begin, argv_ + ((end <= argc_)?end:argc_));
        return args_;
      }
    const std::string
      ArgsToString(int argc_, const char * argv_[], int begin, int end, std::string delim, int delimInit)
      {
        std::string argTemp;
        end = ((end == 0) ? (argc_ - 1) : end);
        for (int index = begin; index < end; index++)
        {
          if (index >= delimInit)
          {
            argTemp.append(delim);
          }
          argTemp.append(argv_[index]);
        }
        const std::string args_ = argTemp;
        return args_;
      }
  };