#pragma once
#ifndef Globals_H
#define Globals_H
#include <map>

namespace Globals
{
  namespace Functions
  {
    extern void rt_err_exit(const char * err_string, int exit);
  };
  namespace Variables
  {
    namespace Paths
    {
      extern const char * PROCDIR;
    };
    namespace Errors
    {
      extern int error;
    };
    namespace Messages
    {
      extern const char * SUCCESS;
      extern const char * TMA;
      extern const char * NOEXIST;
      extern std::map <int, const char *> ERRORMESSAGES;
    };
    namespace Values
    {
      extern const int ARGMAX;
    };
  };
};

#endif
