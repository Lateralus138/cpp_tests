#pragma once
#ifndef STRINGSLIB_H
#define STRINGSLIB_H
#include <Windows.h>
#include <string>
namespace Strings
{
  extern LPWSTR ConvertStringToLPWSTR(const std::string& instr);
};
#endif // !STRINGSLIB_H
