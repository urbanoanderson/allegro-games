#include "player.h"

void Player::Initialize(int x, int y)
{
    iniX = x;
    iniY = y;
    this->dir = DOWN;

    this->imortal = false;

    this->anim[UP].Initialize(game_player_up, 4, 0.1, true);
    this->anim[DOWN].Initialize(game_player_down, 4, 0.1, true);
    this->anim[LEFT].Initialize(game_player_left, 4, 0.1, true);
    this->anim[RIGHT].Initialize(game_player_right, 4, 0.1, true);

    this->box[UP].Initialize(-13, -18, 29, 30);
    this->box[DOWN].Initialize(-13, -18, 29, 32);
    this->box[LEFT].Initialize(-17, -15, 25, 25);
    this->box[RIGHT].Initialize(-9, -15, 28, 25);

    this->vidas = STARTVIDAS;
    ResetStats();
}

void Player::ResetStats()
{
    this->x = iniX;
    this->y = iniY;
    this->numbombas = STARTBOMBAS;
    this->speed = STARTSPEED;
    this->explosionsize = STARTEXPLOSIONSIZE;
    this->tipo_bomba = BOMBA_NORMAL;
    this->podechutar = false;
}

void Player::Die()
{
    ResetStats();
    vidas--;
    dir = DOWN;
    imortal = true;
    timer_imortal = al_get_time();
}

bool Player::CheckCollisionWithObstacles(Tilemap map, int testI, int testJ)
{
    //Colisão contra tiles
    if(map.GetTileID(testI, testJ) != GRASS)
    {
        return box[dir].CollisionWithTiles( (testJ)*TILESIZE + MAP_X0, (testI)*TILESIZE + MAP_Y0, TILESIZE, TILESIZE);
    }

    //Colisão contra bombas
    else if(map.GetBombPos(testI, testJ) == 1)
    {
        return box[dir].CollisionWithTiles( (testJ)*TILESIZE + MAP_X0, (testI)*TILESIZE + MAP_Y0, TILESIZE, TILESIZE);
    }

    return false;
}

