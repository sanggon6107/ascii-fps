#include <iostream>
#include <windows.h>
#include <wchar.h>
#include <string>
#include <chrono>
#include <cmath>


constexpr int screen_width = 240;
constexpr int screen_height = 80;

float player_x = 3.0f;
float player_y = 3.0f;
float player_ang = 0.0f; // 지도상 플레이어 시선의 각도.

int map_height = 16;
int map_width = 16;

constexpr float fov = 3.141592f / 4.0f; // field of view. pi / 4 만큼의 각도가 보인다고 한다.
constexpr float depth = 16.0f; // 앞에 벽이 있는지 확인하기 위한 최대 깊이.


int main()
{
    // 스크린 버퍼 만들기. cout을 이용한 출력은 느리므로 버퍼를 만들어서 직접 입력한다.
    wchar_t* screen = new wchar_t[screen_width * screen_height]; // wide character
    HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // creates a screen buffer for the Windows Console.
    SetConsoleActiveScreenBuffer(console); // Sets the specified screen buffer to be the currently displayed console screen buffer.
    DWORD bytes_written = 0;


    std::wstring map;

    map += L"################";
    map += L"#......#.......#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#.........######";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#......#.......#";
    map += L"#......#.......#";
    map += L"########.......#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#......##......#";
    map += L"#..............#";
    map += L"################";

    auto tp_1 = std::chrono::system_clock::now();
    auto tp_2 = std::chrono::system_clock::now();
    

    while (1)
    {
        tp_2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_time = tp_2 - tp_1; // 프레임 전환 지체 시간.
        tp_1 = tp_2;
        float f_elapsed_time = elapsed_time.count(); 

        // 조작부
        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
        {
            //player_ang -= (0.001f); // while문이 돌아가는 속도는 컴퓨터의 연산 속도에 따라 다르다. 다른 프로그램과 같이 실행할 경우, 앵글 컨트롤 게인이 변할 수 있다.
            // 따라서 아래처럼 시스템 시간을 활용하여 콘솔 프레임이 돌아가는 속도와 무관하게 컨트롤 할 수 있도록 한다.
            player_ang -= f_elapsed_time; // elapsed_time이 길어질 수록 프레임간 지체된 시간이 길고, 그 동안 키보드 입력중이었으므로 회전을 더 많이 한다.
        }

        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
        {
            //player_ang += (0.001f);
            player_ang += f_elapsed_time;
        }

        if (GetAsyncKeyState((unsigned short)'W') & 0x8000) // player_ang로 앞으로 나아갔을 때 벽#이 있으면 안된다.
        {
            
            float player_x_temp = player_x + cosf(player_ang) * 5.0f * f_elapsed_time;
            float player_y_temp = player_y + sinf(player_ang) * 5.0f * f_elapsed_time;

            if (map[static_cast<int>(std::round(player_y_temp)) * map_width + static_cast<int>(std::round(player_x_temp))] != '#')
            {
                player_x = player_x_temp;
                player_y = player_y_temp;
            }
        }

        if (GetAsyncKeyState((unsigned short)'S') & 0x8000) // ?
        {
            float player_x_temp = player_x - cosf(player_ang) * 5.0f * f_elapsed_time;
            float player_y_temp = player_y - sinf(player_ang) * 5.0f * f_elapsed_time;

            if (map[static_cast<int>(std::round(player_y_temp)) * map_width + static_cast<int>(std::round(player_x_temp))] != '#')
            {
                player_x = player_x_temp;
                player_y = player_y_temp;
            }
        }



        for (int x = 0; x < screen_width; x++) // x 크기가 120이므로, 한 픽셀씩 생각한다.
        {   // 플레이어의 시각을 촘촘하게 잘라서, 각 각도별로 벽에 닿을 때까지의 거리를 계산한다. (화면의 가로 길이가 120이므로, 화면의 x를 120개로 나눈다.)
            float ray_angle = ( player_ang - fov / 2.0f ) + ( static_cast<float>(x) / static_cast<float>(screen_width) ) * fov;
            // ( player_ang - fov / 2.0f ) : ray_angle의 시작. 
            // fov를 스크린 넓이 수만큼 나눈 것. 즉, 그림 안에 들어오는 각도 ray_angle은 -fov/2 부터 fov/2까지이다. 

            float distance_to_wall = 0;
            bool hit_wall = false;

            float eye_x = cosf(ray_angle); // 각 각도의 단위 벡터.
            float eye_y = sinf(ray_angle);


            while (!hit_wall && distance_to_wall < depth)
            {
                distance_to_wall += 0.1f;

                int test_x = static_cast<int>(std::round(player_x + eye_x * distance_to_wall));
                int test_y = static_cast<int>(std::round(player_y + eye_y * distance_to_wall));

                if (test_x < 0 || test_x >= map_width || test_y < 0 || test_y >= map_height) // test_x (테스트 지점)이 맵 바깥에 있는 경우
                {
                    hit_wall = true;
                    distance_to_wall = depth; // distance_to_wall은 그냥 최대.
                }
                else // test_x (테스트 지점)이 맵 안에 있는 경우 그 지점이 벽인지 아닌지 판단한다.
                {
                    if (map[test_y * map_width + test_x] == '#') // (x, y)가 벽이라면
                    {
                        hit_wall = true;
                    }
                }
            }

            // 바닥, 천장까지의 거리 계산. distance_to_wall이 길어질 수록 시야상 벽이 작아보이고, 천장과 바닥이 많이 보인다.
            
            int ceiling = static_cast<int>(screen_height / 2) - static_cast<int>(std::round(screen_height / distance_to_wall));
            int floor = screen_height - ceiling; // 바닥은 그냥 천장을 반대로


            short shade = ' ';
            if (distance_to_wall <= depth / 4.0f)     shade = 0x2588;
            else if (distance_to_wall < depth / 3.0f) shade = 0x2592;
            else if (distance_to_wall < depth / 2.0f) shade = 0x2593;
            else if (distance_to_wall < depth)        shade = 0x2591;
            else                                      shade = ' ';
            
            for (int y = 0; y < screen_height; y++)
            {
                if (y < ceiling) // sky
                {
                    screen[y * screen_width + x] = ' ';
                }
                else if(y > floor) // 바닥 경계선보다 y가 크다 = 시야상 바닥. 
                {
                    // screen[y * screen_width + x] = ' ';
                    if (y < static_cast<int>(screen_height / 2)  * 1.45)  screen[y * screen_width + x] = '.';
                    else  screen[y * screen_width + x] = 'X';
                    //else if (y < static_cast<int>(screen_height / 2) * 1.75) screen[y * screen_width + x] = 'X';
                    //else screen[y * screen_width + x] = '#';

                }
                else // wall
                {
                    screen[y * screen_width + x] = shade;
                }
            }



        }


        screen[screen_width * screen_height - 1] = '\0'; // '\0'
        WriteConsoleOutputCharacter(console, screen, screen_width * screen_height, { 0, 0 }, &bytes_written);
        // WriteConsoleOutputCharacter : 문자를 출력한다.
        // 인자 : 핸들, 버퍼(input characters), length, 좌표(글자 위치, 이 경우 항상 tl에 쓸 것.), the number of the chars written.
    }

}
