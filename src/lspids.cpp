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
  bool PROCEXISTS = path_exists_or_exit(PROCPATH, 2);
  bool PROCISDIR  = path_is_directory_or_exit(PROCPATH, 3);

  if (error > 0) rt_err_exit(ERRORMESSAGES[error], error);
  return (EXIT_SUCCESS);
}

