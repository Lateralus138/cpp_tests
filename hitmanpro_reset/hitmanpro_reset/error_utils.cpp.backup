#include "stdafx.h"
#include "error_utils.h"

std::wstring FormatLastError() {
    DWORD error_code = GetLastError();
    if (error_code == 0) {
        return L"";
    }

    LPWSTR buffer = nullptr;
    DWORD size = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error_code,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&buffer,
        0,
        NULL
    );

    if (size == 0) {
        return L"Failed to format error message.";
    }

    std::wstring message(buffer, size);
    LocalFree(buffer);

    return message;
}
