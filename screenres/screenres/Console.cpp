#include "Console.h"
#include "Errors.h"
#include <iostream>
bool CheckAndSetConsoleInput
(
  HANDLE hInput,
  DWORD& lpModeInput,
  DWORD consoleInput
)
{
  bool hasConsoleModeInput = GetConsoleMode(hInput, &lpModeInput);
  if (hasConsoleModeInput)
  {
    SetConsoleMode(hInput, consoleInput);
  }
  else
  {
    std::wcerr << GetLastErrorMessage();
  }
  return hasConsoleModeInput;
}
bool CheckAndSetConsoleOutput
(
  HANDLE hOutput,
  DWORD& lpModeOutput,
  DWORD consoleOutput
)
{
  bool hasConsoleModeOutput = GetConsoleMode(hOutput, &lpModeOutput);
  if (hasConsoleModeOutput)
  {
    SetConsoleMode(hOutput, consoleOutput);
  }
  else
  {
    std::wcerr << GetLastErrorMessage();
  }
  return hasConsoleModeOutput;
}
void CheckAndSetConsoleTitle(LPCWSTR title)
{
  const bool TITLESET = SetConsoleTitleW(title);
  if (!TITLESET)
  {
    std::wcerr << GetLastErrorMessage();
  }
}
bool CheckAndSetConsoleCP(unsigned int cp, unsigned int& current_cp)
{
  current_cp = GetConsoleOutputCP();
  bool CODEPAGESET = false;
  if (cp > 0)
  {
    CODEPAGESET = SetConsoleOutputCP(cp);
  }
  if (!CODEPAGESET)
  {
    std::wcerr << GetLastErrorMessage();
  }
  return CODEPAGESET;
}