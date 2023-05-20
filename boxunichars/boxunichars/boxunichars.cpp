//////////////////////////////////////////////////
// Box Unicode Characters - Print all the ASCII //
// box characters with their corresponding Alt  //
// codes.                                       //
// © 2023 Ian Pride - New Pride Software /      //
// Services                                     //
//////////////////////////////////////////////////
#include "Globals.h"
#include <Windows.h>
#include <iostream>
#include "resource.h"
#include <chrono>
#include <thread>
#include "BoxUniCharsLib.h"

int main()
{
  HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
  SetConsoleMode(hInput, ENABLE_VIRTUAL_TERMINAL_INPUT);
  HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleMode(hOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleTitleW(L"Box Unicode Characters");
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  const HINSTANCE hInstance = GetModuleHandleW(NULL);
  const HICON hIcon = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_ICON2));
  if (hIcon)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    const HWND HWND_ = GetConsoleWindow();
    if (HWND_ != NULL)
    {
      SendMessageW(HWND_, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }
  }

  std::string output = "";

  BoxUniCharsLib box;

  box.Initiate("alt");
  output = box.Default();
  std::cout << output;

  box.Initiate("hexadecimal");
  output = box.Default();
  std::cout << output;
  
  WaitCheck();
  return EXIT_SUCCESS;
}