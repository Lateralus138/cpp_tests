#include "pch.h"
#include "ArgumentParser.h"
#include "Options.h"      // For Options struct
#include "ProgramError.h" // For ProgramError class
#include "Functions.h"    // For ColorString
#include <iostream>       // For std::cout
#include <regex>          // For std::regex_match

// Global regex for unsigned int, used in ParseArguments
extern const std::regex RGX_UINT; // Declared in hostscompress.cpp, now extern

ArgumentParser::ArgumentParser(int& argc, const char** argv, int start)
{
  this->tokens = std::vector<std::string>(argv + start, argv + argc);
}
bool ArgumentParser::optionExists(const std::string& option) const
{
  return (std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end());
}
bool ArgumentParser::optionsExist(const std::vector<std::string>& options) const
{
  for (std::vector<std::string>::const_iterator iter = options.begin(); iter < options.end(); iter++)
  {
    if (this->optionExists(*iter)) return true;
  }
  return false;
}
const std::string& ArgumentParser::getOption(const std::string& option) const
{
  std::vector<std::string>::const_iterator iterator;
  iterator = std::find(this->tokens.begin(), this->tokens.end(), option);
  if ((iterator != this->tokens.end()) && (++iterator != this->tokens.end()))
  {
    return *iterator;
  }
  static const std::string empty("");
  return empty;
}
const std::string& ArgumentParser::getOptions(const std::vector<std::string>& options) const
{
  for (std::vector<std::string>::const_iterator iter = options.begin(); iter < options.end(); iter++)
  {
    const std::string &arg = this->getOption(*iter);
    if (!arg.empty()) return arg;
  }
  static const std::string empty("");
  return empty;
}

// Definition of ParseArguments function
unsigned int ParseArguments(ArgumentParser &argumentParser, Options& options, ProgramError &perror)
{
  const std::vector<std::string> MONOCHROMEOPTIONS{ "/m", "/monochrome" };
  const std::vector<std::string> HELPOPTIONS{ "/h", "/help", "/?"};
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
    std::cout <<
      "\n  Hosts Compress - Consolidate multiple blocked URLs to single IP lines in a"
      "\n  systems's hosts file with various options."
      "\n"
      "\n  @" << ColorString("USAGE", 95, options) <<
      "\n    hostscompress [" << ColorString("SWITCHES", 92, options) <<
      "] [[" << ColorString("OPTIONS", 94, options) <<
      "] <" << ColorString("PARAMS", 93, options) <<
      ">]"
      "\n"
      "\n  @" << ColorString("SWITCHES", 92, options) << ":"
      "\n    /h, /help, /?   This help message."
      "\n    /m, /monochrome Verbose output is void of color."
      "\n    /q, /quiet      No verbosity; silences all errors and output with the errors"
      "\n                    and output with the exception of the resulting compression"
      "\n                    results if no output file is provided."
      "\n    /d, discard     Discard everything except the compressed lines from the"
      "\n                    resulting output. This is only recommended if the HOSTS file"
      "\n                    is only used for blocking URLs."
      "\n"
      "\n  @" << ColorString("OPTIONS", 94, options) << ":"
      "\n    /i, /input      Path to an optional " <<
      ColorString("INPUT FILE", 93, options) <<
      " to parse. Defaults to the"
      "\n                    default system hosts file location."
      "\n    /o, /output     Path to an optional " <<
      ColorString("OUTPUT FILE", 93, options) <<
      ". The default is to output"
      "\n                    to the console."
      "\n    /c, count       " <<
      ColorString("NUMBER", 93, options) <<
      " of URLs to compress to a single line. The default is"
      "\n                    9 (2-9)."
      "\n";
    options.isHelp = true;
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