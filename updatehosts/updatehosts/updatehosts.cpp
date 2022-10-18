//////////////////////////////////////////////////
// 'updatehosts' - Update my hsost file         //
// © 2022 Ian Pride - New Pride Software        //
// / Services                                   //
//////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "FilesLib.h"
#include "StringsLib.h"
#include "ErrorsLib.h"
int main()
{
	const std::string NOTFOUND = " was not found.";
	const std::vector<std::string> errorVector =
	{
		Constants::RWMODE + NOTFOUND,
		Constants::PWSH + NOTFOUND,
		Constants::BLACKHOSTS + NOTFOUND,
		Constants::PATCH + NOTFOUND
	};
	Errors errors(errorVector);
	struct PathsLPWSTR
	{
		const LPWSTR RWMODE = Strings::ConvertStringToLPWSTR(Constants::RWMODE);
		const LPWSTR PWSH = Strings::ConvertStringToLPWSTR(Constants::PWSH);
		const LPWSTR BLACKHOSTS = Strings::ConvertStringToLPWSTR(Constants::BLACKHOSTS);
		const LPWSTR PATCH = Strings::ConvertStringToLPWSTR(Constants::PATCH);
	} pathsLPWSTR;
	const std::vector<LPWSTR> PATHSLPWSTR =
	{
		pathsLPWSTR.RWMODE,
		pathsLPWSTR.PWSH,
		pathsLPWSTR.BLACKHOSTS,
		pathsLPWSTR.PATCH
	};
	{
		int errorIndex = 0;
		for (const LPWSTR& PATH : PATHSLPWSTR)
		{
			errorIndex++;
			if (!Files::FileExists(PATH))
			{
				try
				{
					errors.setValue(errorIndex);
					throw errors;
				}
				catch (Errors err)
				{
					err.printMessage();
					std::exit(err.getValue());
				}
			}
		}
	}
	// TODO Add SHELLEXECUTEINFO and change to ShellExecuteEx(A)
	//HANDLE result =
	//	ShellExecuteA
	//	(
	//		GetConsoleWindow(),
	//		"runas",
	//		Constants::RWMODE.c_str(),
	//		"/F C:\\Windows\\System32\\drivers\\etc\\hosts /r",
	//		"C:\\Windows\\System32\\drivers\\etc",
	//		SW_SHOW
	//	);
	//const intptr_t result_convert_int = reinterpret_cast <intptr_t> (result);
	//if (result_convert_int <= 32)
	//{
	//	DWORD error = GetLastError();
	//	wchar_t err[256];
	//	memset(err, 0, 256);
	//	FormatMessage
	//	(
	//		FORMAT_MESSAGE_FROM_SYSTEM, NULL, error,
	//		MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
	//		err, 255, NULL
	//	);
	//	wprintf(L"%s", err);
	//	return (int)result_convert_int;
	//}
	//return (int)result_convert_int;
	return errors.getValue();
}