﻿// ╔═══════════════════════════════════════════════════════════════════════════════╗
// ║ Password Generator (passgen) - Generate strong random passwords with various  ║
// ║ options.                                                                      ║
// ║ © 2024 Ian Pride - New Pride Software / Services                              ║
// ╚═══════════════════════════════════════════════════════════════════════════════╝
#include "stdafx.h"
void CheckOptionsAndSetOption(ArgumentParser& args, Options& options, std::vector<std::string>& option_vector, int set)
{
  if (args.optionsExist(option_vector))
    options.passwordIndex += set;
}
//void SetOptionIsFullTrue(Options& options, int value)
//{
//  options.passwordIsFull = true;
//  options.passwordIndex = value;
//}
void SetOptionIsFull(Options& options, bool is, int value)
{
  options.passwordIsFull = is;
  options.passwordIndex = value;
}
void SetIsSpecialFull(Options& options, bool is)
{
  options.passwordIsSpecialFull = is;
  if (is) options.passwordIndex += 32;
  else options.passwordIndex -= 32;
}
auto IsASwitch = [](std::string& option)
{
  return
  (
    Globals::ValueInVector(Globals::LENGOPTS, option) ||
    Globals::ValueInVector(Globals::UPPCOPTS, option) ||
    Globals::ValueInVector(Globals::LOWCOPTS, option) ||
    Globals::ValueInVector(Globals::DIGIOPTS, option) ||
    Globals::ValueInVector(Globals::SPCCOPTS, option) ||
    Globals::ValueInVector(Globals::SPCEOPTS, option) ||
    Globals::ValueInVector(Globals::SPCFOPTS, option)
  );
};
bool ArgOptionsExist(ArgumentParser& args)
{
  return
    args.optionsExist(Globals::UPPCOPTS) || args.optionsExist(Globals::LOWCOPTS) ||
    args.optionsExist(Globals::DIGIOPTS) || args.optionsExist(Globals::SPCCOPTS) ||
    args.optionsExist(Globals::SPCEOPTS) || args.optionsExist(Globals::SPCFOPTS);
}
int ParseArguments(ArgumentParser& args, Options& options)
{
  if (ArgOptionsExist(args))
  {
    options.passwordIsFull = false;
    options.passwordIndex = 0;
  }
  if (args.optionsExist(Globals::HELPOPTS))
  {
    std::cout << Globals::HELPMESSAGE;
    return -1;
  }
  if (args.optionsExist(Globals::LENGOPTS))
  {
    std::string option = args.getOptions(Globals::LENGOPTS);
    if (option.empty() || IsASwitch(option)) return 1;
    try
    {
      options.passwordLength = std::stoi(option);
    }
    catch (std::invalid_argument const& error)
    {
      std::cerr << error.what() << '\n';
      return 2;
    }
  }
  CheckOptionsAndSetOption(args, options, Globals::UPPCOPTS, 1);
  CheckOptionsAndSetOption(args, options, Globals::LOWCOPTS, 2);
  CheckOptionsAndSetOption(args, options, Globals::DIGIOPTS, 4);
  if (args.optionsExist(Globals::SPCCOPTS))
  {
    options.passwordIsSpecialCompatible = true;
    options.passwordIndex += 8;
    if (options.passwordIsSpecialExtended)
    {
      options.passwordIsSpecialExtended = false;
      options.passwordIndex -= 16;
    }
    if (options.passwordIsSpecialFull)
    {
      SetIsSpecialFull(options, false);
    }
  }
  if (args.optionsExist(Globals::SPCEOPTS))
  {
    options.passwordIsSpecialExtended = true;
    options.passwordIndex += 16;
    if (options.passwordIsSpecialCompatible)
    {
      options.passwordIsSpecialCompatible = false;
      options.passwordIndex -= 8;
    }
    if (options.passwordIsSpecialFull)
    {
      SetIsSpecialFull(options, false);
    }
  }
  if (args.optionsExist(Globals::SPCFOPTS))
  {
    SetIsSpecialFull(options, true);
    if (options.passwordIsSpecialCompatible)
    {
      options.passwordIsSpecialCompatible = false;
      options.passwordIndex -= 8;
    }
    if (options.passwordIsSpecialExtended)
    {
      options.passwordIsSpecialExtended = false;
      options.passwordIndex -= 16;
    }
  }
  if (args.optionsExist(Globals::FULLOPTS))
  {
    SetOptionIsFull(options, true, 39);
    return EXIT_SUCCESS;
  }
  if (args.optionsExist(Globals::EXTDOPTS))
  {
    SetOptionIsFull(options, true, 23);
    return EXIT_SUCCESS;
  }
  if (args.optionsExist(Globals::COMPOPTS))
  {
    SetOptionIsFull(options, true, 15);
    return EXIT_SUCCESS;
  }
  return EXIT_SUCCESS;
}
int main(int argc, const char* argv[])
{
  SetConsoleTitle(L"Password Generator");
  std::srand(static_cast<unsigned int>(GetTickCount64()));
  Options options = { 12, true, false, false, false, 15 };
  Errors errors =
  { {
      {1, "No value provided for [/l, /length]."},
      {2, "Passed value is not an integer."}
  } };
  ArgumentParser args(argc, argv, 1);
  const int PARSED = ParseArguments(args, options);
  if (PARSED == -1) return EXIT_SUCCESS;
  if (PARSED > 0) return Globals::PrintError(PARSED, errors);
  errno_t errt = {};
  for (int index = 0; index < options.passwordLength; index++)
  {
    unsigned int number = {};
    errt = rand_s(&number);
    const int randCharIndex = number % (Globals::CHARSMAP[options.passwordIndex].length()) + 0;
    //const int randCharIndex = rand_s(&number) % (Globals::CHARSMAP[options.passwordIndex].length()) + 0;
    Globals::PASSWORD.push_back(Globals::CHARSMAP[options.passwordIndex][randCharIndex]);
  }
  std::cout << Globals::PASSWORD << '\n';
  return EXIT_SUCCESS;
}
