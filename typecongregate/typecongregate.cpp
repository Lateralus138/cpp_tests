// ╔═════════════════════════════════════════════════════════════════════════════╗
// ║ Type Congregate - Congregate files based on their extension to a different  ║
// ║ directory.                                                                  ║
// ║ Project started: 20:47, September 18, 2023 Universal Time Coordinated       ║
// ║ © 2023 Ian Pride - New Pride Software / Services                            ║
// ╚═════════════════════════════════════════════════════════════════════════════╝
#include "stdafx.h"
struct Options
{
  bool isColorOutput      = true;
  bool isQuiet            = false;
  bool isHelp             = false;
  bool isRecursive        = false;
  std::vector<std::string> extnTypes;
  std::string extnTypeStr = "";
  std::string rootPathStr = ".\\";
  std::string destPathStr = "";
};
template <typename T>
bool IsInVector(std::vector<T> &vector, T item)
{
  typename std::vector<T>::iterator iterator;
  iterator = std::find(vector.begin(), vector.end(), item);
  return (iterator != vector.end());
}
std::vector<std::string> SplitStringToVector(std::string string, std::string delimeter)
{
  std::vector<std::string> split;
  if (!string.empty())
  {
    size_t start = 0;
    do
    {
      size_t index = string.find(delimeter, start);
      if (index == std::string::npos) break;
      size_t length = (index - start);
      split.push_back(string.substr(start, length));
      start += (length + delimeter.size());
    } while (true);
    split.push_back(string.substr(start));
  }
  return split;
}
std::string ColorString(std::string string, int color, Options& options)
{
  std::string result = std::string("");
  if (options.isColorOutput)
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
unsigned int ParseArguments(ArgumentParser & args, Options &options, ProgramError &perror)
{
  const std::vector<std::string> MONOCHROMEOPTIONS{ "/m", "/monochrome", "/M", "/MONOCHROME" };
  const std::vector<std::string> QUIETOPTIONS{ "/q", "/quiet", "/Q", "/QUIET" };
  const std::vector<std::string> RECUROPTIONS{ "/r", "/recurse", "/R", "/RECURSE" };
  const std::vector<std::string> HELPOPTIONS{ "/h", "/help", "/H", "/HELP" };
  const std::vector<std::string> EXTNOPTIONS{ "/x", "/extension", "/X", "/EXTENSION" };
  const std::vector<std::string> RPATHOPTIONS{ "/s", "/source", "/S", "/SOURCE" };
  const std::vector<std::string> DPATHOPTIONS{ "/d", "/destination", "/D", "/DESTINATION" };
  std::vector<std::string> ALLOPTIONS{};
  ALLOPTIONS.insert(ALLOPTIONS.end(), MONOCHROMEOPTIONS.begin(), MONOCHROMEOPTIONS.end());
  ALLOPTIONS.insert(ALLOPTIONS.end(), QUIETOPTIONS.begin(), QUIETOPTIONS.end());
  ALLOPTIONS.insert(ALLOPTIONS.end(), RECUROPTIONS.begin(), RECUROPTIONS.end());
  ALLOPTIONS.insert(ALLOPTIONS.end(), HELPOPTIONS.begin(), HELPOPTIONS.end());
  ALLOPTIONS.insert(ALLOPTIONS.end(), EXTNOPTIONS.begin(), EXTNOPTIONS.end());
  ALLOPTIONS.insert(ALLOPTIONS.end(), RPATHOPTIONS.begin(), RPATHOPTIONS.end());
  ALLOPTIONS.insert(ALLOPTIONS.end(), DPATHOPTIONS.begin(), DPATHOPTIONS.end());
  if (args.optionsExist(MONOCHROMEOPTIONS))
  {
    options.isColorOutput = false;
  }
  if (args.optionsExist(QUIETOPTIONS))
  {
    options.isQuiet = true;
  }
  if (args.optionsExist(RECUROPTIONS))
  {
    options.isRecursive = true;
  }
  if (args.optionsExist(HELPOPTIONS))
  {
    options.isHelp = true;
    // TODO finish help section
    std::cout << "HELP\n";
    return 0;
  }
  if (args.optionsExist(EXTNOPTIONS))
  {
    options.extnTypeStr = args.getOptions(EXTNOPTIONS);
    if (options.extnTypeStr.empty())
    {
      perror.addError(1, "Argument not provided for [/x, /extension]");
      perror.setError(1);
      if (!options.isQuiet) perror.print(options.isColorOutput);
      return perror.getError().value;
    }
    options.extnTypes = SplitStringToVector(options.extnTypeStr, ",");
    for (std::vector<std::string>::const_iterator iterator = ALLOPTIONS.begin(); iterator != ALLOPTIONS.end(); iterator++)
    {
      if (IsInVector(options.extnTypes, *iterator))
      {
        perror.addError(2, "Argument provided for [/x, /extension] is invalid");
        perror.setError(2);
        if (!options.isQuiet) perror.print(options.isColorOutput);
        return perror.getError().value;
      }
    }
  }
  if (args.optionsExist(RPATHOPTIONS))
  {
    options.rootPathStr = args.getOptions(RPATHOPTIONS);
    if (options.rootPathStr.empty())
    {
      perror.addError(3, "Argument not provided for [/s, /source]");
      perror.setError(3);
      if (!options.isQuiet) perror.print(options.isColorOutput);
      return perror.getError().value;
    }
    for (std::vector<std::string>::const_iterator iterator = ALLOPTIONS.begin(); iterator != ALLOPTIONS.end(); iterator++)
    {
      if (*iterator == options.rootPathStr)
      {
        perror.addError(4, "Argument provided for [/s, /source] is invalid");
        perror.setError(4);
        if (!options.isQuiet) perror.print(options.isColorOutput);
        return perror.getError().value;
      }
    }
  }
  if (args.optionsExist(DPATHOPTIONS))
  {
    options.destPathStr = args.getOptions(DPATHOPTIONS);
    if (options.destPathStr.empty())
    {
      perror.addError(5, "Argument not provided for [/d, /destination]");
      perror.setError(5);
      if (!options.isQuiet) perror.print(options.isColorOutput);
      return perror.getError().value;
    }
    for (std::vector<std::string>::const_iterator iterator = ALLOPTIONS.begin(); iterator != ALLOPTIONS.end(); iterator++)
    {
      if (*iterator == options.destPathStr)
      {
        perror.addError(6, "Argument provided for [/d, /destination] is invalid");
        perror.setError(6);
        if (!options.isQuiet) perror.print(options.isColorOutput);
        return perror.getError().value;
      }
    }
  }
  return 0;
}
int main(int argc, const char* argv[])
{
  Options options;
  ArgumentParser args(argc, argv, 1);
  ProgramError perror;
  const unsigned int PARSEARGUMENTSRESULT = ParseArguments(args, options, perror);
  if (PARSEARGUMENTSRESULT > 0) return perror.getError().value;
  if (options.isHelp) return EXIT_SUCCESS;
  Handle handle{};
  CodePage codePage;
  ConsoleMode
    inputConsoleMode,
    outputConsoleMode;
  const int CONSOLEINPUTMODE  = (ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT);
  const int CONSOLEOUTPUTMODE = (ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT);
  auto ErrorTest = [options](ProgramError& perror)
  {
    if (perror.getError().value > 0)
    {
      if (!options.isQuiet) perror.print(options.isColorOutput);
      std::exit(perror.getError().value);
    }
  };

  handle.setInputHandle(perror, 7, "Could not get the current input handle");
  ErrorTest(perror);
  handle.setOutputHandle(perror, 8, "Could not get the current output handle");   
  ErrorTest(perror);

  codePage.setInitCodePage(perror, 9, "Could not get the console's initial code page");
  ErrorTest(perror);
  if (codePage.getCurrentCodePage() != CP_UTF8)
    codePage.setCodePage(CP_UTF8, perror, 10, "Could not set the console's code page");
  ErrorTest(perror);

  inputConsoleMode.setInitConsoleMode(handle.getInputHandle(), perror, 11, "");
  //ErrorTest(perror);
  const DWORD ICMERROR = GetLastError();
  if (ICMERROR == ERROR_SUCCESS)
  {
    if (inputConsoleMode.getCurrentConsoleMode() != CONSOLEINPUTMODE)
    {
      inputConsoleMode.setConsoleMode(handle.getInputHandle(), CONSOLEINPUTMODE, perror, 12, "");
      ErrorTest(perror);
    }
  }

  outputConsoleMode.setInitConsoleMode(handle.getOutputHandle(), perror, 13, "");
  //ErrorTest(perror);
  const DWORD OCMERROR = GetLastError();
  if (OCMERROR == ERROR_SUCCESS)
  {
    if (outputConsoleMode.getCurrentConsoleMode() != CONSOLEOUTPUTMODE)
    {
      outputConsoleMode.setConsoleMode(handle.getOutputHandle(), CONSOLEOUTPUTMODE, perror, 14, "");
      ErrorTest(perror);
    }
  }

  // TODO Main program

  if (codePage.getCurrentCodePage() != codePage.getInitCodePage())
  {
    codePage.setCodePage(codePage.getInitCodePage(), perror, 15, "Could not set the console's code page");
    ErrorTest(perror);
  }
  if (inputConsoleMode.getCurrentConsoleMode() != inputConsoleMode.getInitConsoleMode())
  {
    inputConsoleMode.setConsoleMode(handle.getInputHandle(), inputConsoleMode.getInitConsoleMode(), perror, 16, "");
    ErrorTest(perror);
  }
  if (outputConsoleMode.getCurrentConsoleMode() != outputConsoleMode.getInitConsoleMode())
  {
    outputConsoleMode.setConsoleMode(handle.getOutputHandle(), outputConsoleMode.getInitConsoleMode(), perror, 17, "");
    ErrorTest(perror);
  }
  return EXIT_SUCCESS;
}