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
}