#include <iostream>
#include <windows.h>

int screen_width = 120;
int screen_height = 40;


int main()
{
    // 스크린 버퍼 만들기. cout을 이용한 출력은 느리므로 버퍼를 만들어서 직접 입력한다.
    wchar_t* screen = new wchar_t[screen_width * screen_height];
    HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(console);
    DWORD bytes_written = 0;


}
