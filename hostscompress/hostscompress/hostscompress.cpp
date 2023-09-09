// ╔══════════════════════════════════════════════════════════════════════════════════╗
// ║ Hosts Compress - Aggregate multiple domain names into single lines for local IP  ║
// ║ addresses of 0.0.0.0 and 127.0.0.1.                                              ║
// ║ © 2023 Ian Pride - New Pride Software / Services                                 ║
// ╚══════════════════════════════════════════════════════════════════════════════════╝
#include "pch.h"
Bench bench;
struct Options
{
  std::regex RGX_UINT = std::regex("[0-9]+");
  int urlsPerLine = 9;
  std::string inputFile = "";
  std::string outputFile = "";
  bool isOutputColor = true;
  bool isDiscard = false;
  bool isOutputFile = false;
  int urlStartingLineIndex = 0;
  int url000StartingLineIndex = 0;
  int url127StartingLineIndex = 0;
  bool hasUrl000StartingLineIndex = false;
  bool hasUrl127StartingLineIndex = false;
  bool hasFooterAndHeader = false;
  std::vector<std::string> urls000;
  std::vector<std::string> urls127;
  std::vector<std::string> headerContent;
  std::vector<std::string> footerContent;
};
struct Regex
{
  std::regex RGX_ISURL_000 = std::regex("^0.0.0.0[\\s]+(?!(0.0.0.0|127.0.0.1|local$|localhost$|localhost.localdomain$)).*");
  std::regex RGX_URLS000_REPLACE = std::regex("^(0.0.0.0)[\\s]+");
  std::regex RGX_ISURL_127 = std::regex("^127.0.0.1[\\s]+(?!(0.0.0.0|127.0.0.1|local$|localhost$|localhost.localdomain$)).*");
  std::regex RGX_URLS127_REPLACE = std::regex("^(127.0.0.1)[\\s]+");
};
unsigned int ParseArguments(ArgumentParser &argumentParser, Options& options, ProgramError &perror)
{
  const std::vector<std::string> MONOCHROMEOPTIONS{ "/m", "/monochrome" };
  const std::vector<std::string> HELPOPTIONS{ "/h", "/help" };
  const std::vector<std::string> INPUTFILEOPTIONS{ "/i", "/input" };
  const std::vector<std::string> OUTPUTFILEOPTIONS{ "/o", "/output" };
  const std::vector<std::string> COUNTOPTIONS{ "/c", "/count" };
  const std::vector<std::string> DISCARDOPTIONS{ "/d", "/discard" };
  if (argumentParser.optionsExist(MONOCHROMEOPTIONS))
  {
    options.isOutputColor = false;
  }
  if (argumentParser.optionsExist(DISCARDOPTIONS))
  {
    options.isDiscard = true;
  }
  if (argumentParser.optionsExist(HELPOPTIONS))
  {
    // TODO Finish help message
    std::cout << "HELP\n";
    return EXIT_SUCCESS;
  }
  if (argumentParser.optionsExist(INPUTFILEOPTIONS))
  {
    options.inputFile = argumentParser.getOptions(INPUTFILEOPTIONS);
    if (options.inputFile.empty())
    {
      perror.addError(1, "Option not provided for [/i, /input]");
      perror.setError(1);
      perror.print(options.isOutputColor);
      return perror.getError().value;
    }
  }
  if (argumentParser.optionsExist(OUTPUTFILEOPTIONS))
  {
    options.outputFile = argumentParser.getOptions(OUTPUTFILEOPTIONS);
    if (options.outputFile.empty())
    {
      perror.addError(2, "Option not provided for [/o, /output]");
      perror.setError(2);
      perror.print(options.isOutputColor);
      return perror.getError().value;
    }
    options.isOutputFile = true;
  }
  if (argumentParser.optionsExist(COUNTOPTIONS))
  {
    const std::string& option = argumentParser.getOptions(COUNTOPTIONS);
    if (!std::regex_match(option, options.RGX_UINT))
    {
      perror.addError(3, "Option provided for [/c, /count] is not a valid value.\nPlease provide a positive integer.");
      perror.setError(3);
      perror.print(options.isOutputColor);
      return perror.getError().value;
    }
    options.urlsPerLine = std::stoi(option);
  }
  return 0;
}
void ParseContent(std::vector<std::string>& inputFileData, Options& options, std::string variableName, std::vector<std::string>& urls, std::regex &match, std::regex& regexReplace)
{
  int parseDataIndex = 0;
  const bool isUrls000 = (variableName == "urls000");
  const bool isUrls127 = (variableName == "urls127");
  for (std::vector<std::string>::iterator iterator = inputFileData.begin(); iterator != inputFileData.end(); iterator++)
  {
    if (std::regex_match(*iterator, match))
    {
      if ((isUrls000) && (!options.hasUrl000StartingLineIndex))
      {
        options.hasUrl000StartingLineIndex = true;
        options.url000StartingLineIndex = parseDataIndex;
      }
      if ((isUrls127) && (!options.hasUrl127StartingLineIndex))
      {
        options.hasUrl127StartingLineIndex = true;
        options.url127StartingLineIndex = parseDataIndex;
      }
      *iterator = std::regex_replace(*iterator, regexReplace, "");
      urls.push_back(*iterator);
    }
    else
    {
      if (!options.hasFooterAndHeader)
      {
        const bool hasUrlsIndex = (options.hasUrl000StartingLineIndex || options.hasUrl127StartingLineIndex);
        if (!hasUrlsIndex) options.headerContent.push_back(*iterator);
        else options.footerContent.push_back(*iterator);
      }
    }
    parseDataIndex++;
  }
  options.hasFooterAndHeader = true;
}
void CompressUrls(Options& options, std::vector<std::string> &urls, std::vector < std::string> &output, std::string pre)
{
  for (int index = 0; index <= (int)(urls.size() - options.urlsPerLine); index += options.urlsPerLine)
  {
    std::stringstream ss;
    ss << pre << ' ';
    for (int index2 = 0; index2 < options.urlsPerLine; index2++)
    {
      const int nIndex = (index + index2);
      ss << urls[nIndex];
      if (index2 < (options.urlsPerLine - 1)) ss << ' ';
    }
    output.push_back(ss.str());
  }
  int leftOver = (int)(urls.size() - (output.size() * options.urlsPerLine));
  if (leftOver > 0)
  {
    std::stringstream ss;
    for (int index = (int)(output.size() * options.urlsPerLine); index < (int)urls.size(); index++)
    {
      ss << urls[index];
      if (index < ((int)urls.size() - 1))
      {
        ss << ' ';
      }
    }
    output.push_back(ss.str());
  }
}
std::vector<std::string> ReadHostsToVector(std::ifstream& inputFileStream, std::filesystem::path &inputPath, ProgramError &perror)
{
  std::vector<std::string> inputFileData = {};
  if (inputFileStream.is_open())
  {
    for (std::string line; std::getline(inputFileStream, line);)
    {
      inputFileData.push_back(line);
    }
    inputFileStream.close();
  }
  else
  {
    std::string message = "Could not open file: ";
    message.append(inputPath.string());
    message.append(" for reading");
    perror.addError(15, message);
    perror.setError(15);
  }
  return inputFileData;
}

