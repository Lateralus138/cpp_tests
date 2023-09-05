// ╔══════════════════════════════════════════════════════════════════════════════════╗
// ║ Hosts Compress - Aggregate multiple domain names into single lines for local IP  ║
// ║ addresses of 0.0.0.0 and 127.0.0.1.                                              ║
// ║ © 2023 Ian Pride - New Pride Software / Services                                 ║
// ╚══════════════════════════════════════════════════════════════════════════════════╝
#include "pch.h"
int main(int argc, const char* argv[])
{
  ProgramError perror;
  CodePage cp;
  Handle handle{};
  ConsoleMode
    inputConsoleMode,
    outputConsoleMode;
  auto errorTest = [](ProgramError &perror)
  {
    if (perror.getError().value > 0)
    {
      perror.print(true);
      std::exit(perror.getError().value);
    }
  };

  // BEGIN CodePage Init
  cp.setInitCodePage(perror, 1, "Could not get the initial code page.");
  errorTest(perror);
  if (cp.getCurrentCodePage() != CP_UTF8)
  {
    cp.setCodePage(CP_UTF8, perror, 2, "Could not set the current code page.");
    errorTest(perror);
  }
  // END CodePage Init
  // BEGIN InputHandle Init
  handle.setInputHandle(perror, 3, "Could not retrieve console input handle.");
  errorTest(perror);
  // END InputHandle Init
  // BEGIN InitConsoleMode Init
  inputConsoleMode.setInitConsoleMode(handle.getInputHandle(), perror, 4, "");
  errorTest(perror);
  inputConsoleMode.setConsoleMode
  (
    handle.getInputHandle(),
    ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT,
    perror, 5, ""
  );
  errorTest(perror);
  // END InitConsoleMode Init
  // BEGIN InputHandle Init
  handle.setOutputHandle(perror, 5, "Could not retrieve console output handle.");
  errorTest(perror);
  outputConsoleMode.setInitConsoleMode(handle.getOutputHandle(), perror, 4, "");
  errorTest(perror);
  outputConsoleMode.setConsoleMode
  (
    handle.getOutputHandle(),
    ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING,
    perror, 5, ""
  );
  // END InputHandle Init
  SetConsoleTitle(L"Hosts Compressor");

  // TODO Process arguments
  // TODO Continue program

  // BEGIN CodePage Exit
  if (cp.getCurrentCodePage() != cp.getInitCodePage())
  {
    cp.setCodePage(cp.getInitCodePage(), perror, 3, "Could not set the code page to the initial value.");
    errorTest(perror);
  }
  // END CodePage Exit
  // BEGIN InputConsoleMode Exit
  if (inputConsoleMode.getCurrentConsoleMode() != inputConsoleMode.getInitConsoleMode())
  {
    inputConsoleMode.setConsoleMode(handle.getInputHandle(), inputConsoleMode.getInitConsoleMode(), perror, 1, "");
  }
  // END InputConsoleMode Exit
  // BEGIN OutputConsoleMode Exit
  if (outputConsoleMode.getCurrentConsoleMode() != outputConsoleMode.getInitConsoleMode())
  {
    outputConsoleMode.setConsoleMode(handle.getInputHandle(), outputConsoleMode.getInitConsoleMode(), perror, 1, "");
  }
  // END OutputConsoleMode Exit
  return EXIT_SUCCESS;
}