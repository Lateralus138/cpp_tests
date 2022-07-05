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

  try
  {
    std::error_code ec;
    const auto PROCEXISTS = std::filesystem::exists(PROCPATH, ec);
    int ECV = (int) ec.value();
    switch (ECV)
    {
    case 0:
      break;
    default:
      std::cerr << ec.message() << '\n';
      std::exit(ECV);
    }
    if (!PROCEXISTS)
    {
      error = 2;
      throw std::runtime_error(ERRORMESSAGES[error]);
    }
    const auto PROCISDIR = std::filesystem::is_directory(PROCPATH, ec);
    switch (ECV)
    {
    case 0:
      break;
    default:
      std::cerr << ec.message() << '\n';
      std::exit(ECV);
    }
    if (!PROCISDIR)
    {
      error = 3;
      throw std::runtime_error(ERRORMESSAGES[error]);
    }
  }
  catch (std::runtime_error & rerr)
  {
    std::cerr << rerr.what() << '\n';
    std::exit(error);
  }
  
  if (error > 0) rt_err_exit(ERRORMESSAGES[error], error);
  return (EXIT_SUCCESS);
}

