#include "bomb.h"

void Bomb::Initialize(int x, int y, int tipo, float time_until_explosion, Tilemap &map)
{
   this->x = x;
   this->y = y;
   this->posI = (y - MAP_Y0) / TILESIZE;
   this->posJ = (x - MAP_X0) / TILESIZE;
   this->box.Initialize(-16, -13, 34, 30);
   this->tipo = tipo;

   this->in_motion = false;

   if(tipo == BOMBA_NORMAL)
     this->anim.Initialize(game_bomb, 4, ALLEGRO_MSECS_TO_SECS(150), true);
   else if(tipo == BOMBA_RELOGIO)
     this->anim.Initialize(game_bomba_relogio, 4, ALLEGRO_MSECS_TO_SECS(150), true);
   else if(tipo == BOMBA_ESPINHO)
     this->anim.Initialize(game_bomba_espinho, 4, ALLEGRO_MSECS_TO_SECS(150), true);

   this->active = true;
   this->time_until_explosion = time_until_explosion;
   this->timer = al_get_time();

   map.SetBombPos(posI, posJ, 1);
}

bool Bomb::IsOnTheCenterOfTile()
{
    int a = (x - MAP_X0)%(TILESIZE);
    int b = (y - MAP_Y0)%(TILESIZE);
    return (a >= TILESIZE/2 - VELOCIDADE_BOMBA && a <= TILESIZE/2 + VELOCIDADE_BOMBA
         && b >= TILESIZE/2 - VELOCIDADE_BOMBA && b <= TILESIZE/2 + VELOCIDADE_BOMBA  );
}

bool Bomb::CheckForObstaclesOnTile(Tilemap &map, int i, int j)
{
    return map.IsPathBlocked(i, j);
}

void Bomb::Update(Tilemap &map)
{
    //Atualiza índices (muda no mapa também)
    map.SetBombPos(posI, posJ, 0);
    posI = (y - MAP_Y0) / TILESIZE;
    posJ = (x - MAP_X0) / TILESIZE;
    map.SetBombPos(posI, posJ, 1);

    //Se está em Movimento
    if(in_motion)
    {
        //Move a bomba
        if(dir == UP)
            y -= VELOCIDADE_BOMBA;
        else if(dir == DOWN)
            y += VELOCIDADE_BOMBA;
        else if(dir == LEFT)
            x -= VELOCIDADE_BOMBA;
        else if(dir == RIGHT)
            x += VELOCIDADE_BOMBA;

        //Testar se já pode parar
        if(IsOnTheCenterOfTile())
        {
            if( (dir == UP && CheckForObstaclesOnTile(map, posI-1, posJ))
            ||  (dir == DOWN && CheckForObstaclesOnTile(map, posI+1, posJ))
            ||  (dir == LEFT && CheckForObstaclesOnTile(map, posI, posJ-1))
            ||  (dir == RIGHT && CheckForObstaclesOnTile(map, posI, posJ+1)) )
            {
                in_motion = false;
                x = MAP_X0 + TILESIZE*posJ + TILESIZE/2;
                y = MAP_Y0 + TILESIZE*posI + TILESIZE/2;
            }
        }
    }

    box.UpdatePosition(x, y);
    anim.Update();

    if(al_get_time() - timer >= time_until_explosion && tipo != BOMBA_RELOGIO)
     Detonate(map);
}

void Bomb::Draw()
{
    anim.Draw(x, y, 1.0, 1.0, 0, al_map_rgba(255, 255, 255, 255));

    #if DEBUG
        if(debug_mode)
        {
            box.Draw();

            if(in_motion)
                al_draw_textf(font_debug, al_map_rgb(255, 0, 0), x, y+45, ALLEGRO_ALIGN_CENTER, "IN MOTION");

            al_draw_textf(font_debug, al_map_rgb(0, 0, 0), x, y+25, ALLEGRO_ALIGN_CENTER, "POS I: %d, POS J: %d", posI, posJ);
            al_draw_textf(font_debug, al_map_rgb(0, 0, 0), x, y+35, ALLEGRO_ALIGN_CENTER, "x: %d, y: %d", x, y);

        }
    #endif
}
