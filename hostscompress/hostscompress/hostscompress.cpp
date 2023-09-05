// ╔══════════════════════════════════════════════════════════════════════════════════╗
// ║ Hosts Compress - Aggregate multiple domain names into single lines for local IP  ║
// ║ addresses of 0.0.0.0 and 127.0.0.1.                                              ║
// ║ © 2023 Ian Pride - New Pride Software / Services                                 ║
// ╚══════════════════════════════════════════════════════════════════════════════════╝
#include "pch.h"
int main(int argc, const char* argv[])
{
  // TODO Process arguments
  // TODO /h, /help       - help message
  // TODO /m, /monochrome - output has no color
  // TODO /i, /input      - input file
  // TODO /o, /ouput      - output file
  // TODO /c, /count      - urls per line
  // TODO /d, /discard    - discard everything but values
  // BEGIN argument parsing
  ProgramError perror;
  const std::regex UINT("[0-9]+");
  unsigned int urlsPerLine = 9;
  std::string inputFile = "";
  std::string outputFile = "";
  bool isOutputColor = true;
  bool isDiscard = false;
  bool isOutputFile = false;
  CodePage cp;
  Handle handle{};
  ConsoleMode
    inputConsoleMode,
    outputConsoleMode;
  auto errorTest = [isOutputColor](ProgramError& perror)
  {
    if (perror.getError().value > 0)
    {
      perror.print(isOutputColor);
      std::exit(perror.getError().value);
    }
  };
  ArgumentParser argumentParser(argc, argv, 1);
  const std::vector<std::string> MONOCHROMEOPTIONS  { "/m", "/monochrome" };
  const std::vector<std::string> HELPOPTIONS        { "/h", "/help"       };
  const std::vector<std::string> INPUTFILEOPTIONS   { "/i", "/input"      };
  const std::vector<std::string> OUTPUTFILEOPTIONS  { "/o", "/output"     };
  const std::vector<std::string> COUNTOPTIONS       { "/c", "/count"      };
  const std::vector<std::string> DISCARDOPTIONS     { "/d", "/discard"    };
  if (argumentParser.optionsExist(MONOCHROMEOPTIONS))
  {
    isOutputColor = false;
  }
  if (argumentParser.optionsExist(DISCARDOPTIONS))
  {
    isDiscard = true;
  }
  if (argumentParser.optionsExist(HELPOPTIONS))
  {
    // TODO Finish help message
    std::cout << "HELP\n";
    return EXIT_SUCCESS;
  }
  if (argumentParser.optionsExist(INPUTFILEOPTIONS))
  {
    inputFile = argumentParser.getOptions(INPUTFILEOPTIONS);
    if (inputFile.empty())
    {
      perror.addError(1, "Option not provided for [/i, /input]");
      perror.setError(1);
      perror.print(isOutputColor);
      return perror.getError().value;
    }
  }
  if (argumentParser.optionsExist(OUTPUTFILEOPTIONS))
  {
    outputFile = argumentParser.getOptions(OUTPUTFILEOPTIONS);
    if (outputFile.empty())
    {
      perror.addError(2, "Option not provided for [/o, /output]");
      perror.setError(2);
      perror.print(isOutputColor);
      return perror.getError().value;
    }
    isOutputFile = true;
  }
  if (argumentParser.optionsExist(COUNTOPTIONS))
  {
    const std::string& option = argumentParser.getOptions(COUNTOPTIONS);
    if (!std::regex_match(option, UINT))
    {
      perror.addError(3, "Option provided for [/c, /count] is not a valid value.\nPlease provide a positive integer.");
      perror.setError(3);
      perror.print(isOutputColor);
      return perror.getError().value;
    }
    urlsPerLine = std::stoi(option);
  }
  // END argument parsing

  const std::string WINDIR = GetWindowsDirectoryAsString(perror, 4, "Could not retrieve the Windows Directory");
  errorTest(perror);
  if (inputFile.empty())
  {
    inputFile.append(WINDIR);
    inputFile.append("\\System32\\drivers\\etc\\hosts");
  }
  std::filesystem::path inputPath(inputFile);
  std::filesystem::path outputPath(outputFile);
  std::error_code ec;
  const bool INPUTPATHEXISTS = std::filesystem::exists(inputPath, ec);
  if (ec.value() > 0)
  {
    perror.addError(5, ec.message());
    perror.setError(5);
    perror.print(isOutputColor);
    return perror.getError().value;
  }
  if (!INPUTPATHEXISTS)
  {
    std::string message(inputPath.string());
    message.append(" does not exist");
    perror.addError(6, message);
    perror.setError(6);
    perror.print(isOutputColor);
    return perror.getError().value;
  }
  // BEGIN CodePage Init
  cp.setInitCodePage(perror, 1, "Could not get the initial code page.");
  errorTest(perror);
  if (cp.getCurrentCodePage() != CP_UTF8)
  {
    cp.setCodePage(CP_UTF8, perror, 2, "Could not set the current code page.");
    errorTest(perror);
  }
  // END CodePage Init
  // BEGIN InputHandle Init
  handle.setInputHandle(perror, 3, "Could not retrieve console input handle.");
  errorTest(perror);
  // END InputHandle Init
  // BEGIN InitConsoleMode Init
  inputConsoleMode.setInitConsoleMode(handle.getInputHandle(), perror, 4, "");
  errorTest(perror);
  inputConsoleMode.setConsoleMode
  (
    handle.getInputHandle(),
    ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT,
    perror, 5, ""
  );
  errorTest(perror);
  // END InitConsoleMode Init
  // BEGIN InputHandle Init
  handle.setOutputHandle(perror, 5, "Could not retrieve console output handle.");
  errorTest(perror);
  outputConsoleMode.setInitConsoleMode(handle.getOutputHandle(), perror, 4, "");
  errorTest(perror);
  outputConsoleMode.setConsoleMode
  (
    handle.getOutputHandle(),
    ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING,
    perror, 5, ""
  );
  // END InputHandle Init
  SetConsoleTitle(L"Hosts Compress");
 
  // TODO Continue program

  std::cin.get();
  // BEGIN CodePage Exit
  if (cp.getCurrentCodePage() != cp.getInitCodePage())
  {
    cp.setCodePage(cp.getInitCodePage(), perror, 3, "Could not set the code page to the initial value.");
    errorTest(perror);
  }
  // END CodePage Exit
  // BEGIN InputConsoleMode Exit
  if (inputConsoleMode.getCurrentConsoleMode() != inputConsoleMode.getInitConsoleMode())
  {
    inputConsoleMode.setConsoleMode(handle.getInputHandle(), inputConsoleMode.getInitConsoleMode(), perror, 1, "");
  }
  // END InputConsoleMode Exit
  // BEGIN OutputConsoleMode Exit
  if (outputConsoleMode.getCurrentConsoleMode() != outputConsoleMode.getInitConsoleMode())
  {
    outputConsoleMode.setConsoleMode(handle.getInputHandle(), outputConsoleMode.getInitConsoleMode(), perror, 1, "");
  }
  // END OutputConsoleMode Exit
  return EXIT_SUCCESS;
}