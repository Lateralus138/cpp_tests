// -----------------------------------------------
// 'lspids' - ls pids in /proc in Linux
// Ian Pride @ New Pride Software/Services
// Copyright © 2022
// Tue 05 Jul 2022 01:12:38 AM UTC
// -----------------------------------------------

#include "globals.h"
#include "Bench.h"

int main(int argc, char *argv[])
{
  (void) argv;
  using namespace Bench;
  start();
  using namespace GLOBALS::VARIABLES::ERRORS;
  using namespace GLOBALS::VARIABLES::MESSAGES;
  using namespace GLOBALS::VARIABLES::VALUES;
  using namespace GLOBALS::FUNCTIONS;
  stop();
  print_duration("Execution time: ", "\n", Start, Stop);
  if (argc > (ARGMAX + 1)) error = 1;
  if (error > 0) rt_err_exit(ERRORMESSAGES[error], error);
}