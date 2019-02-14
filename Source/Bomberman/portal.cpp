#include "portal.h"

void Portal::Initialize(int i, int j)
{
    anim.Initialize(game_portal, 4, ALLEGRO_MSECS_TO_SECS(150), true);
    this->i = i;
    this->j = j;

    this->x = MAP_X0 + j * TILESIZE + TILESIZE/2;
    this->y = MAP_Y0 + i * TILESIZE + TILESIZE/2;
}

bool Portal::Update(Tilemap map, int playerX, int playerY, int enemy_list_size)
{
    anim.Update();

    if(map.GetTileID(i, j) == GRASS && enemy_list_size <= 0)
    {
        if( sqrt((playerX-x)*(playerX-x) + (playerY-y)*(playerY-y)) < 10 )
          return true;
    }

    //retorna se o portal deve funcionar ou não
    return false;
}

void Portal::Draw(Tilemap map, int enemy_list_size)
{
    if(map.GetTileID(i, j) == GRASS && enemy_list_size <= 0)
      anim.Draw(MAP_X0 + j * TILESIZE + TILESIZE/2, MAP_Y0 + i * TILESIZE + TILESIZE/2, 1.0, 1.0, 0.0, al_map_rgb(255,255,255));

    #if DEBUG
     if(debug_mode)
     al_draw_filled_circle(x, y, 3, al_map_rgba(255,0,0,255));
    #endif
}
