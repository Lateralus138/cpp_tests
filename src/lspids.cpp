// -----------------------------------------------
// 'lspids' - ls pids in /proc in Linux
// Ian Pride @ New Pride Software/Services
// Copyright © 2022
// Tue 05 Jul 2022 01:12:38 AM UTC
// -----------------------------------------------

#include "globals.h"
#include <iostream>
//#include "Bench.h"

int main(int argc, char *argv[])
{
  (void) argv;
  //  using namespace Bench;
  //  start();
  using namespace Globals::Variables::Errors;
  using namespace Globals::Variables::Messages;
  using namespace Globals::Variables::Values;
  using namespace Globals::Variables::Paths;
  using namespace Globals::Functions;
  //  stop();
  //  print_duration("Execution time: ", "\n", Start, Stop);
//  if (argc > (ARGMAX + 1)) error = 1;
  if (error > 0) rt_err_exit(ERRORMESSAGES[error], error);
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
  return (EXIT_SUCCESS);
}

