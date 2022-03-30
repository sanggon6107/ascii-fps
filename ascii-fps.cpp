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
float depth = 16.0f; // 앞에 벽이 있는지 확인하기 위한 최대 깊이.

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
        {   // 플레이어의 시각을 촘촘하게 잘라서, 각 각도별로 벽에 닿을 때까지의 거리를 계산한다.
            float ray_angle = ( player_ang - fov / 2.0f ) + ( static_cast<float>(x) / static_cast<float>(screen_width) ) * fov;
            // ( player_ang - fov / 2.0f ) : ray_angle의 시작. 
            // fov를 스크린 넓이 수만큼 나눈 것. 즉, 그림 안에 들어오는 각도 ray_angle은 -fov/2 부터 fov/2까지이다. 

            float distance_to_wall = 0;
            bool hit_wall = false;

            float eye_x = sinf(ray_angle); // 단위 벡터.
            float eye_y = cosf(ray_angle);


            while (!hit_wall && distance_to_wall < depth)
            {
                distance_to_wall += 0.1f;

                int test_x = (int)(player_x + eye_x * distance_to_wall);
                int test_y = (int)(player_y + eye_y * distance_to_wall);

                if (test_x < 0 || test_x >= map_width || test_y < 0 || test_y >= map_height) // test_x (테스트 지점)이 맵 바깥에 있는 경우
                {
                    hit_wall = true;
                    distance_to_wall = depth; // distance_to_wall은 그냥 최대.
                }
                else // test_x (테스트 지점)이 맵 안에 있는 경우 그 지점이 벽인지 아닌지 판단한다.
                {
                    if (std::to_string(map[test_y * map_width + test_x]) == "#") // (x, y)가 벽이라면
                    {
                        hit_wall = true;
                    }
                }
            }

            // 바닥, 천장까지의 거리 계산. distance_to_wall이 길어질 수록 시야상 벽이 작아보이고, 천장과 바닥이 많이 보인다.
            
            int ceiling = (float)(screen_height / 2, 0) - screen_height / (float)distance_to_wall;
            int floor = screen_height - ceiling; // 바닥은 그냥 천장을 반대로



        }


        screen[screen_width * screen_height - 1] = L'\0'; // '\0'
        WriteConsoleOutputCharacter(console, screen, screen_width * screen_height, { 0, 0 }, &bytes_written);
        // WriteConsoleOutputCharacter : 문자를 출력한다.
        // 인자 : 핸들, 버퍼(input characters), length, 좌표(글자 위치, 이 경우 항상 tl에 쓸 것.), the number of the chars written.
    }

}
