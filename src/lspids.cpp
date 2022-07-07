// -----------------------------------------------
// 'lspids' - ls pids in /proc in Linux
// Ian Pride @ New Pride Software/Services
// Copyright © 2022
// Tue 05 Jul 2022 01:12:38 AM UTC
// -----------------------------------------------

#include "globals.h"
#include "ParseArgs.h"
#include <iostream>
#include <filesystem>
#include <regex>

int main(int argc, char *argv[])
{
  using namespace Globals::Variables::Errors;
  using namespace Globals::Variables::Messages;
  using namespace Globals::Variables::Values;
  using namespace Globals::Variables::Paths;
  using namespace Globals::Variables::Regex;
  using namespace Globals::Functions;
  args.delimiter = "\n";
  try
  {
    if (argc > (ARGMAX + 1))
      throw std::runtime_error(ERRORMESSAGES[++error]);
  }
  catch (std::runtime_error & rerr)
  {
    std::cerr << rerr.what() << '\n';
    return error;
  }
  if (argc > 1)
  {
    ParseArgs args(argc, argv);
    args.parse(1, argc);
  }
  const std::filesystem::path PROCPATH(PROCDIR);
  path_exists_or_exit(PROCPATH, 2, 2);
  path_is_directory_or_exit(PROCPATH, 3, 3);
  try
  {
    std::error_code ec;
    const auto PROC_ITERATOR = std::filesystem::directory_iterator(PROCPATH, ec);
    const int ECV = (int) ec.value();
    switch (ECV)
    {
    case 0:
      break;
    default:
      std::cerr << ec.message() << '\n';
      std::exit(ECV);
    }
    int iter_index = 0;
    for (auto & iter : PROC_ITERATOR)
    {
      const bool is_directory = iter.is_directory();
      if (is_directory)
      {
        const std::string DIRNAME =
                iter.path().filename().native().c_str();
        if (std::regex_match(DIRNAME, R_UINT))
        {
          iter_index++;
          if (iter_index > 1)
            std::cout << args.delimiter;
          std::cout << DIRNAME;
        }
      }
    }
    if (!args.formatIsNull)
      std::cout << '\n';
  }
  catch (std::filesystem::filesystem_error & fserr)
  {
    std::cerr
            << "What         : " << fserr.what() << '\n'
            << "Path 1       : " << fserr.path1() << '\n'
            << "Path 2       : " << fserr.path2() << '\n'
            << "Code Value   : " << fserr.code().value() << '\n'
            << "Code Message : " << fserr.code().message() << '\n'
            << "Code Category: " << fserr.code().category().name() << '\n';
    try
    {
      error = 4;
      throw std::runtime_error(ERRORMESSAGES[error]);
    }
    catch (std::runtime_error & rerr)
    {
      std::cerr << rerr.what() << '\n';
      std::exit(error);
    }
  }
  return (EXIT_SUCCESS);
}

