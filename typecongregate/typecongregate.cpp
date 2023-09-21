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
  const std::vector<std::string> MONOCHROMEOPTIONS{ "/m", "/monochrome", "/M", "/MONOCHROME" };
  const std::vector<std::string> QUIETOPTIONS{ "/q", "/quiet", "/Q", "/QUIET" };
  const std::vector<std::string> RECUROPTIONS{ "/r", "/recurse", "/R", "/RECURSE" };
  const std::vector<std::string> HELPOPTIONS{ "/h", "/help", "/H", "/HELP" };
  const std::vector<std::string> EXTNOPTIONS{ "/x", "/extension", "/X", "/EXTENSION" };
  const std::vector<std::string> RPATHOPTIONS{ "/s", "/source", "/S", "/SOURCE" };
  const std::vector<std::string> DPATHOPTIONS{ "/d", "/destination", "/D", "/DESTINATION" };
  std::vector<std::string> ALLOPTIONS{};
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
template <typename T, typename ...T2>
void ConcatenateVectors(std::vector<T> &toVector, std::vector<T2> ...extraVectors)
{
  for (auto const item : { extraVectors... })
  {
    toVector.insert(toVector.end(), item.begin(), item.end());
  }
}
int IfConditionAddError(ProgramError& perror, Options& options, bool condition, int errorValue, std::string errorMessage)
{
  int status = 0;
  if (condition)
  {
    perror.addError(errorValue, errorMessage);
    perror.setError(errorValue);
    if (!options.isQuiet) perror.print(options.isColorOutput);
    status = perror.getError().value;
  }
  return status;
}
template <typename T>
int IsInVectorErrorCheck(std::vector<T> &vector, T value, ProgramError &perror, Options& options, int errorValue, std::string errorMessage)
{
  //if (IsInVector(vector, value))
  //{
  //  perror.addError(errorValue, errorMessage);
  //  perror.setError(errorValue);
  //  if (!options.isQuiet) perror.print(options.isColorOutput);
  //}
  //return perror.getError().value;
  return IfConditionAddError(perror, options, IsInVector(vector, value), errorValue, errorMessage);
}
unsigned int ParseArguments(ArgumentParser & args, Options &options, ProgramError &perror)
{
  //const std::vector<std::string> MONOCHROMEOPTIONS{ "/m", "/monochrome", "/M", "/MONOCHROME" };
  //const std::vector<std::string> QUIETOPTIONS{ "/q", "/quiet", "/Q", "/QUIET" };
  //const std::vector<std::string> RECUROPTIONS{ "/r", "/recurse", "/R", "/RECURSE" };
  //const std::vector<std::string> HELPOPTIONS{ "/h", "/help", "/H", "/HELP" };
  //const std::vector<std::string> EXTNOPTIONS{ "/x", "/extension", "/X", "/EXTENSION" };
  //const std::vector<std::string> RPATHOPTIONS{ "/s", "/source", "/S", "/SOURCE" };
  //const std::vector<std::string> DPATHOPTIONS{ "/d", "/destination", "/D", "/DESTINATION" };
  //std::vector<std::string> ALLOPTIONS{};
  ConcatenateVectors(options.ALLOPTIONS, options.MONOCHROMEOPTIONS, options.QUIETOPTIONS, options.RECUROPTIONS, options.HELPOPTIONS, options.EXTNOPTIONS, options.RPATHOPTIONS, options.DPATHOPTIONS);
  if (args.optionsExist(options.MONOCHROMEOPTIONS))
  {
    options.isColorOutput = false;
  }
  if (args.optionsExist(options.QUIETOPTIONS))
  {
    options.isQuiet = true;
  }
  if (args.optionsExist(options.RECUROPTIONS))
  {
    options.isRecursive = true;
  }
  if (args.optionsExist(options.HELPOPTIONS))
  {
    options.isHelp = true;
    // TODO finish help section
    std::cout << "HELP\n";
    return 0;
  }
  if (args.optionsExist(options.EXTNOPTIONS))
  {
    options.extnTypeStr = args.getOptions(options.EXTNOPTIONS);
    //if (options.extnTypeStr.empty())
    //{
    //  perror.addError(1, "Argument not provided for [/x, /extension]");
    //  perror.setError(1);
    //  if (!options.isQuiet) perror.print(options.isColorOutput);
    //  return perror.getError().value;
    //}
    if (IfConditionAddError(perror, options, options.extnTypeStr.empty(), 1, "Argument not provided for [/x, /extension]") > 0)
      return perror.getError().value;
    options.extnTypes = SplitStringToVector(options.extnTypeStr, ",");
    for (std::vector<std::string>::const_iterator iterator = options.ALLOPTIONS.begin(); iterator != options.ALLOPTIONS.end(); iterator++)
    {
      if (IsInVectorErrorCheck(options.extnTypes, *iterator, perror, options, 2, "Argument provided for [/x, /extension] is invalid") > 0) return perror.getError().value;
      //const int result =
      //  IsInVectorErrorCheck(options.extnTypes, *iterator, perror, options, 2, "Argument provided for [/x, /extension] is invalid");
      //if (result > 0) return perror.getError().value;
      //if (IsInVector(options.extnTypes, *iterator))
      //{
      //  perror.addError(2, "Argument provided for [/x, /extension] is invalid");
      //  perror.setError(2);
      //  if (!options.isQuiet) perror.print(options.isColorOutput);
      //  return perror.getError().value;
      //}
    }
  }
  if (args.optionsExist(options.RPATHOPTIONS))
  {
    options.rootPathStr = args.getOptions(options.RPATHOPTIONS);
    //if (options.rootPathStr.empty())
    //{
    //  perror.addError(3, "Argument not provided for [/s, /source]");
    //  perror.setError(3);
    //  if (!options.isQuiet) perror.print(options.isColorOutput);
    //  return perror.getError().value;
    //}
    if (IfConditionAddError(perror, options, options.rootPathStr.empty(), 4, "Argument not provided for [/s, /source] is invalid") > 0)
      return perror.getError().value;
    if (IsInVectorErrorCheck(options.ALLOPTIONS, options.rootPathStr, perror, options, 5, "Argument provided for [/s, /source] is invalid") > 0) return perror.getError().value;
    //const int result =
    //  IsInVectorErrorCheck(options.ALLOPTIONS, options.rootPathStr, perror, options, 4, "Argument provided for [/s, /source] is invalid");
    //if (result > 0) return perror.getError().value;
    //if (IsInVector(ALLOPTIONS, options.rootPathStr))
    //{
    //  perror.addError(4, "Argument provided for [/s, /source] is invalid");
    //  perror.setError(4);
    //  if (!options.isQuiet) perror.print(options.isColorOutput);
    //  return perror.getError().value;
    //}
  }
  if (args.optionsExist(options.DPATHOPTIONS))
  {
    options.destPathStr = args.getOptions(options.DPATHOPTIONS);
    //if (options.destPathStr.empty())
    //{
    //  perror.addError(5, "Argument not provided for [/d, /destination]");
    //  perror.setError(5);
    //  if (!options.isQuiet) perror.print(options.isColorOutput);
    //  return perror.getError().value;
    //}
    if (IfConditionAddError(perror, options, options.destPathStr.empty(), 6, "Argument not provided for [/d, /destination]") > 0)
      return perror.getError().value;
    if (IsInVectorErrorCheck(options.ALLOPTIONS, options.destPathStr, perror, options, 7, "Argument provided for [/d, /destination] is invalid") > 0) return perror.getError().value;
    //const int result =
    //  IsInVectorErrorCheck(options.ALLOPTIONS, options.destPathStr, perror, options, 6, "Argument provided for [/d, /destination] is invalid");
    //if (result > 0) return perror.getError().value;
    //if (IsInVector(ALLOPTIONS, options.destPathStr))
    //{
    //  perror.addError(6, "Argument provided for [/d, /destination] is invalid");
    //  perror.setError(6);
    //  if (!options.isQuiet) perror.print(options.isColorOutput);
    //  return perror.getError().value;
    //}
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