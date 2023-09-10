// ╔══════════════════════════════════════════════════════════════════════════════════╗
// ║ Hosts Compress - Aggregate multiple domain names into single lines for local IP  ║
// ║ addresses of 0.0.0.0 and 127.0.0.1.                                              ║
// ║ © 2023 Ian Pride - New Pride Software / Services                                 ║
// ╚══════════════════════════════════════════════════════════════════════════════════╝
#include "pch.h"
// TODO Create program/progess verbosity based on options.isQuiet
const std::regex RGX_ISURL_000("^0.0.0.0[\\s]+(?!(0.0.0.0|127.0.0.1|local$|localhost$|localhost.localdomain$)).*");
const std::regex RGX_URLS000_REPLACE("^(0.0.0.0)[\\s]+");
const std::regex RGX_ISURL_127("^127.0.0.1[\\s]+(?!(0.0.0.0|127.0.0.1|local$|localhost$|localhost.localdomain$)).*");
const std::regex RGX_URLS127_REPLACE("^(127.0.0.1)[\\s]+");
const std::regex RGX_UINT("[0-9]+");
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
  bool isQuiet = false;
  std::vector<std::string> urls000;
  std::vector<std::string> urls127;
  std::vector<std::string> headerContent;
  std::vector<std::string> footerContent;
};
unsigned int ParseArguments(ArgumentParser &argumentParser, Options& options, ProgramError &perror)
{
  const std::vector<std::string> MONOCHROMEOPTIONS{ "/m", "/monochrome" };
  const std::vector<std::string> HELPOPTIONS{ "/h", "/help" };
  const std::vector<std::string> INPUTFILEOPTIONS{ "/i", "/input" };
  const std::vector<std::string> OUTPUTFILEOPTIONS{ "/o", "/output" };
  const std::vector<std::string> COUNTOPTIONS{ "/c", "/count" };
  const std::vector<std::string> DISCARDOPTIONS{ "/d", "/discard" };
  const std::vector<std::string> QUIETOPTIONS{ "/q", "/quiet" };
  if (argumentParser.optionsExist(MONOCHROMEOPTIONS))
  {
    options.isOutputColor = false;
  }
  if (argumentParser.optionsExist(DISCARDOPTIONS))
  {
    options.isDiscard = true;
  }
  if (argumentParser.optionsExist(QUIETOPTIONS))
  {
    options.isQuiet = true;
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
    const int UPL = std::stoi(option);
    if ((UPL < 2) || (UPL > 9))
    {
      perror.addError(4, "Option provided for [/c, /count] exceeds url limit per line.\nPlease provide a positive integer from 2 - 9.");
      perror.setError(4);
      perror.print(options.isOutputColor);
      return perror.getError().value;
    }
    options.urlsPerLine = UPL;
  }
  return 0;
}
void ParseContent(std::vector<std::string>& inputFileData, Options& options, std::string variableName, std::vector<std::string>& urls, std::regex match, std::regex regexReplace)
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
std::string GetHostsOutput(std::vector<std::string> &compressed, Options &options)
{
  std::string output = std::string("");
  if ((!options.isDiscard) && ((int)options.headerContent.size()))
  {
    for (std::vector<std::string>::const_iterator iterator = options.headerContent.begin(); iterator != options.headerContent.end(); iterator++)
    {
      if (!output.empty()) output.push_back('\n');
      output.append(*iterator);
    }
  }
  for (std::vector<std::string>::const_iterator iterator = compressed.begin(); iterator != compressed.end(); iterator++)
  {
    if (!output.empty()) output.push_back('\n');
    output.append(*iterator);
  }
  if ((!options.isDiscard) && ((int)options.footerContent.size()))
  {
    for (std::vector<std::string>::const_iterator iterator = options.footerContent.begin(); iterator != options.footerContent.end(); iterator++)
    {
      if (!output.empty()) output.push_back('\n');
      output.append(*iterator);
    }
  }
  return output;
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
std::vector<std::string> ReadHostsToVector(std::filesystem::path &inputPath, ProgramError &perror)
{
  std::ifstream inputFileStream(inputPath);
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
    perror.addError(13, message);
    perror.setError(13);
  }
  return inputFileData;
}
void CreateHostsFile(const std::string &OUTPUTDATA, Options& options, ProgramError &perror)
{
  std::ofstream ofs(options.outputFile, std::fstream::trunc);
  if (ofs.is_open())
  {
    ofs << OUTPUTDATA;
    ofs.close();
  }
  else
  {
    std::string message = "Could not open file: ";
    message.append(options.outputFile);
    message.append(" for writing");
    perror.addError(14, message);
    perror.setError(14);
  }
}
int main(int argc, const char* argv[])
{
  ProgramError perror;
  Options options;
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
  ArgumentParser argumentParser(argc, argv, 1);
  const unsigned int PARSEARGUMENTSRESULT = ParseArguments(argumentParser, options, perror);
  if (PARSEARGUMENTSRESULT > 0)
  {
    return PARSEARGUMENTSRESULT;
  }

  const std::string WINDIR = GetWindowsDirectoryAsString(perror, 5, "Could not retrieve the Windows Directory");
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
    perror.addError(6, ec.message());
    perror.setError(6);
    perror.print(options.isOutputColor);
    return perror.getError().value;
  }
  if (!INPUTPATHEXISTS)
  {
    std::string message(inputPath.string());
    message.append(" does not exist");
    perror.addError(7, message);
    perror.setError(7);
    perror.print(options.isOutputColor);
    return perror.getError().value;
  }
  cp.setInitCodePage(perror, 8, "Could not get the initial code page.");
  errorTest(perror);
  if (cp.getCurrentCodePage() != CP_UTF8)
  {
    cp.setCodePage(CP_UTF8, perror, 9, "Could not set the current code page.");
    errorTest(perror);
  }
  handle.setInputHandle(perror, 10, "Could not retrieve console input handle.");
  errorTest(perror);
  inputConsoleMode.setInitConsoleMode(handle.getInputHandle(), perror, 11, "");
  errorTest(perror);
  inputConsoleMode.setConsoleMode
  (
    handle.getInputHandle(),
    ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT,
    perror, 12, ""
  );
  errorTest(perror);
  SetConsoleTitle(L"Hosts Compress");
  std::vector<std::string> inputFileData =
    ReadHostsToVector(inputPath, perror);
  errorTest(perror);
  std::vector<std::string> urls000;
  std::vector<std::string> urls127;
  ParseContent(inputFileData, options, "urls000", urls000, RGX_ISURL_000, RGX_URLS000_REPLACE);
  ParseContent(inputFileData, options, "urls127", urls127, RGX_ISURL_127, RGX_URLS127_REPLACE);
  std::vector<std::string> compressed;
  if ((int)urls000.size() > 0) CompressUrls(options, urls000, compressed, "0.0.0.0");
  if ((int)urls127.size() > 0) CompressUrls(options, urls127, compressed, "127.0.0.1");
  const std::string OUTPUTDATA = GetHostsOutput(compressed, options);
  if (!options.isOutputFile)
  {
    std::cout << GetHostsOutput(compressed, options);
  }
  else
  {
    CreateHostsFile(OUTPUTDATA, options, perror);
    errorTest(perror);
  }
  if (cp.getCurrentCodePage() != cp.getInitCodePage())
  {
    cp.setCodePage(cp.getInitCodePage(), perror, 15, "Could not set the code page to the initial value.");
    errorTest(perror);
  }
  if (inputConsoleMode.getCurrentConsoleMode() != inputConsoleMode.getInitConsoleMode())
  {
    inputConsoleMode.setConsoleMode(handle.getInputHandle(), inputConsoleMode.getInitConsoleMode(), perror, 16, "");
  }
  return EXIT_SUCCESS;
}