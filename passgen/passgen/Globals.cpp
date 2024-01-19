#include "stdafx.h"
#include "Globals.h"
extern struct Options options;
extern struct Errors errors;
namespace Globals
{
  bool ValueInVector(std::vector<std::string> const& vector, std::string value)
  {
    return (std::find(vector.begin(), vector.end(), value) != vector.end());
  }
  int PrintError(int value, Errors& error)
  {
    std::cerr << error.messages[value] << '\n';
    return value;
  }
  extern const std::string CHARSUPPERCASE  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  extern const std::string CHARSLOWERCASE  = "abcdefghijklmnopqrstuvwxyz";
  extern const std::string CHARSDIGITS     = "0123456789";
  extern const std::string CHARSSPECIALCOM = "#!~()_";                             // compatible; default
  extern const std::string CHARSSPECIALEXT = "#!~()_:;<>{}[]";                     // extended
  extern const std::string CHARSSPECIALFUL = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"; // full
  std::map<int, std::string> CHARSMAP
  {
    {1, CHARSUPPERCASE}, {2, CHARSLOWERCASE},
    {3, CHARSUPPERCASE + CHARSLOWERCASE}, {4, CHARSDIGITS},
    {5, CHARSUPPERCASE + CHARSDIGITS}, {6, CHARSLOWERCASE + CHARSDIGITS},
    {7, CHARSUPPERCASE + CHARSLOWERCASE + CHARSDIGITS}, {8, CHARSSPECIALCOM},
    {9, CHARSUPPERCASE + CHARSSPECIALCOM}, {10, CHARSLOWERCASE + CHARSSPECIALCOM},
    {11, CHARSUPPERCASE + CHARSLOWERCASE + CHARSSPECIALCOM}, {12, CHARSDIGITS + CHARSSPECIALCOM},
    {13, CHARSUPPERCASE + CHARSDIGITS + CHARSSPECIALCOM}, {14, CHARSLOWERCASE + CHARSDIGITS + CHARSSPECIALCOM},
    {15, CHARSUPPERCASE + CHARSLOWERCASE + CHARSDIGITS + CHARSSPECIALCOM}, {16, CHARSSPECIALEXT},
    {17, CHARSUPPERCASE + CHARSSPECIALEXT}, {18, CHARSLOWERCASE + CHARSSPECIALEXT},
    {19, CHARSUPPERCASE + CHARSLOWERCASE + CHARSSPECIALEXT}, {20, CHARSDIGITS + CHARSSPECIALEXT},
    {21, CHARSUPPERCASE + CHARSDIGITS + CHARSSPECIALEXT}, {22, CHARSLOWERCASE + CHARSDIGITS + CHARSSPECIALEXT},
    {23, CHARSUPPERCASE + CHARSLOWERCASE + CHARSDIGITS + CHARSSPECIALEXT}, {32, CHARSSPECIALFUL},
    {33, CHARSUPPERCASE + CHARSSPECIALFUL}, {34, CHARSLOWERCASE + CHARSSPECIALFUL},
    {35, CHARSUPPERCASE + CHARSLOWERCASE + CHARSSPECIALFUL}, {36, CHARSDIGITS + CHARSSPECIALFUL},
    {37, CHARSUPPERCASE + CHARSDIGITS + CHARSSPECIALFUL}, {38, CHARSLOWERCASE + CHARSDIGITS + CHARSSPECIALFUL},
    {39, CHARSUPPERCASE + CHARSLOWERCASE + CHARSDIGITS + CHARSSPECIALFUL}
  };
  std::string PASSWORD = "";
  std::vector<std::string> HELPOPTS = { "/?", "/h", "/help", "/H", "/HELP" };
  std::vector<std::string> LENGOPTS = { "/l", "/length", "/L", "/LENGTH" };
  std::vector<std::string> COMPOPTS = { "/c", "/compatible", "/C", "/COMPATIBLE" };
  std::vector<std::string> EXTDOPTS = { "/e", "/extended", "/E", "/EXTENDED" };
  std::vector<std::string> FULLOPTS = { "/f", "/full", "/F", "/FULL" };
  std::vector<std::string> UPPCOPTS = { "/uc", "/uppercase", "/UC", "/UPPERCASE" };
  std::vector<std::string> LOWCOPTS = { "/lc", "/lowercase", "/LC", "/LOWERCASE" };
  std::vector<std::string> DIGIOPTS = { "/d", "/digits", "/D", "/DIGITS" };
  std::vector<std::string> SPCCOPTS = { "/sc", "/specialcompatible", "/SC", "/SPECIALCOMPATIBLE" };
  std::vector<std::string> SPCEOPTS = { "/se", "/specialextended", "/SE", "/SPECIALEXTENDED" };
  std::vector<std::string> SPCFOPTS = { "/sf", "/specialfull", "/SF", "/SPECIALFULL" };
  extern const std::string HELPMESSAGE =
    "\n  Password Generator - Generate strong random passwords with various options."
    "\n  The default password style consists of uppercase, lowercase, digits, and"
    "\n  a few basic compatible special characters that work in most cases. This"
    "\n  program provides additional switches to allow an extended or full list of"
    "\n  special characters. You can also specify the use of only one type of"
    "\n  character and/or digit and mix and match."
    "\n\n  passgen [SWITCHES] [OPTIONS <ARGUMENT>]"
    "\n\n  @OPTIONS"
    "\n    /l, /length             The length of the password. Defaults to 12."
    "\n\n  @SWITCHES"
    "\n    /?, /h, /help           This help message."
    "\n    /c, /compatible         Full password with compatible special characters."
    "\n                            This is the default style and this switch is only"
    "\n                            necessary to override any previous options."
    "\n                            Compatible characters: " + Globals::CHARSSPECIALCOM +
    "\n    /e, /extended           Full password with extended characters."
    "\n                            If this switch is provided it overrides everthing"
    "\n                            except the /c, /compatible switch."
    "\n                            Extended characters: " + Globals::CHARSSPECIALEXT +
    "\n    /f, /full               Full password with all characters."
    "\n                            If this switch is provided it overrides everthing"
    "\n                            except the /c, /compatible and /e, /extended"
    "\n                            switches."
    "\n                            Full characters: " + Globals::CHARSSPECIALFUL +
    "\n    /uc, /uppercase         Use uppercase characters. This switch can be used"
    "\n                            with other singular types."
    "\n    /lc, /lowercase         Use lowercase characters. This switch can be used"
    "\n                            with other singular types."
    "\n    /d, /digits             Use digits/integers. This switch can be used"
    "\n                            with other singular types."
    "\n    /sc, /specialcompatible Use special compatible characters. This switch can"
    "\n                            be used with other singular types. Only one type of"
    "\n                            special character set can be used and the last"
    "\n                            /s* switch provided overrides other /s* switches."
    "\n    /se, /specialextended   Use special extended characters. This switch can"
    "\n                            be used with other singular types."
    "\n    /sf, /specialfull       Use special full characters. This switch can be"
    "\n                            used with other singular types."
    "\n\n";
}