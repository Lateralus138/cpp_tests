#include "pch.h"
#include "Console.h"
unsigned int CodePage::getInitCodePage(ProgramError& perror, int errorValue, std::string errorMessage)
{
  if (initCodePage == 0)
  {
    initCodePage = getCodePage(perror, errorValue, errorMessage);
  }
  return initOutputCodePage;
}
unsigned int CodePage::getCodePage(ProgramError& perror, int errorValue, std::string errorMessage)
{
  const unsigned int CP = GetConsoleCP();
  perror.addError(errorValue, errorMessage);
  if (CP == 0) perror.setError(errorValue);
  currentCodePage = CP;
  return currentCodePage;
}
unsigned int CodePage::getCurrentCodePage()
{
  return currentCodePage;
}
void CodePage::setCodePage(unsigned int codePage, ProgramError& perror, int errorValue, std::string errorMessage)
{
  bool SET = SetConsoleCP(codePage);
  perror.addError(errorValue, errorMessage);
  if (!SET) perror.setError(errorValue);
  else currentCodePage = codePage;
}
unsigned int CodePage::getInitOutputCodePage(ProgramError& perror, int errorValue, std::string errorMessage)
{
  if (initOutputCodePage == 0)
  {
    initOutputCodePage = getOutputCodePage(perror, errorValue, errorMessage);
  }
  return initOutputCodePage;
}
unsigned int CodePage::getOutputCodePage(ProgramError& perror, int errorValue, std::string errorMessage)
{
  const unsigned int CP = GetConsoleOutputCP();
  perror.addError(errorValue, errorMessage);
  if (CP == 0) perror.setError(errorValue);
  currentOutputCodePage = CP;
  return currentOutputCodePage;
}
unsigned int CodePage::getCurrentOutputCodePage()
{
  return CodePage::currentOutputCodePage;
}
void CodePage::setOutputCodePage(unsigned int outputCodePage, ProgramError& perror, int errorValue, std::string errorMessage)
{
  bool SET = SetConsoleOutputCP(outputCodePage);
  perror.addError(errorValue, errorMessage);
  if (!SET) perror.setError(errorValue);
  else currentCodePage = outputCodePage;
}
