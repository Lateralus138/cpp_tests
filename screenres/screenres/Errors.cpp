#include "Errors.h"
const LPWSTR GetLastErrorMessage()
{
  const DWORD LERROR = GetLastError();
  const DWORD DWFLAGS =
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS |
    FORMAT_MESSAGE_ARGUMENT_ARRAY |
    FORMAT_MESSAGE_ALLOCATE_BUFFER;
  LPCTSTR errorMessage = { 0 };
  FormatMessage(DWFLAGS, NULL, LERROR, 0, (LPWSTR)&errorMessage, 0, NULL);
  return const_cast<LPWSTR>(errorMessage);
}