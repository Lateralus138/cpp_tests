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
//#include "Bench.h"

int main(int argc, char *argv[])
{
  //  using namespace Bench;
  using namespace Globals::Variables::Errors;
  using namespace Globals::Variables::Messages;
  using namespace Globals::Variables::Values;
  using namespace Globals::Variables::Paths;
  using namespace Globals::Functions;

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

  // TODO Finish HELP message
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
    for (auto & iter : PROC_ITERATOR)
    {
      bool id = iter.is_directory();
      std::cout << iter.path().native().c_str() << " is a directory [" << BOOLS[id] << ']' << std::endl;
    }
  }
  catch (std::filesystem::filesystem_error & fserr)
  {
    (void) fserr;
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

  if (error > 0) rt_err_exit(ERRORMESSAGES[error], error);
  return (EXIT_SUCCESS);
}

