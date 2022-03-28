#include <iostream>
#include <windows.h>
#include <wchar.h>
#include <string>

int screen_width = 120;
int screen_height = 40;


float player_x = 0.0f;
float player_y = 0.0f;
float player_ang = 0.0f;


int map_height = 16;
int map_width = 16;


int main()
{
    // 스크린 버퍼 만들기. cout을 이용한 출력은 느리므로 버퍼를 만들어서 직접 입력한다.
    wchar_t* screen = new wchar_t[screen_width * screen_height]; // wide character
    HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // creates a screen buffer for the Windows Console.
    SetConsoleActiveScreenBuffer(console); // Sets the specified screen buffer to be the currently displayed console screen buffer.
    DWORD bytes_written = 0;


    std::wstring map;

    map += L"################";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";


    while (1)
    {
        screen[screen_width * screen_height - 1] = L'\0'; // '\0'
        WriteConsoleOutputCharacter(console, screen, screen_width * screen_height, { 0, 0 }, &bytes_written);
        // WriteConsoleOutputCharacter : 문자를 출력한다.
        // 인자 : 핸들, 버퍼(input characters), length, 좌표(글자 위치, 이 경우 항상 tl에 쓸 것.), the number of the chars written.
    }

}
