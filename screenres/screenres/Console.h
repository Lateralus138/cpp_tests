#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
#include <Windows.h>
bool CheckAndSetConsoleInput
(
  HANDLE hInput,
  DWORD& lpModeInput,
  DWORD consoleInput
);
bool CheckAndSetConsoleOutput
(
  HANDLE hOutput,
  DWORD& lpModeOutput,
  DWORD consoleOutput
);
void CheckAndSetConsoleTitle(LPCWSTR title);
bool CheckAndSetConsoleCP(unsigned int cp, unsigned int& current_cp);
#endif // !CONSOLE_H


