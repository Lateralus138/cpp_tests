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
    bool path_exists_or_exit(std::filesystem::path path_, int err_index, int err_msg_index = 2)
    {
      try
      {
        std::error_code ec;
        const auto EXISTS = std::filesystem::exists(path_, ec);
        int ECV = (int) ec.value();
        switch (ECV)
        {
        case 0:
          break;
        default:
          std::cerr << ec.message() << '\n';
          std::exit(ECV);
        }
        if (!EXISTS)
        {
          Globals::Variables::Errors::error = err_index;
          throw std::runtime_error(Globals::Variables::Messages::ERRORMESSAGES[err_msg_index]);
        }
        return EXISTS;
      }
      catch (std::runtime_error & rerr)
      {
        std::cerr << rerr.what() << '\n';
        std::exit(Globals::Variables::Errors::error);
      }
    }
    bool path_is_directory_or_exit(std::filesystem::path path_, int err_index, int err_msg_index = 3)
    {
      try
      {
        std::error_code ec;
        const auto ISDIRECTORY = std::filesystem::is_directory(path_, ec);
        int ECV = (int) ec.value();
        switch (ECV)
        {
        case 0:
          break;
        default:
          std::cerr << ec.message() << '\n';
          std::exit(ECV);
        }
        if (!ISDIRECTORY)
        {
          Globals::Variables::Errors::error = err_index;
          throw std::runtime_error(Globals::Variables::Messages::ERRORMESSAGES[err_msg_index]);
        }
        return ISDIRECTORY;
      }
      catch (std::runtime_error & rerr)
      {
        std::cerr << rerr.what() << '\n';
        std::exit(Globals::Variables::Errors::error);
      }
    }
    bool path_is_regular_file_or_exit(std::filesystem::path path_, int err_index, int err_msg_index = 4)
    {
      try
      {
        std::error_code ec;
        const auto ISREGULARFILE = std::filesystem::is_regular_file(path_, ec);
        int ECV = (int) ec.value();
        switch (ECV)
        {
        case 0:
          break;
        default:
          std::cerr << ec.message() << '\n';
          std::exit(ECV);
        }
        if (!ISREGULARFILE)
        {
          Globals::Variables::Errors::error = err_index;
          throw std::runtime_error(Globals::Variables::Messages::ERRORMESSAGES[err_msg_index]);
        }
        return ISREGULARFILE;
      }
      catch (std::runtime_error & rerr)
      {
        std::cerr << rerr.what() << '\n';
        std::exit(Globals::Variables::Errors::error);
      }
    }
  };
  namespace Variables
  {
    namespace Paths
    {
      const char * PROCDIR = "/proc";
    };
    namespace Errors
    {
      int error = 0;
    };
    namespace Messages
    {
      const char * SUCCESS = "Success...";
      const char * TMA = "Too many arguments passed to this program...";
      const char * NOEXIST = "Does not exist...";
      const char * NODIR = "Not a directory...";
      const char * NOFILE = "Not a regular file...";
      const char * PROCNOEXIST  = "'/proc' does not exist...";
      const char * PROCNODIR    = "'/proc' is not a directory...";
      std::map <int, const char *> ERRORMESSAGES ={
        {0, SUCCESS},
        {1, TMA},
        {2, NOEXIST},
        {3, NODIR},
        {4, NOFILE},
        {5, PROCNOEXIST},
        {6, PROCNODIR}
      };
    };
    namespace Values
    {
      const int ARGMAX = 256;
    };
  };
};
