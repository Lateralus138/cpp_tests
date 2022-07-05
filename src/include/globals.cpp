#include "globals.h"
#include <iostream>

namespace GLOBALS
{
  namespace FUNCTIONS
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
    }};
  namespace VARIABLES
          {
    namespace ERRORS
    {
      int error = 0;};
    namespace MESSAGES
    {
      const char * SUCCESS = "Success...";
      const char * TMA = "Too many arguments...";
      std::map <int, const char *> ERRORMESSAGES =
      {
        {0, SUCCESS},
        {1, TMA}
      };};
    namespace VALUES
    {
      const int ARGMAX = 64;};};
};
