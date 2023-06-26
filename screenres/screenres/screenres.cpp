// ╔═══════════════════════════════════════════════════════════╗
// ║ 'Screen Res' - Get Windows screen resolution and/or DPI.  ║
// ║ © 2023 Ian Pride - New Pride Software / Services          ║
// ╚═══════════════════════════════════════════════════════════╝
#include "Console.h"
#include "ArgParser.h"
#include "ScreenResolution.h"
#include <iostream>
//#include <string>
//const char* to_u8string(std::u8string_view string)
//{
//  return (const char* )string.data();
//}
int main(int argc, const char* argv[])
{
  HANDLE
    hInput = GetStdHandle(STD_INPUT_HANDLE),
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD
    lpModeInput = { 0 },
    lpModeOutput = { 0 },
    consoleInput = ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT,
    consoleOutput = ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  bool
    hasConsoleModeInput = false,
    hasConsoleModeOutput = false,
    hasCodePage = false;
  unsigned int CODEPAGE = 0;
  Switches switches;
  hasConsoleModeInput = CheckAndSetConsoleInput(hInput, lpModeInput, consoleInput);
  hasConsoleModeOutput = CheckAndSetConsoleOutput(hOutput, lpModeOutput, consoleOutput);
  hasCodePage = CheckAndSetConsoleCP(CP_UTF8, CODEPAGE);
  CheckAndSetConsoleTitle(L"🖥️ Screen Resolution 🖥️");
  if (argc > 1) ArgParser(argc, argv, switches);
  const std::string OUTPUT = [switches]()
  {
    Screen screen;
    GetDesktopResolution(screen);
    std::string output;
    if (switches.width)
    {
      output = std::to_string(screen.dpiWidth);
    }
    if (switches.height)
    {
      if (!output.empty())
      {
        output.push_back(switches.formatted?'x':' ');
      }
      output.append(std::to_string(screen.dpiHeight));
    }
    if (switches.dpi)
    {
      if (!output.empty())
      {
        output.push_back(switches.formatted ? '@' : ' ');
      }
      output.append(std::to_string(screen.dpi));
    }
    return static_cast<const std::string>(output);
  }();
  std::cout << OUTPUT << '\n';
  if (hasCodePage) CheckAndSetConsoleCP(CODEPAGE, CODEPAGE);
  if (hasConsoleModeInput) CheckAndSetConsoleInput(hInput, lpModeInput, lpModeInput);
  if (hasConsoleModeOutput) CheckAndSetConsoleOutput(hOutput, lpModeOutput, lpModeOutput);
  return EXIT_SUCCESS;
}