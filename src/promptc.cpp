// -----------------------------------------------
// 'promptc' - Command line prompt to give a
// command an opputunity for the command to be
// cancelled.
// Ian Pride @ New Pride Software/Services
// Copyright © 2022
// Mon 12 Sep 2022 05:11:59 PM UTC
// -----------------------------------------------
#include <iostream>
#include <unistd.h>
#include "ParsePipe.h"
#include "ParseArgs.h"
#include <vector>
#include <regex>
#include "Safety.h"
int main(int argc, const char * argv[])
{
  using namespace ParsePipe;
  using namespace ParseArgs;
  const std::regex 
    YES("^([yY]|[yY][eE][sS])$"),
    NO("^([nN]|[nN][oO])$");
  const std::string pipeString = PipeToString(0, ARG_MAX, " ", 0);
  const std::string argsString = ArgsToString(argc, argv, 1, argc, " ", 1);
  const std::string finalString(argsString + pipeString);
  std::string userInput;
  try
  {
    FILE* ttyin = freopen("/dev/tty", "rw", stdin);
    if (ttyin == nullptr)
    {
      std::string message = "Could not open '/dev/tty'.\n";
      message.append(strerror(errno));
      throw std::runtime_error(message);
    }
  }
  catch (std::runtime_error & run_error)
  {
    std::cerr << run_error.what() << '\n';
    return int(errno);
  }
  while ((!std::regex_match(userInput, YES)) && (!std::regex_match(userInput, NO)))
  {
    std::cin.clear();
    std::cout << "\rConfirm command execution? ([Y]es, [N]o): ";
    getline(std::cin, userInput);
  }
  if (std::regex_match(userInput, YES))
  {
    Safety::SystemCheck(); // using system() as safely as possible ;)
    errno = system(finalString.c_str()) / 256;
  }
  return int(errno);
}