// -----------------------------------------------
// 'lspids' - ls pids in /proc in Linux
// Ian Pride @ New Pride Software/Services
// Copyright © 2022
// Tue 05 Jul 2022 01:12:38 AM UTC
// -----------------------------------------------

#include "globals.h"
#include "ParseArgs.h"
#include <iostream>
#include "Bench.h"

int main(int argc, char *argv[])
{
  (void) argv;
  using namespace Bench;
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
  
  if (argc > 1)
  {
    start();
    ParseArgs args(argc, argv);
    args.parse(1, argc);
    stop();
    print_duration("Execution time: ", "\n", Start, Stop);
  }

  if (error > 0) rt_err_exit(ERRORMESSAGES[error], error);
  return (EXIT_SUCCESS);
}

