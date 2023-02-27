#include "ContextGamePlay.h"

ContextGamePlay::ContextGamePlay() : mouse_(), current_stage_(0), map_width_unit_(17), map_height_unit_(17) {}

ContextState ContextGamePlay::Run()
{
    current_stage_ = 0;

    constexpr float fov = 3.141592f / 4.0f;
    constexpr float depth = 16.0f;

    auto& screen_mgr = ScreenMgr::GetInstance();

    Player player{ .x_ = 1.0f, .y_ = 1.0f, .ang_ = 0.0f };
    MapInfo map_info;
    shared_ptr<MapCreator> map_creator = make_shared<MapCreator>(map_width_unit_, map_height_unit_);
    
    InitStage(player, map_info, map_creator);
    
    auto tp_1 = std::chrono::system_clock::now();
    auto tp_2 = std::chrono::system_clock::now();

    while (1)
    {
        tp_2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_time = tp_2 - tp_1; // 프레임 전환 지체 시간.
        tp_1 = tp_2;
        float f_elapsed_time = elapsed_time.count();

        if (round(player.x_) == map_info.map_width_ - 2 && round(player.y_) == map_info.map_height_- 2) { InitStage(player, map_info, map_creator); }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { return ContextState::kContextTitleScreen; }

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000) { MoveOnUserKeyUpdate(player, map_info, f_elapsed_time, CharactorDirection::kLeft); }
        if (GetAsyncKeyState((unsigned short)'D') & 0x8000) { MoveOnUserKeyUpdate(player, map_info, f_elapsed_time, CharactorDirection::kRight); }
        if (GetAsyncKeyState((unsigned short)'W') & 0x8000) { MoveOnUserKeyUpdate(player, map_info, f_elapsed_time, CharactorDirection::kForward); }
        if (GetAsyncKeyState((unsigned short)'S') & 0x8000) { MoveOnUserKeyUpdate(player, map_info, f_elapsed_time, CharactorDirection::kBackward); }
        SetMouseToZero();
        MoveOnUserMouseUpdate(player);

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


                if (test_x < 0 || test_x >= map_info.map_width_ || test_y < 0 || test_y >= map_info.map_height_)
                {
                    is_hit_wall = true;
                    distance_to_wall = depth;
                }
                else if (map_info.map_[test_y * map_info.map_width_ + test_x] == '#')
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
                    screen_[y * screen_width_ + x] = ' ';
                }
                else if (y > floor) 
                {
                    if (y < static_cast<int>(screen_height_ / 2) * 1.45)  screen_[y * screen_width_ + x] = '.';
                    else  screen_[y * screen_width_ + x] = 'X';

                }
                else
                {
                    screen_[y * screen_width_ + x] = shade;
                }
            }
        }
        ShowFrame(map_info, player, screen_mgr);
    }
	return ContextState::kContextExit;
}


void ContextGamePlay::MoveOnUserKeyUpdate(Player& player, MapInfo& map_info, float elapsed_time, CharactorDirection charactor_direction)
{
    float player_x_temp = 0.0;
    float player_y_temp = 0.0;

    switch (charactor_direction)
    {
    case CharactorDirection::kForward:
        player_x_temp = player.x_ + cosf(player.ang_) * 3.0f * elapsed_time;
        player_y_temp = player.y_ + sinf(player.ang_) * 3.0f * elapsed_time;
        break;

    case CharactorDirection::kBackward:
        player_x_temp = player.x_ - cosf(player.ang_) * 3.0f * elapsed_time;
        player_y_temp = player.y_ - sinf(player.ang_) * 3.0f * elapsed_time;
        break;

    case CharactorDirection::kLeft:
        player_x_temp = player.x_ + sinf(player.ang_) * 3.0f * elapsed_time;
        player_y_temp = player.y_ - cosf(player.ang_) * 3.0f * elapsed_time;
        break;

    case CharactorDirection::kRight:
        player_x_temp = player.x_ - sinf(player.ang_) * 3.0f * elapsed_time;
        player_y_temp = player.y_ + cosf(player.ang_) * 3.0f * elapsed_time;
        break;

    default:
        break;
    }

    if (map_info.map_[static_cast<int>(std::round(player_y_temp)) * map_info.map_width_ + static_cast<int>(std::round(player_x_temp))] != '#')
    {
        player.x_ = player_x_temp;
        player.y_ = player_y_temp;
    }
}

void ContextGamePlay::MoveOnUserMouseUpdate(Player& player)
{
    auto [delta_x, delta_y] = mouse_.DetectMouseMovement();
    player.ang_ += static_cast<float>(delta_x) * 0.001f;
}

void ContextGamePlay::SetMouseToZero()
{
    auto [mouse_x, mouse_y] = mouse_.GetMousePos();

    if (mouse_x > 100 || mouse_x < 30 || mouse_y > 100 || mouse_y < 30)
    {
        mouse_.SetMousePos(70, 50);
        mouse_.UpdateMousePosInfo();
    }

}

void ContextGamePlay::InitStage(Player& player, MapInfo& map_info, shared_ptr<MapCreator> map_creator)
{
    current_stage_ += 1;
    
    player.ang_ = 0.0f;
    player.x_ = 1.0f;
    player.y_ = 1.0f;

    map_info.map_.clear();
    map_creator->CreateMap(current_stage_ * map_width_unit_, current_stage_ * map_height_unit_);
    map_creator->GetCurrentMapInfo(map_info);
}

void ContextGamePlay::ShowFrame(MapInfo& map_info, Player& player, ScreenMgr& screen_mgr)
{
    int top = static_cast<int>(player.y_) - (((kMiniMapHeight + 1) / 2) - 1);
    int left = static_cast<int>(player.x_) - (((kMiniMapWidth + 1) / 2) - 1);
    
    if (top < 0) top = 0;
    else if (top + 16 > map_info.map_height_ - 1) top = map_info.map_height_ - kMiniMapHeight;
    if (left < 0) left = 0;
    else if (left + 16 > map_info.map_width_ - 1) left = map_info.map_width_ - kMiniMapWidth;

    map_info.map_[static_cast<int>(std::round(player.y_)) * map_info.map_width_ + static_cast<int>(std::round(player.x_))] = 0x2588;

    if (GetAsyncKeyState(VK_TAB) & 0x8000)
    {
        for (int pos = 0; pos < map_info.map_.size(); pos++)
        {
            screen_[static_cast<int>(pos / map_info.map_width_) * screen_width_ + pos % map_info.map_width_] = map_info.map_[pos];
        }
    }
    else
    {
        for (int row = 0; row < kMiniMapHeight; row++)
        {
            for (int col = 0; col < kMiniMapWidth; col++)
            {
                screen_[row * screen_width_ + col] = map_info.map_[(row + top) * map_info.map_width_ + (col + left)];
            }
        }
    }

    screen_mgr.Show();
    map_info.map_[static_cast<int>(std::round(player.y_)) * map_info.map_width_ + static_cast<int>(std::round(player.x_))] = L'.';
}