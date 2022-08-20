#pragma once
#ifndef Globals_H
#define Globals_H
#include <map>
#include <filesystem>
#include <regex>

struct Shell
{
  std::string Title;
  std::string Path;
  std::string Args;
};

namespace Globals
{
  namespace Functions
  {
//    extern void rt_err_exit(const char * err_string, int exit);
    extern bool path_exists_or_exit(std::filesystem::path path_, int err_index, int err_msg_index);
    extern bool path_is_directory_or_exit(std::filesystem::path path_, int err_index, int err_msg_index);
    extern bool path_is_regular_file_or_exit(std::filesystem::path path_, int err_index, int err_msg_index);
    extern int random_in_range(int begin, int end);
    extern int random_color_int(bool fullRange);
    extern void check_arg_max(int argc, char *argv[]);
    extern std::filesystem::path defaultPathOrThrow();
    extern int getIntegerInput();
  };
  namespace Variables
  {
    namespace Regex
    {
      extern const std::regex R_UINT;
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
      extern const char * PROCNOEXIST;
      extern const char * PROCNODIR;
      extern std::map <int, const char *> ERRORMESSAGES;
    };
    namespace Values
    {
      extern const int ARGMAX;
    };
  };
};

#endif
