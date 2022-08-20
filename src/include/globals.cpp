#include "globals.h"
#include <iostream>
#include <random>

namespace Globals
{
  namespace Functions
  {
//    void rt_err_exit(const char * err_string, int exit)
//    {
//      std::runtime_error rerr =
//              std::runtime_error(err_string);
//      if (exit > 0)
//        std::cerr << rerr.what() << '\n';
//      else
//        std::cout << rerr.what() << '\n';
//      std::exit(exit);
//    }
    bool path_exists_or_exit(std::filesystem::path path_, int err_index, int err_msg_index = 2)
    {
      try
      {
        std::error_code ec;
        const auto EXISTS = std::filesystem::exists(path_, ec);
        const int ECV = (int) ec.value();
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
        const int ECV = (int) ec.value();
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
        const int ECV = (int) ec.value();
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
    int random_in_range(int begin, int end)
    {
      std::random_device rdev;
      std::mt19937 generator(rdev());
      std::uniform_int_distribution<> distribute(begin, end);
      return distribute(generator);
    }
    int random_color_int(bool fullRange)
    {
      int
        darkLow   = 30,
        darkHigh  = 37,
        lightLow  = 90,
        lightHigh = 97;
      if (fullRange == false)
      {
        darkLow++;
        darkHigh--;
        lightLow++;
        lightHigh--;
      }
      return
      (
        random_in_range(0,1)?
        random_in_range(darkLow, darkHigh):
        random_in_range(lightLow, lightHigh)
      );
    }
    void check_arg_max(int argc, char *argv[])
    {
      try
      {
        if (argc > (Globals::Variables::Values::ARGMAX + 1))
        {
          throw std::runtime_error(Globals::Variables::Messages::ERRORMESSAGES[++Globals::Variables::Errors::error]);
        }
      }
      catch (std::runtime_error & rerr)
      {
        std::cerr << rerr.what() << '\n';
        std::exit(Globals::Variables::Errors::error);
      }
    }
    std::filesystem::path defaultPathOrThrow()
    {
      try
      {
        const char *HOMEPATH = getenv("HOME");
        if (HOMEPATH == NULL)
        {
          Globals::Variables::Errors::error = 5;
          throw std::runtime_error(Globals::Variables::Messages::ERRORMESSAGES[Globals::Variables::Errors::error]);
        }
        std::string configPathStr = std::string(HOMEPATH);
        configPathStr.append("/.config/UniShellect/unishellect.json");
        return std::filesystem::path(configPathStr);
      }
      catch (std::runtime_error &err)
      {
        std::cerr << err.what() << '\n';
        std::exit(Globals::Variables::Errors::error);
      }
    }

    int getIntegerInput()
    {
      std::string input;
      bool isMatch = false;
      while (!isMatch)
      {
        getline(std::cin, input);
        isMatch = std::regex_match(input, Globals::Variables::Regex::R_UINT);
        if (!isMatch)
        {
          std::cerr << "\r\'" << input << "\' is not an integer, please try again (Ctrl+C to cancel): ";
        }
      }
      return std::stoi(input);
    }
  };
  namespace Variables
  {
    namespace Regex
    {
      const std::regex R_UINT("^[0-9]+$");
    };
    namespace Errors
    {
      int error = 0;
    };
    namespace Messages
    {
      const char * SUCCESS = "Success...";
      const char * TMA = "Too many options passed to this program...";
      const char * NOEXIST = "Does not exist...";
      const char * NODIR = "Not a directory...";
      const char * NOFILE = "Not a regular file...";
      const char * NOHOME = "Could not get the value of HOME from the environment...";
      std::map <int, const char *> ERRORMESSAGES = {
        {0, SUCCESS},
        {1, TMA},
        {2, NOEXIST},
        {3, NODIR},
        {4, NOFILE},
        {5, NOHOME}
      };
    };
    namespace Values
    {
      const int ARGMAX = 256;
    };
  };
};
