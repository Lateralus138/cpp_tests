#include "FilesLib.h"
namespace Constants
{
	extern const std::string RWMODE			= "C:\\Users\\flux\\Bin\\rwmode.exe";
	extern const std::string PWSH				= "C:\\Program Files\\PowerShell\\7\\pwsh.exe";
	extern const std::string BLACKHOSTS = "C:\\Users\\flux\\Bin\\blackhosts.exe";
	extern const std::string PATCH			= "C:\\Users\\flux\\Bin\\patch_easeus_activation.exe";
};
namespace Files
{
	bool FileExists(LPCWSTR pszFilename)
	{
		DWORD dwAttrib = GetFileAttributes(pszFilename);
		return (!(dwAttrib & FILE_ATTRIBUTE_DEVICE) && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
};
