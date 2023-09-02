// ╔══════════════════════════════════════════════════════════════════════════════════╗
// ║ Hosts Compress - Aggregate multiple domain names into single lines for local IP  ║
// ║ addresses of 0.0.0.0 and 127.0.0.1.                                              ║
// ║ © 2023 Ian Pride - New Pride Software / Services                                 ║
// ╚══════════════════════════════════════════════════════════════════════════════════╝
#include "pch.h"
std::string GetLastErrorAsString()
{
  //Get the error message, if any.
  DWORD errorMessageID = ::GetLastError();
  if (errorMessageID == 0)
    return std::string(); //No error message has been recorded

  LPSTR messageBuffer = nullptr;
  size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

  std::string message(messageBuffer, size);

  //Free the buffer.
  LocalFree(messageBuffer);

  return message;
}
int main(int argc, const char* argv[])
{
  ProgramError perror;
  CodePage cp;
  auto errorTest = [](ProgramError &perror)
  {
    if (perror.getError().value > 0)
    {
      perror.print(true);
      std::exit(perror.getError().value);
    }
  };
  const unsigned int INITCODEPAGE = cp.getInitCodePage(perror, 1, "Could not get the initial code page.");
  errorTest(perror);
  //if (perror.getError().value > 0)
  //{
  //  perror.print(true);
  //  return perror.getError().value;
  //}
  if (INITCODEPAGE != CP_UTF8)
  {
    cp.setCodePage(CP_UTF8, perror, 2, "Could not set the current code page.");
    errorTest(perror);
    //if (perror.getError().value > 0)
    //{
    //  perror.print(true);
    //  return perror.getError().value;
    //}
  }
  //std::cout << INITCODEPAGE << ':' << CP_UTF8 << '\n';
  //std::cout << cp.getCurrentCodePage() << '\n';
  //cp.setCodePage(437, perror, 2, "");
  //std::cout << cp.getCurrentCodePage() << '\n';
  //std::cout << cp.setCodePage(CP_UTF8, perror, 2, "") << '\n';
  ////perror.print(false);
  ////perror.print(true);
  //perror.addError(1, "Fake Error");
  //perror.setError(1);
  //const int currentError = perror.getError().value;
  //if (currentError > 0)
  //{
  //  perror.print(true);
  //  return currentError;
  //}
  //try
  //{
  //  const UINT WINAPI INITCODEPOUTPUTPAGE = GetConsoleOutputCP();

  //}
  //const UINT WINAPI INITCODEPAGE = GetConsoleCP();
  //std::error_code ec;
  //try
  //{
  //  std::thread().detach();
  //  //throw std::system_error::system_error(ec, );
  //}
  //catch (std::system_error& error)
  //{
  //  std::cerr
  //    << "Value:\t\t" << error.code().value()
  //    << "\nMessage:\t" << error.code().message()
  //    << "\nWhat\t\t" << error.what()
  //    << '\n';
  //}
  ////GetNetworkResource();
  //std::cout << GetLastErrorAsString() << '\n';
  HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
  SetConsoleMode(hInput, ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT);
  HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleMode(hOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleTitle(L"This is a test");
  //std::cin.get();
  // TODO Process arguments
  // TODO Continue program
  return EXIT_SUCCESS;
}