#include "pch.h"
#include "ProgramError.h"
void ProgramError::addError(int value, std::string message)
{
  errors[value] = message;
}
void ProgramError::setError(int errorNumber)
{
  currentError = { errorNumber, errors[errorNumber] };
}
ErrorStruct ProgramError::getError()
{
  return currentError;
}
void ProgramError::print(bool color)
{
  std::string errorMessage = ((color) ? "\x1b[" : "");
  if (color)
  {
    errorMessage.append((currentError.value > 0) ? "91" : "92");
    errorMessage.push_back('m');
  }
  errorMessage.append(currentError.message);
  errorMessage.push_back(':');
  if (color)
  {
    errorMessage.append("\x1b[m");
  }
  errorMessage.append(" [");
  if (color)
  {
    errorMessage.append("\x1b[");
    errorMessage.append((currentError.value > 0) ? "91" : "92");
    errorMessage.push_back('m');
  }
  errorMessage.append(std::to_string(currentError.value));
  if (color)
  {
    errorMessage.append("\x1b[m");
  }
  errorMessage.push_back(']');
  if (currentError.value > 0) std::cerr << errorMessage << '\n';
  else std::cout << errorMessage << '\n';
}
//ProgramError perror;