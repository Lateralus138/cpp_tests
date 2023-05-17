#pragma once
#ifndef USERNAMEREGEX_H
#define USERNAMEREGEX_H
#include <regex>
namespace UserNameRegex
{
  const std::regex HELP   = std::regex("^/([\?]|[hH]|[hH][eE][lL][pP])$");
  const std::regex UPPER  = std::regex("^/([uU]|[uU][pP][pP][eE][rR])$");
  const std::regex LOWER  = std::regex("^/([lL]|[lL][oO][wW][eE][rR])$");
  const std::regex TITLE  = std::regex("^/([tT]|[tT][iI][tT][lL][eE])$");
};
#endif // !USERNAMEREGEX_H
