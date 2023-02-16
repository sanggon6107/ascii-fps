#include "ContextTitleScreen.h"

ContextTitleScreen::ContextTitleScreen(int w, int h) : IContext(w, h){}

ContextState ContextTitleScreen::Run()
{
	wchar_t* screen = new wchar_t[w_ * h_];
	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
	DWORD bytes_written = 0;
	wstring a = L"Hello!";

	while (1)
	{
		for (int i = 0; i < h_; i++)
		{
			for (int j = 0; j < w_; j++)
			{
				screen[i * w_ + j] = ' ';
			}
		}

		screen[w_ * h_ - 1] = '\0';
		WriteConsoleOutputCharacter(console, screen, w_ * h_, { 0, 0 }, &bytes_written);
	}

	return ContextState::kContextTitleScreen;
}

void ContextTitleScreen::SetText() {}