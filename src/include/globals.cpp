#include "globals.h"
#include <iostream>

namespace Globals
{
  namespace Functions
  {
    void rt_err_exit(const char * err_string, int exit)
    {
      std::runtime_error rerr =
              std::runtime_error(err_string);
      if (exit > 0)
        std::cerr << rerr.what() << '\n';
      else
        std::cout << rerr.what() << '\n';
      std::exit(exit);
    }
  };
  namespace Variables
  {
    namespace Paths
    {
      const char * PROCDIR = "/procs";
    };
    namespace Errors
    {
      int error = 0;
    };
    namespace Messages
    {
      const char * SUCCESS = "Success...";
      const char * TMA = "Too many arguments...";
      const char * NOEXIST = "Does not exist...";
      std::map <int, const char *> ERRORMESSAGES ={
        {0, SUCCESS},
        {1, TMA},
        {2, NOEXIST}
      };
    };
    namespace Values
    {
      const int ARGMAX = 256;
    };
  };
};
