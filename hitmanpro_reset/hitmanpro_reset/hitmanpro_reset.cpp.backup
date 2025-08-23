#include "stdafx.h"
int main() {
	const int mode_result = _setmode(_fileno(stdout), _O_U16TEXT);
	std::map<std::string, std::wstring> LOGO = {
		{"UTF16", L"╭─────────────┬─────────────────┬────────────────╮\n"
							L"│             │ HitmanPro Reset │                │\n"
							L"├─────────────┴─────────────────┴────────────────┤\n"
							L"│    Reset HitmanPro license by deleting the     │\n"
							L"│ pertinent files:                               │\n"
							L"│ HitmanPro.key                                  │\n"
							L"│ HitmanPro.lic                                  │\n"
							L"╰────────────────────────────────────────────────╯\n"},
		{"ASCII",	L"+-------------+-----------------+----------------+\n"
							L"|             | HitmanPro Reset |                |\n"
							L"+-------------+-----------------+----------------+\n"
							L"|    Reset HitmanPro license by deleting the     |\n"
							L"| pertinent files:                               |\n"
							L"| HitmanPro.key                                  |\n"
							L"| HitmanPro.lic                                  |\n"
							L"+------------------------------------------------+\n"}
	};
	const std::wstring PROGRAMDATA = GetEnvironmentVariableStringW(L"PROGRAMDATA");
	if (PROGRAMDATA.empty()) {
		std::wcerr << L"PROGRAMDATA path was not found.\n";
		return 1;
	}
	const std::wstring HITMANPRO_PATH = PROGRAMDATA + L"\\HitmanPro";
	if (!DirectoryExists(HITMANPRO_PATH)) {
		std::wcout << L"HitmanPro directory not found, no reset required.";
		return 0;
	}
	std::map<std::wstring, std::wstring> hitmanpro_files = {
		{L"HitmanPro.key", HITMANPRO_PATH + L"\\HitmanPro.key"},
		{L"HitmanPro.lic", HITMANPRO_PATH + L"\\HitmanPro.lic"}
	};
	if (mode_result == -1) {
		std::wcout << LOGO["ASCII"];
	} else {
		std::wcout << LOGO["UTF16"];
	}
	for (const auto& [filename, filepath] : hitmanpro_files) {
		if (FileExists(filepath)) {
			if (DeleteFileW(filepath.c_str())) {
				std::wcout << L"Successfully deleted: " << filename << L"\n";
			} else {
				std::wcerr << L"Failed to delete: " << filename << L".\nError code: " << FormatLastError() << L"\n";
			}
		} else {
			std::wcout << L"File not found, skipping: " << filename << L"\n";
		}
	}
	return 0;
}