void Player::PutBomb(Tilemap &map)
{
    if(bomb_list.size() < (unsigned) numbombas && map.GetBombPos(posI, posJ) == 0)
    {
     al_play_sample(SFX_put_bomb, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
     Bomb nova;
     nova.Initialize(((x-MAP_X0)/TILESIZE)*TILESIZE + MAP_X0 + TILESIZE/2, ((y-MAP_Y0)/TILESIZE)*TILESIZE + TILESIZE/2 + MAP_Y0, tipo_bomba, TEMPO_ATE_DETONACAO, map);
     bomb_list.push_back(nova);
    }
}

void Player::RaiseSpeed()
{
    speed++;

    if(speed > MAXSPEED)
     speed = MAXSPEED;
}

void Player::RaiseFire()
{
    explosionsize++;

    if(explosionsize > MAXEXPLOSIONSIZE)
     explosionsize = MAXEXPLOSIONSIZE;
}

void Player::RaiseLife()
{
    vidas++;

    if(vidas > MAXVIDAS)
     vidas = MAXVIDAS;
}

void Player::RaiseNumBombs()
{
    numbombas++;

    if(numbombas > MAXBOMBAS)
     numbombas = MAXBOMBAS;
}

void Player::DetonateRemoteBomb(Tilemap &map)
{
    for(it = bomb_list.begin(); it != bomb_list.end(); it++)
    {
        if((*it).GetType() == BOMBA_RELOGIO)
        {
            (*it).Detonate(map);
            break;
        }
    }
}

void Player::MoveBomb(int i, int j)
{
    for(it = bomb_list.begin(); it != bomb_list.end(); it++)
    {
        //Se achou a bomba e ela não está se movendo
        if( !(*it).GetInMotion() && (*it).GetI() == i && (*it).GetJ() == j )
        {
            (*it).KickBomb(dir);
        }
    }
}

void Player::Move(Tilemap &map)
{
    ///INPUT=========================================

    int prevX = x;
    int prevY = y;

    //UP
    if(al_key_down(&keystate, ALLEGRO_KEY_UP)
    || joy1_state.stick[0].axis[1] < 0)
    {
       y -= speed;
       dir = UP;

       if(CheckCollisionWithObstacles(map, posI-1, posJ)
       || CheckCollisionWithObstacles(map, posI-1, posJ-1)
       || CheckCollisionWithObstacles(map, posI-1, posJ+1)  )
       {
         x = prevX;
         y = prevY;

          //Chutando bombas
          if(podechutar && map.GetBombPos(posI-1, posJ) == 1)
            MoveBomb(posI-1, posJ);
       }
    }

    //DOWN
    else if( al_key_down(&keystate, ALLEGRO_KEY_DOWN)
    || joy1_state.stick[0].axis[1] > 0 )
    {
       y += speed;
       dir = DOWN;

       if(CheckCollisionWithObstacles(map, posI+1, posJ)
       || CheckCollisionWithObstacles(map, posI+1, posJ-1)
       || CheckCollisionWithObstacles(map, posI+1, posJ+1)  )
       {
            x = prevX;
            y = prevY;

            //Chutando bombas
            if(podechutar && map.GetBombPos(posI+1, posJ) == 1)
                MoveBomb(posI+1, posJ);
       }
    }

    //LEFT
    else if( al_key_down(&keystate, ALLEGRO_KEY_LEFT)
    || joy1_state.stick[0].axis[0] < 0 )
    {
       x -= speed;
       dir = LEFT;

       if(CheckCollisionWithObstacles(map, posI, posJ-1)
       || CheckCollisionWithObstacles(map, posI-1, posJ-1)
       || CheckCollisionWithObstacles(map, posI+1, posJ-1)  )
       {
            x = prevX;
            y = prevY;

            //Chutando bombas
            if(podechutar && map.GetBombPos(posI, posJ-1) == 1)
                MoveBomb(posI, posJ-1);
       }
    }

    //RIGHT
    else if( al_key_down(&keystate, ALLEGRO_KEY_RIGHT)
    || joy1_state.stick[0].axis[0] > 0 )
    {
        x += speed;
        dir = RIGHT;

       if(CheckCollisionWithObstacles(map, posI, posJ+1)
       || CheckCollisionWithObstacles(map, posI-1, posJ+1)
       || CheckCollisionWithObstacles(map, posI+1, posJ+1)  )
       {
            x = prevX;
            y = prevY;

            //Chutando bombas
            if(podechutar && map.GetBombPos(posI, posJ+1) == 1)
                MoveBomb(posI, posJ+1);
       }
    }

    //NÃO ESTÁ SE MOVENDO
    else
    {
        anim[dir].Reset();
    }
}

void Player::Update(Tilemap &map)
{
    posI = (y - MAP_Y0) / TILESIZE;
    posJ = (x - MAP_X0) / TILESIZE;

    Move(map);

    ///===============================================

    anim[dir].Update();
    box[dir].UpdatePosition(x, y);

    //Atualiza lista de bombas
    for(it = bomb_list.begin(); it != bomb_list.end(); it++)
    {
        (*it).Update(map);

        //Se a bomba estourou
        if( (*it).GetActive() == false )
        {
            //Cria a explosão
            Explosion nova;
            nova.Initialize(bomb_list, map, explosionsize, (*it).GetI(), (*it).GetJ(), DURACAO_EXPLOSAO, ((*it).GetType() == BOMBA_ESPINHO));
            explosion_list.push_back(nova);

            //Remove a bomba da lista
            it = bomb_list.erase(it);
        }
    }

    //Atualiza lista de Explosões
    for(it2 = explosion_list.begin(); it2 != explosion_list.end(); it2++)
    {
        (*it2).Update(upgrade_list, map);

        //Checa se o boneco encostou em alguma explosão
        if(!imortal && (box[dir].CheckCollision( (*it2).GetBoxY() ) || box[dir].CheckCollision( (*it2).GetBoxX() )) )
         Die();

        //Remove da lista as explsões que terminaram
        if( (*it2).GetActive() == false )
        {
            it2 = explosion_list.erase(it2);
        }
    }

    //Atualiza lista de Upgrades
    for(it3 = upgrade_list.begin(); it3 != upgrade_list.end(); it3++)
    {
        (*it3).Update();

        //Entrou em contato com o upgrade
        if(box[dir].CheckCollision((*it3).GetBox()) == true)
        {
            al_play_sample(SFX_pick_upgrade, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

            if( (*it3).GetID() == EXTRA_BOMB )
              RaiseNumBombs();
            else if( (*it3).GetID() == FIRE )
              RaiseFire();
            else if( (*it3).GetID() == SPEED )
              RaiseSpeed();
            else if( (*it3).GetID() == EXTRA_LIFE )
              RaiseLife();
            else if( (*it3).GetID() == REMOTE_BOMB )
              tipo_bomba = BOMBA_RELOGIO;
            else if( (*it3).GetID() == SPIKE_BOMB )
              tipo_bomba = BOMBA_ESPINHO;
            else if( (*it3).GetID() == KICK_BOMBS )
              podechutar = true;

            it3 = upgrade_list.erase(it3);
        }
    }

    //Imortalidade temporária
    if(imortal && al_get_time() - timer_imortal >= TEMPO_IMORTALIDADE)
     imortal = false;

}

void Player::Draw()
{
    //Desenha lista de bombas
    for(it = bomb_list.begin(); it != bomb_list.end(); it++)
    {
        (*it).Draw();
    }

    //Desenha lista de Explosões
    for(it2 = explosion_list.begin(); it2 != explosion_list.end(); it2++)
    {
        (*it2).Draw();
    }

    //Desenha lista de Upgrades
    for(it3 = upgrade_list.begin(); it3 != upgrade_list.end(); it3++)
    {
        (*it3).Draw();
    }

    //Desenha o Boneco

    if(!imortal || (imortal && ((int)(al_get_time()*1000)/100)%2 == 0) )
    anim[dir].Draw(x, y-15, 0.9, 0.9, 0, al_map_rgba(255, 255, 255, 255));

    #if DEBUG
        if(debug_mode){
		box[dir].Draw();
		al_draw_filled_circle(x, y, 3, al_map_rgba(255,0,0,255));

        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);

        al_draw_textf(font_debug, al_map_rgb(0, 0, 0), x, y+15, ALLEGRO_ALIGN_CENTER, "Pos I: %d, Pos J: %d", posI, posJ);
        al_draw_textf(font_debug, al_map_rgb(0, 0, 0), x, y+25, ALLEGRO_ALIGN_CENTER, "x: %d, y: %d", x, y);
        }
	#endif
}
