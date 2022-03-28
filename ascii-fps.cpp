#include <iostream>
#include <windows.h>
#include <wchar.h>
#include <string>

int screen_width = 120;
int screen_height = 40;


float player_x = 0.0f;
float player_y = 0.0f;
float player_ang = 0.0f; // 지도상 플레이어 시선의 각도.


int map_height = 16;
int map_width = 16;

float fov = 3.141592 / 4.0; // field of view. pi / 4 만큼의 각도가 보인다고 한다.

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

        for (int x = 0; x < screen_width; x++)
        {
            float ray_angle = ( player_ang - fov / 2.0f ) + ( static_cast<float>(x) / static_cast<float>(screen_width) ) * fov;
            // ( player_ang - fov / 2.0f ) : ray_angle의 시작. 
            // fov를 스크린 넓이 수만큼 나눈 것. 즉, 그림 안에 들어오는 각도 ray_angle은 -fov/2 부터 fov/2까지이다. 
        }


        screen[screen_width * screen_height - 1] = L'\0'; // '\0'
        WriteConsoleOutputCharacter(console, screen, screen_width * screen_height, { 0, 0 }, &bytes_written);
        // WriteConsoleOutputCharacter : 문자를 출력한다.
        // 인자 : 핸들, 버퍼(input characters), length, 좌표(글자 위치, 이 경우 항상 tl에 쓸 것.), the number of the chars written.
    }

}
