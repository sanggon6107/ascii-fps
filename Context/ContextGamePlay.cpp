#include "ContextGamePlay.h"

ContextGamePlay::ContextGamePlay(){}

ContextState ContextGamePlay::Run()
{
    const int map_width = 17;
    const int map_height = 17;

    constexpr float fov = 3.141592f / 4.0f;
    constexpr float depth = 16.0f;

    wchar_t* screen = new wchar_t[screen_width_ * screen_height_];
    HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(console);
    DWORD bytes_written = 0;

    Player player{ .x_ = 1.0f, .y_ = 1.0f, .ang_ = 0.0f };

    std::wstring map;
    std::shared_ptr<MapCreator> map_creator = make_shared<MapCreator>(map_width, map_height);
    map_creator->Export(map);

    auto tp_1 = std::chrono::system_clock::now();
    auto tp_2 = std::chrono::system_clock::now();

    while (1)
    {
        tp_2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_time = tp_2 - tp_1; // 프레임 전환 지체 시간.
        tp_1 = tp_2;
        float f_elapsed_time = elapsed_time.count();

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
        {
            player.ang_ -= 2.5f * f_elapsed_time;
        }

        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
        {
            //player_ang += (0.001f);
            player.ang_ += 2.5f * f_elapsed_time;
        }

        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {

            float player_x_temp = player.x_ + cosf(player.ang_) * 5.0f * f_elapsed_time;
            float player_y_temp = player.y_ + sinf(player.ang_) * 5.0f * f_elapsed_time;

            if (map[static_cast<int>(std::round(player_y_temp)) * map_width + static_cast<int>(std::round(player_x_temp))] != '#')
            {
                player.x_ = player_x_temp;
                player.y_ = player_y_temp;
            }
        }

        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
        {
            float player_x_temp = player.x_ - cosf(player.ang_) * 5.0f * f_elapsed_time;
            float player_y_temp = player.y_ - sinf(player.ang_) * 5.0f * f_elapsed_time;

            if (map[static_cast<int>(std::round(player_y_temp)) * map_width + static_cast<int>(std::round(player_x_temp))] != '#')
            {
                player.x_ = player_x_temp;
                player.y_ = player_y_temp;
            }
        }



        for (int x = 0; x < screen_width_; x++)
        {   
            float ray_angle = (player.ang_ - fov / 2.0f) + (static_cast<float>(x) / static_cast<float>(screen_width_)) * fov;

            float distance_to_wall = 0;
            bool is_hit_wall = false;
            bool is_boundary = false;

            float eye_x = cosf(ray_angle);
            float eye_y = sinf(ray_angle);

            int test_x = 0;
            int test_y = 0;


            while (!is_hit_wall && distance_to_wall < depth)
            {
                distance_to_wall += 0.1f;

                test_x = static_cast<int>(std::round(player.x_ + eye_x * distance_to_wall));
                test_y = static_cast<int>(std::round(player.y_ + eye_y * distance_to_wall));


                if (test_x < 0 || test_x >= map_width || test_y < 0 || test_y >= map_height)
                {
                    is_hit_wall = true;
                    distance_to_wall = depth;
                }
                else if (map[test_y * map_width + test_x] == '#')
                {
                    is_hit_wall = true;

                    double wall_pos_x = player.x_ + eye_x * distance_to_wall;
                    double wall_pos_y = player.y_ + eye_y * distance_to_wall;

                    double wall_pos_x_tenths = abs(wall_pos_x - round(wall_pos_x));
                    double wall_pos_y_tenths = abs(wall_pos_y - round(wall_pos_y));
                    if (wall_pos_x_tenths > 0.4 && wall_pos_y_tenths > 0.4) is_boundary = true;
                }
            }

            int ceiling = static_cast<int>(screen_height_ / 2) - static_cast<int>(std::round(screen_height_ / distance_to_wall));
            int floor = screen_height_ - ceiling;


            short shade = ' ';
            if (distance_to_wall > 16.0f) distance_to_wall = 16.0f;
            shade = wall_shades_[static_cast<int>(distance_to_wall)];
            if (is_boundary) shade = ' ';

            for (int y = 0; y < screen_height_; y++)
            {
                if (y < ceiling)
                {
                    screen[y * screen_width_ + x] = ' ';
                }
                else if (y > floor) 
                {
                    if (y < static_cast<int>(screen_height_ / 2) * 1.45)  screen[y * screen_width_ + x] = '.';
                    else  screen[y * screen_width_ + x] = 'X';

                }
                else
                {
                    screen[y * screen_width_ + x] = shade;
                }
            }



        }

        map[static_cast<int>(std::round(player.y_)) * map_width + static_cast<int>(std::round(player.x_))] = L'P';
        for (int pos = 0; pos < map.size(); pos++)
        {
            screen[static_cast<int>(pos / map_width) * screen_width_ + pos % map_width] = map[pos];
        }

        screen[screen_width_ * screen_height_ - 1] = '\0';
        WriteConsoleOutputCharacter(console, screen, screen_width_ * screen_height_, { 0, 0 }, &bytes_written);
        map[static_cast<int>(std::round(player.y_)) * map_width + static_cast<int>(std::round(player.x_))] = L'.';
    }

	return ContextState::kContextExit;
}