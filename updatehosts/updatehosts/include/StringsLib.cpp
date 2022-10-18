#include "StringsLib.h"
namespace Strings
{
  LPWSTR ConvertStringToLPWSTR(const std::string& instr)
  {
    int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), (int)instr.size(), NULL, 0);
    if (bufferlen == 0)
    {
      return 0;
    }
    LPWSTR widestr = new WCHAR[static_cast <unsigned __int64> (bufferlen) + 1];
    ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), (int)instr.size(), widestr, bufferlen);
    widestr[bufferlen] = 0;
    return widestr;
  }
};