// ╔═══════════════════════════════════════════════════════════╗
// ║ 'Beep Frequency' - Execute a beep on a Windows computer.  ║
// ║ © 2023 Ian Pride - New Pride Software / Services          ║
// ╚═══════════════════════════════════════════════════════════╝
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "ArgParser.h"
int main(int argc, const char* argv[])
{
  Parameters params;
  if (argc > 1) ArgParser(argc, argv, params);
  const bool beep_status = Beep(params.beep_frequency, params.beep_duration);
  if (!beep_status) params.error_value = 5;
  return params.error_value;
}