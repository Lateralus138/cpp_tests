#include "stdafx.h"
#include "env_var.h"

std::wstring GetEnvironmentVariableStringW(const std::wstring& name) {
    DWORD size = GetEnvironmentVariableW(name.c_str(), nullptr, 0);
    if (size == 0) {
        if (GetLastError() == ERROR_ENVVAR_NOT_FOUND) {
            return {};
        }
        return {};
    }

    std::wstring value(size, L'\0');
    GetEnvironmentVariableW(name.c_str(), &value[0], size);
    value.pop_back();
    return value;
}