int main(int argc, const char* argv[])
{
  ProgramError perror;
  Options options;
  Regex regex;
  CodePage cp;
  Handle handle{};
  ConsoleMode
    inputConsoleMode,
    outputConsoleMode;
  auto errorTest = [options](ProgramError& perror)
  {
    if (perror.getError().value > 0)
    {
      perror.print(options.isOutputColor);
      std::exit(perror.getError().value);
    }
  };
  // TODO Process arguments
  // TODO /h, /help       - help message
  // BEGIN argument parsing
  ArgumentParser argumentParser(argc, argv, 1);
  const unsigned int PARSEARGUMENTSRESULT = ParseArguments(argumentParser, options, perror);
  if (PARSEARGUMENTSRESULT > 0)
  {
    return PARSEARGUMENTSRESULT;
  }
  // END argument parsing

  const std::string WINDIR = GetWindowsDirectoryAsString(perror, 4, "Could not retrieve the Windows Directory");
  errorTest(perror);
  if (options.inputFile.empty())
  {
    options.inputFile.append(WINDIR);
    options.inputFile.append("\\System32\\drivers\\etc\\hosts");
  }
  std::filesystem::path inputPath(options.inputFile);
  std::filesystem::path outputPath(options.outputFile);
  std::error_code ec;
  const bool INPUTPATHEXISTS = std::filesystem::exists(inputPath, ec);
  if (ec.value() > 0)
  {
    perror.addError(5, ec.message());
    perror.setError(5);
    perror.print(options.isOutputColor);
    return perror.getError().value;
  }
  if (!INPUTPATHEXISTS)
  {
    std::string message(inputPath.string());
    message.append(" does not exist");
    perror.addError(6, message);
    perror.setError(6);
    perror.print(options.isOutputColor);
    return perror.getError().value;
  }
  // BEGIN CodePage Init
  cp.setInitCodePage(perror, 7, "Could not get the initial code page.");
  errorTest(perror);
  if (cp.getCurrentCodePage() != CP_UTF8)
  {
    cp.setCodePage(CP_UTF8, perror, 8, "Could not set the current code page.");
    errorTest(perror);
  }
  // END CodePage Init
  // BEGIN InputHandle Init
  handle.setInputHandle(perror, 9, "Could not retrieve console input handle.");
  errorTest(perror);
  // END InputHandle Init
  // BEGIN InitConsoleMode Init
  inputConsoleMode.setInitConsoleMode(handle.getInputHandle(), perror, 10, "");
  errorTest(perror);
  inputConsoleMode.setConsoleMode
  (
    handle.getInputHandle(),
    ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT,
    perror, 11, ""
  );
  errorTest(perror);
  // END InitConsoleMode Init
  // BEGIN InputHandle Init
 /* handle.setOutputHandle(perror, 12, "Could not retrieve console output handle.");
  errorTest(perror);
  outputConsoleMode.setInitConsoleMode(handle.getOutputHandle(), perror, 13, "");
  perror.setError(0);
  errorTest(perror);
  outputConsoleMode.setConsoleMode
  (
    handle.getOutputHandle(),
    ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING,
    perror, 14, ""
  );*/
  // END InputHandle Init
  SetConsoleTitle(L"Hosts Compress");
 
  // TODO Continue program
  //Bench b;
  //std::cout << "Press [Enter] to continue... > ";
  //std::cin.get();
  //std::cout << '\n';
  //std::cout << "\nBegin benchmark for reading the hosts file:\n";
  //b._Begin();
  std::ifstream inputFileStream(inputPath);
  std::vector<std::string> inputFileData =
    ReadHostsToVector(inputFileStream, inputPath, perror);
  errorTest(perror);
  //b._End();
  //b._PrintElapseMessage();
  //std::cout << "\nBegin benchmark for parsing the urls:\n";
  //b._Begin();
  std::vector<std::string> urls000;
  std::vector<std::string> urls127;

  ParseContent(inputFileData, options, "urls000", urls000, regex.RGX_ISURL_000, regex.RGX_URLS000_REPLACE);
  ParseContent(inputFileData, options, "urls127", urls127, regex.RGX_ISURL_127, regex.RGX_URLS127_REPLACE);
  //int urls000sz = (int)options.urls000.size();
  //int urls127sz = (int)options.urls000.size();

  //b._End();
  //b._PrintElapseMessage();
  std::vector<std::string> compressed;
  //std::cout << "\nBegin benchmark for compressing the urls:\n";
  //b._Begin();
  if ((int)urls000.size() > 0) CompressUrls(options, urls000, compressed, "0.0.0.0");
  if ((int)urls127.size() > 0) CompressUrls(options, urls127, compressed, "127.0.0.1");
  
  if ((int)options.headerContent.size())
  {
    for (std::vector<std::string>::const_iterator iterator = options.headerContent.begin(); iterator != options.headerContent.end(); iterator++)
    {
      std::cout << *iterator << '\n' << std::flush;
    }
  }
  for (std::vector<std::string>::const_iterator iterator = compressed.begin(); iterator != compressed.end(); iterator++)
  {
    std::cout << *iterator << '\n' << std::flush;
  }
  if ((int)options.footerContent.size())
  {
    for (std::vector<std::string>::const_iterator iterator = options.footerContent.begin(); iterator != options.footerContent.end(); iterator++)
    {
      std::cout << *iterator << '\n' << std::flush;
    }
  }
  //b._End();
  //b._PrintElapseMessage();

  // BEGIN CodePage Exit
  if (cp.getCurrentCodePage() != cp.getInitCodePage())
  {
    cp.setCodePage(cp.getInitCodePage(), perror, 15, "Could not set the code page to the initial value.");
    errorTest(perror);
  }
  // END CodePage Exit
  // BEGIN InputConsoleMode Exit
  if (inputConsoleMode.getCurrentConsoleMode() != inputConsoleMode.getInitConsoleMode())
  {
    inputConsoleMode.setConsoleMode(handle.getInputHandle(), inputConsoleMode.getInitConsoleMode(), perror, 16, "");
  }
  // END InputConsoleMode Exit
  //// BEGIN OutputConsoleMode Exit
  //if (outputConsoleMode.getCurrentConsoleMode() != outputConsoleMode.getInitConsoleMode())
  //{
  //  outputConsoleMode.setConsoleMode(handle.getInputHandle(), outputConsoleMode.getInitConsoleMode(), perror, 17, "");
  //}
  //// END OutputConsoleMode Exit
  return EXIT_SUCCESS;
}