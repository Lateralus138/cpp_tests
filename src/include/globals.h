#pragma once
#ifndef Globals_H
#define Globals_H
#include <map>
#include <filesystem>

namespace Globals
{
  namespace Functions
  {
    extern void rt_err_exit(const char * err_string, int exit);
    extern bool path_exists_or_exit(std::filesystem::path path_, int err_msg_index);
    extern bool path_is_directory_or_exit(std::filesystem::path path_, int err_msg_index);
    extern bool path_is_regular_file_or_exit(std::filesystem::path path_, int err_msg_index);
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
      extern const char * NODIR;
      extern std::map <int, const char *> ERRORMESSAGES;
    };
    namespace Values
    {
      extern const int ARGMAX;
    };
  };
};

#endif
