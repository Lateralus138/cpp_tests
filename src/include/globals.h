#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
#include <map>

namespace GLOBALS
{
  namespace FUNCTIONS
  {
    extern void rt_err_exit(const char * err_string, int exit);
  };
  namespace VARIABLES
  {
    namespace ERRORS
    {
      extern int error;
    };
    namespace MESSAGES
    {
      extern const char * SUCCESS;
      extern const char * TMA;
      extern std::map <int, const char *> ERRORMESSAGES;
    };
    namespace VALUES
    {
      extern const int ARGMAX;
    };
  };
};

#endif
