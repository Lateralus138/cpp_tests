#include "ScreenResolution.h"
#include <Windows.h>
#include "Errors.h"
#include <iostream>
void GetDesktopResolution(Screen &screen)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	const bool hasRect = GetWindowRect(hDesktop, &desktop);
	if (!hasRect)
	{
		std::wcerr << GetLastErrorMessage();
		std::exit((int)GetLastError());
	}
	screen.width = desktop.right;
	screen.height = desktop.bottom;
	const DPI_AWARENESS_CONTEXT DPI_CONTEXT =
		SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
	if (DPI_CONTEXT == NULL)
	{
		std::wcerr << "Could not retrieve the DPI context.\n";
		std::exit(0x3E80);
	}
	screen.dpi = GetDpiForSystem();
	const double DPI_MULTIPLIER = (screen.dpi / static_cast<double>(96));
	screen.dpiWidth =
		static_cast<unsigned int>(static_cast<double>(screen.width) * DPI_MULTIPLIER);
	screen.dpiHeight =
		static_cast<unsigned int>(static_cast<double>(screen.height) * DPI_MULTIPLIER);
}