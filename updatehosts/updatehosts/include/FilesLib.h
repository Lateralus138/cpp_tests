#pragma once
#ifndef FILESLIB_H
#define FILESLIB_H
#include <Windows.h>
#include <string>
namespace Constants
{
	extern const std::string RWMODE;
	extern const std::string PWSH;
	extern const std::string BLACKHOSTS;
	extern const std::string PATCH;
};
namespace Files
{
	extern bool FileExists(LPCWSTR pszFilename);
};
#endif // !FILESLIB_H