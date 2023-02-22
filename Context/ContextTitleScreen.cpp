﻿#include "ContextTitleScreen.h"


ContextState ContextTitleScreen::Run()
{
	int current_cursor_pos = static_cast<int>(TitleScreenText::kStart);
	cursor_.SetCursor(text_position_[current_cursor_pos].w_, text_position_[current_cursor_pos].h_);
	
	auto& screen_mgr = ScreenMgr::GetInstance();

	while (1)
	{
		for (int i = 0; i < screen_height_; i++) { for (int j = 0; j < screen_width_; j++) { screen_[i * screen_width_ + j] = L' '; } }

		PutText(screen_.get(), text_position_[(int)TitleScreenText::kTitle].w_, text_position_[(int)TitleScreenText::kTitle].h_, TitleScreenText::kTitle);
		PutText(screen_.get(), text_position_[(int)TitleScreenText::kStart].w_, text_position_[(int)TitleScreenText::kStart].h_, TitleScreenText::kStart);
		PutText(screen_.get(), text_position_[(int)TitleScreenText::kExit].w_, text_position_[(int)TitleScreenText::kExit].h_, TitleScreenText::kExit);

		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && current_cursor_pos < (int)TitleScreenText::kTitleScreenTextSize - 1)
		{
			++current_cursor_pos;
			cursor_.SetCursor(text_position_[current_cursor_pos].w_, text_position_[current_cursor_pos].h_);
		}
		if ((GetAsyncKeyState(VK_UP) & 0x8000) && current_cursor_pos > (int)TitleScreenText::kStart)
		{
			--current_cursor_pos;
			cursor_.SetCursor(text_position_[current_cursor_pos].w_, text_position_[current_cursor_pos].h_);
		}
		cursor_.ShowCursor(screen_.get());

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			switch (current_cursor_pos)
			{
			case (int)TitleScreenText::kStart :
				return ContextState::kContextGamePlay;

			case (int)TitleScreenText::kExit :
				return ContextState::kContextExit;

			default :
				return ContextState::kContextExit;
			}
		}
		screen_mgr.Show();
	}

	return ContextState::kContextTitleScreen;
}

void ContextTitleScreen::PutText(wchar_t* screen, int w, int h, TitleScreenText text_type)
{
	//w and h should be bigger than 0.
	for (int height = h; height < h + text_list_[(int)text_type].size(); height++)
	{
		wchar_t* char_to_put = text_list_[(int)text_type][height - h].data();
		wcscpy_s(&screen[screen_width_ * height + w], wcslen(char_to_put) + 1, char_to_put);
	}
}

																											   
ContextTitleScreen::ContextTitleScreen() : cursor_(screen_width_, screen_height_)
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

	text_list_[(int)TitleScreenText::kStart].push_back(L"███─███─████─████─███");
	text_list_[(int)TitleScreenText::kStart].push_back(L"█────█──█──█─█──█──█─");
	text_list_[(int)TitleScreenText::kStart].push_back(L"███──█──████─████──█─");
	text_list_[(int)TitleScreenText::kStart].push_back(L"──█──█──█──█─█─█───█─");
	text_list_[(int)TitleScreenText::kStart].push_back(L"███──█──█──█─█─█───█─");

	text_list_[(int)TitleScreenText::kExit].push_back(L"███─██─██─███─███");
	text_list_[(int)TitleScreenText::kExit].push_back(L"█────███───█───█─");
	text_list_[(int)TitleScreenText::kExit].push_back(L"███───█────█───█─");
	text_list_[(int)TitleScreenText::kExit].push_back(L"█────███───█───█─");
	text_list_[(int)TitleScreenText::kExit].push_back(L"███─██─██─███──█─");

	text_position_.resize((int)TitleScreenText::kTitleScreenTextSize, {.w_ = 0, .h_ = 0});
	text_position_[(int)TitleScreenText::kTitle] = { .w_ = 90,  .h_ = 10 };
	text_position_[(int)TitleScreenText::kStart] = { .w_ = 100, .h_ = 40 };
	text_position_[(int)TitleScreenText::kExit]  = { .w_ = 100, .h_ = 50 };

}

int main()
{

	constexpr int screen_width = 240;
	constexpr int screen_height = 80;

	shared_ptr<IContext> ptr = make_shared<ContextTitleScreen>();
	ptr->Run();
	return 0;
}
