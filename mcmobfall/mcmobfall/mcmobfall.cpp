//////////////////////////////////////////////////
// MC Mob Fall - Calculate fall distance        //
// to bring a mob to half a heart in            //
// Minecraft.                                   //
// © 2023 Ian Pride - New Pride Software        //
// / Services                                   //
//////////////////////////////////////////////////
#include <Windows.h>
#include <iostream>
#include "Globals.h"
#include "Regex_.h"

int main(int argc, const char* argv[])
{
  HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
  SetConsoleMode(hInput, ENABLE_VIRTUAL_TERMINAL_INPUT);
  HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleMode(hOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleTitle(L"Minecraft Mob Fall");
  struct Regex regex
  {
    std::regex("^[0-9]+$"),
    std::regex("^/([\\?]|[hH][eE][lL][pP])$"),
    std::regex("^/([h]|[hH][eE][aA][lL][tT][hH])$"),
    std::regex("^/([H]|[hH][eE][aA][rR][tT][sS])$")

  };
  bool hasHealthOrHeartValue = false;
  bool isHealthValue = true;
  int healthOrHeartValue = 0;
  int dropDistance = 0;
  if (argc > 1)
  {
    for (int index = 1; index < argc; index++)
    {
      if (std::regex_match(argv[index], regex.HELP))
      {
        const std::string HELPMESSAGE =
          "\n"
          "Minecraft Mob Fall - Calculate fall distance to bring a mob to half a heart\n"
          "                     in Minecraft.\n"
          "\n"
          "mcmobfall [/? | /help] | [/h | /health] [/H | /hearts] <INT VALUE>\n"
          "\n"
          "  /?, /help     This help screen.\n"
          "  /h, /health   <INT VALUE> provided is a health value. This is the default\n"
          "                and this switch is only necessary if needed\n"
          "                to override a provided /hearts switch after.\n"
          "  /H, /hearts   <INT VALUE> provided is a heart value. (health * 2).\n"
          "\n";
        std::cout << HELPMESSAGE;
        return EXIT_SUCCESS;
      }
      if (std::regex_match(argv[index], regex.UINT))
      {
        hasHealthOrHeartValue = true;
        healthOrHeartValue = atoi(argv[1]);
        continue;
      }
      if (std::regex_match(argv[index], regex.HEALTH))
      {
        isHealthValue = true;
        continue;
      }
      if (std::regex_match(argv[index], regex.HEARTS))
      {
        isHealthValue = false;
        continue;
      }
    }
  }
  if (!hasHealthOrHeartValue)
  {
    std::cerr << "A health or heart vaue was not provided.\n";
    return 1;
  }
  if (isHealthValue)
  {
    dropDistance = ((healthOrHeartValue - 1) + 3);
  }
  else
  {
    dropDistance = (((healthOrHeartValue * 2) - 1) + 3);
  }
  std::cout << dropDistance << '\n';
  WaitCheck();
  return EXIT_SUCCESS;
}