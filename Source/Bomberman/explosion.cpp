#include "explosion.h"

void Explosion::Initialize(std::list<Bomb> &lista_bombas, Tilemap &map, int size, int i, int j, float time_until_end, bool flag_espinho)
{
    this->posI = i;
    this->posJ = j;
    this->x = MAP_X0 + TILESIZE*j + TILESIZE/2;
    this->y = MAP_Y0 + TILESIZE*i + TILESIZE/2;
    this->active = true;
    this->time_until_end = time_until_end;
    this->timer = al_get_time();
    this->size = size;

    FindBounds(map, flag_espinho);

    this->box[0].Initialize2(x - THICKNESS/2, y - boundup - THICKNESS/2, THICKNESS, boundup + bounddown + THICKNESS); //Cima/baixo
    this->box[1].Initialize2(x - boundleft - THICKNESS/2, y - THICKNESS/2, boundleft + boundright + THICKNESS, THICKNESS); //Esquerda/Direita

    brick_anim.Initialize(game_brick_explosion, 6, ALLEGRO_MSECS_TO_SECS(80), false);

    //Explode bombas no raio de explosão
    for(std::list<Bomb>::iterator it2 = lista_bombas.begin(); it2 != lista_bombas.end(); it2++ )
    {
        if( (*it2).GetBox().CheckCollision( box[0] )
         || (*it2).GetBox().CheckCollision( box[1] ) )
          (*it2).Detonate(map);
    }

    al_play_sample(SFX_explosion, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Explosion::FindBounds(Tilemap &map, bool flag_espinho)
{
    int maxbound;

    //Limites normais
    boundup = size ;
    bounddown = size;
    boundleft = size;
    boundright = size;

    //-------------------------------
    //Limite superior
    maxbound = 0;

    for(int i = posI-1, j = posJ; maxbound < size; i--)
    {
        if(map.GetTileID(i, j) == GRASS || map.GetTileID(i, j) == INVISIBLE_BLOCK)
        {
           maxbound++;
        }
        else if(map.GetTileID(i, j) == BRICK)
        {
              maxbound++;

              BRICK_INFO novo;
              novo.i = i;
              novo.j = j;
              brick_list.push_back(novo);

              map.SetTileID(i, j, INVISIBLE_BLOCK);

              //Não é espinho - acabou
              if(flag_espinho == 0)
                break;
        }

        //Se for BLOCK ou WALL
        else
            break;
    }

    boundup = maxbound * UNIDADE_DE_EXPLOSAO;

    //------------------------------------
    //Limite inferior
    maxbound = 0;

    for(int i = posI+1, j = posJ; maxbound < size; i++)
    {
        if(map.GetTileID(i, j) == GRASS || map.GetTileID(i, j) == INVISIBLE_BLOCK)
        {
           maxbound++;
        }
        else if(map.GetTileID(i, j) == BRICK)
        {
              maxbound++;

              BRICK_INFO novo;
              novo.i = i;
              novo.j = j;
              brick_list.push_back(novo);

              map.SetTileID(i, j, INVISIBLE_BLOCK);

              //Não é espinho - acabou
              if(flag_espinho == 0)
                break;
        }

        //Se for BLOCK ou WALL
        else
            break;
    }

    bounddown = maxbound * UNIDADE_DE_EXPLOSAO;

    //----------------------------------
    //Limite à esquerda
    maxbound = 0;

    for(int i = posI, j = posJ-1; maxbound < size; j--)
    {
        if(map.GetTileID(i, j) == GRASS || map.GetTileID(i, j) == INVISIBLE_BLOCK)
        {
           maxbound++;
        }
        else if(map.GetTileID(i, j) == BRICK)
        {
              maxbound++;

              BRICK_INFO novo;
              novo.i = i;
              novo.j = j;
              brick_list.push_back(novo);

              map.SetTileID(i, j, INVISIBLE_BLOCK);

              //Não é espinho - acabou
              if(flag_espinho == 0)
                break;
        }

        //Se for BLOCK ou WALL
        else
            break;
    }

    boundleft = maxbound * UNIDADE_DE_EXPLOSAO;

    //---------------------------------
    //Limite à direita
    maxbound = 0;

    for(int i = posI, j = posJ+1; maxbound < size; j++)
    {
        if(map.GetTileID(i, j) == GRASS || map.GetTileID(i, j) == INVISIBLE_BLOCK)
        {
           maxbound++;
        }
        else if(map.GetTileID(i, j) == BRICK)
        {
              maxbound++;

              BRICK_INFO novo;
              novo.i = i;
              novo.j = j;
              brick_list.push_back(novo);

              map.SetTileID(i, j, INVISIBLE_BLOCK);

              //Não é espinho - acabou
              if(flag_espinho == 0)
                break;
        }

        //Se for BLOCK ou WALL
        else
            break;
    }

    boundright = maxbound * UNIDADE_DE_EXPLOSAO;
}

void Explosion::Update(std::list<Upgrade> &upgrade_list, Tilemap &map)
{
    //Se terminou de explodir
    if(al_get_time() - timer >= time_until_end)
    {
        active = false;
    }

    //Atualiza animações de tijolos explodindo
    brick_anim.Update();

    //Testa colisão contra upgrades
    for(std::list<Upgrade>::iterator it2 = upgrade_list.begin(); it2 != upgrade_list.end(); it2++)
    {
        if((box[0].CheckCollision( (*it2).GetBox() )
        || box[1].CheckCollision( (*it2).GetBox() ))
        && !(*it2).GetIndestrutivel() )
         it2 = upgrade_list.erase(it2);
    }

    //Todas as animações acabaram
    if(brick_anim.Finish())
    {
        while(!brick_list.empty())
        {
            it = brick_list.begin();

            //Tira o muro invisível
            map.SetTileID((*it).i, (*it).j, GRASS);

            //Tenta gerar upgrade
            if(rand() % 100 <= CHANCE_UPGRADE && (*it).i != map.GetPortalI() && (*it).j != map.GetPortalJ())
            {
                 Upgrade novo;
                 novo.Initialize(MAP_X0 + (*it).j*TILESIZE, MAP_Y0 + (*it).i*TILESIZE);
                 upgrade_list.push_back(novo);
            }

            brick_list.pop_front();
        }
    }
}

void Explosion::Draw()
{
   al_draw_filled_rounded_rectangle(x - boundleft - THICKNESS/2, y - THICKNESS/2, x + boundright + THICKNESS/2, y + THICKNESS/2, 15, 15, al_map_rgb(255, 127, 39));
   al_draw_filled_rounded_rectangle(x - THICKNESS/2, y - boundup - THICKNESS/2, x + THICKNESS/2, y + bounddown + THICKNESS/2, 10, 10, al_map_rgb(255, 127, 39));
   al_draw_filled_rounded_rectangle(x - boundleft - THICKNESS/2 +8, y - THICKNESS/2 +8, x + boundright + THICKNESS/2 -8, y + THICKNESS/2 -8, 15, 15, al_map_rgb(238, 228, 176));
   al_draw_filled_rounded_rectangle(x - THICKNESS/2 +8, y - boundup - THICKNESS/2 +8, x + THICKNESS/2 -8, y + bounddown + THICKNESS/2 -8, 10, 10, al_map_rgb(238, 228, 176));

   //Desenha a animação dos tijolos explodindo
   for(it = brick_list.begin(); it != brick_list.end(); it++)
   {
      brick_anim.Draw((*it).j * TILESIZE + TILESIZE/2 + MAP_X0, (*it).i * TILESIZE + TILESIZE/2 + MAP_Y0, 1.0, 1.0, 0.0, al_map_rgb(255,255,255));
   }

   #if DEBUG
       if(debug_mode){
       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 20, ALLEGRO_ALIGN_RIGHT, "BOUNDUP: %d", boundup);
       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 30, ALLEGRO_ALIGN_RIGHT, "BOUNDDOWN: %d", bounddown);
       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 40, ALLEGRO_ALIGN_RIGHT, "BOUNDLEFT: %d", boundleft);
       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 50, ALLEGRO_ALIGN_RIGHT, "BOUNDRIGHT: %d", boundright);
       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 60, ALLEGRO_ALIGN_RIGHT, "SIZE: %d", size);
       al_draw_filled_circle(x, y, 2, al_map_rgb(255, 0, 0));
       box[0].Draw();
       box[1].Draw();
       }
   #endif
}
