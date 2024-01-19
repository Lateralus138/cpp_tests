#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
struct Options
{
  int passwordLength;
  bool passwordIsFull;
  //bool passwordHasUppercase;
  //bool passwordHasLowercase;
  //bool passwordHasDigits;
  //bool passwordHasSpecial;
  bool passwordIsSpecialCompatible;
  bool passwordIsSpecialExtended;
  bool passwordIsSpecialFull;
  int passwordIndex;
};
struct Errors
{
  std::map<int, std::string> messages;
};
namespace Globals
{
  bool ValueInVector(std::vector<std::string>const& vector, std::string value);
  int PrintError(int value, Errors& error);
  extern const std::string CHARSUPPERCASE;
  extern const std::string CHARSLOWERCASE;
  extern const std::string CHARSDIGITS;
  extern const std::string CHARSSPECIALCOM; // compatible; default
  extern const std::string CHARSSPECIALEXT; // extended
  extern const std::string CHARSSPECIALFUL; // full
  extern std::map<int, std::string> CHARSMAP;
  extern std::string PASSWORD;
  extern std::vector<std::string> HELPOPTS;
  extern std::vector<std::string> LENGOPTS;
  extern std::vector<std::string> COMPOPTS;
  extern std::vector<std::string> EXTDOPTS;
  extern std::vector<std::string> FULLOPTS;
  extern std::vector<std::string> UPPCOPTS;
  extern std::vector<std::string> LOWCOPTS;
  extern std::vector<std::string> DIGIOPTS;
  extern std::vector<std::string> SPCCOPTS;
  extern std::vector<std::string> SPCEOPTS;
  extern std::vector<std::string> SPCFOPTS;
  extern const std::string HELPMESSAGE;
}
#endif // ! GLOBALS_H