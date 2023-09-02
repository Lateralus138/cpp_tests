#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
class CodePage
{
private:
  unsigned int initCodePage;
  unsigned int initOutputCodePage;
  unsigned int currentCodePage;
  unsigned int currentOutputCodePage;
public:
  unsigned int getInitCodePage(ProgramError& perror, int errorValue, std::string errorMessage);
  unsigned int getCodePage(ProgramError &perror, int errorValue, std::string errorMessage);
  unsigned int getCurrentCodePage();
  void setCodePage(unsigned int codePage, ProgramError& perror, int errorValue, std::string errorMessage);
  unsigned int getInitOutputCodePage(ProgramError& perror, int errorValue, std::string errorMessage);
  unsigned int getOutputCodePage(ProgramError& perror, int errorValue, std::string errorMessage);
  unsigned int getCurrentOutputCodePage();
  void setOutputCodePage(unsigned int outputCodePage, ProgramError& perror, int errorValue, std::string errorMessage);
  CodePage(const unsigned int& initCodePage, const unsigned int& initOutputCodePage, const unsigned int& currentCodePage, const unsigned int& currentOutputCodePage) : initCodePage(initCodePage), initOutputCodePage(initOutputCodePage), currentCodePage(currentCodePage), currentOutputCodePage(currentOutputCodePage) {};
  bool operator==(const CodePage& other) const = default;
  CodePage()
  {
    initCodePage = 0;
    initOutputCodePage = 0;
    currentCodePage = initCodePage;
    currentOutputCodePage = initOutputCodePage;
  };
};
#endif // !CONSOLE_H


