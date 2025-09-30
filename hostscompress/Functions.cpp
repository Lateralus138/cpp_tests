#include "pch.h"
#include "Functions.h"
#include <iostream> // Required for std::cout

const std::string GetWindowsDirectoryAsString(ProgramError& perror, int errorValue, std::string errorMessage)
{
  char path[MAX_PATH];
  unsigned int size = GetWindowsDirectoryA(path, sizeof(path));
  if (size == 0)
  {
    std::string message = GetLastErrorAsString();
    message.append(errorMessage);
    perror.addError(errorValue, message);
    return std::string("");
  }
  return std::string(path);
}

std::string ColorString(std::string string, int color, Options& options)
{
  std::string result = std::string("");
  if (options.isOutputColor)
  {
    result.append("\x1b[");
    result.append(std::to_string(color));
    result.push_back('m');
    result.append(string);
    result.append("\x1b[");
    result.push_back('m');
  }
  else
  {
    result = string;
  }
  return result;
}

void PrintMessage(std::string message, Options& options)
{
  if (!options.isQuiet) std::cout << message;
}

void PrintMessage(std::vector<std::string> strings, Options& options)
{
  if (!options.isQuiet)
  {
    std::string message;
    for (std::vector<std::string>::const_iterator iterator = strings.begin(); iterator != strings.end(); iterator++)
    {
      message.append(*iterator);
    }
    std::cout << message;
  }
}