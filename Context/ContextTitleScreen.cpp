#include "ContextTitleScreen.h"

ContextTitleScreen::ContextTitleScreen(int w, int h) : IContext(w, h)
{
	for (int list_idx = 0; list_idx < (int)TitleScreenText::kTitleScreenTextSize; list_idx++)
	{
		text_list_.emplace_back(0);
	}

	text_list_[(int)TitleScreenText::kTitle].push_back(L"██████████████████████████████████");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█─█─█─██─█───█────█────█────██───█");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█─█─█──█─██─██─██─█─██─█─██──█─███");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█─█─█─█──██─██─████─██─█─██──█───█");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█─█─█─██─██─██─██─█─██─█─██──█─███");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█───█─██─█───█────█────█────██───█");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"██████████████████████████████████");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"████████████████████████████████████████████████████");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█─███─█────█────█───████────█─█─█─██─█─██─█───█────█");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█──█──█─██─███──█─██████─██─█─█─█──█─█──█─█─███─██─█");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█─█─█─█────██──██───████────█─█─█─█──█─█──█───█────█");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█─███─█─██─█──███─██████─█─██─█─█─██─█─██─█─███─█─██");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"█─███─█─██─█────█───████─█─██───█─██─█─██─█───█─█─██");
	text_list_[(int)TitleScreenText::kTitle].push_back(L"████████████████████████████████████████████████████");
}

ContextState ContextTitleScreen::Run()
{
	wchar_t* screen = new wchar_t[screen_width_ * screen_height_];
	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
	DWORD bytes_written = 0;
	wstring a = L"Hello!";

	while (1)
	{
		for (int i = 0; i < screen_height_; i++) { for (int j = 0; j < screen_width_; j++) { screen[i * screen_width_ + j] = ' '; } }

		PutText(screen, 1, 1, TitleScreenText::kTitle);

		screen[screen_width_ * screen_height_ - 1] = '\0';
		WriteConsoleOutputCharacter(console, screen, screen_width_ * screen_height_, { 0, 0 }, &bytes_written);
	}

	return ContextState::kContextTitleScreen;
}

void ContextTitleScreen::PutText(wchar_t* screen, int w, int h, TitleScreenText text_type)
{
	//w and h should be bigger than 0.
	for (int height = h; height < h + text_list_[(int)text_type].size(); height++)
	{
		wcscpy_s(&screen[screen_width_ * height + w], wcslen(screen), text_list_[(int)text_type][height - h].data());
	}
}