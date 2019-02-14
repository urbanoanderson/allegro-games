#include "tilemap.h"

void Tilemap::Initialize(FILE* f, int portalI, int portalJ)
{
    this->portalI = portalI;
    this->portalJ = portalJ;

    if(f)
    {
        for(int i = 0; i < TILES_I; i++)
        {
            for(int j = 0; j < TILES_J; j++)
            {
             fscanf(f, "%d", &matriz[i][j]);

             //Inicializa matriz de inimigos e de bombas
             matbombas[i][j] = 0;
             matenemies[i][j] = 0;
            }
        }
    }
}

void Tilemap::Draw()
{
    for(int i = 0; i < TILES_I; i++)
    {
       for(int j = 0; j < TILES_J; j++)
       {
          al_draw_bitmap(game_tile[matriz[i][j]], MAP_X0 + j * TILESIZE, MAP_Y0 + i * TILESIZE, 0);

          #if DEBUG
          if(debug_mode)
           al_draw_textf(font_debug, al_map_rgba(255, 255, 0, 255), MAP_X0+j*TILESIZE + TILESIZE/2, MAP_Y0+i*TILESIZE + TILESIZE/2, ALLEGRO_ALIGN_CENTER, "%d, %d", matriz[i][j], matbombas[i][j]);
          #endif
       }
    }
}
