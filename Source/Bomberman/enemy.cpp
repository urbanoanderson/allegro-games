#include "enemy.h"

void Enemy::Initialize(int i, int j)
{
    this->anim[UP].Initialize(game_enemy_up, 4, 0.1, true);
    this->anim[DOWN].Initialize(game_enemy_down, 4, 0.1, true);
    this->anim[LEFT].Initialize(game_enemy_left, 4, 0.1, true);
    this->anim[RIGHT].Initialize(game_enemy_right, 4, 0.1, true);

    this->box[UP].Initialize(-16, -22, 32, 32);
    this->box[DOWN].Initialize(-16, -22, 32, 32);
    this->box[LEFT].Initialize(-16, -20, 34, 25);
    this->box[RIGHT].Initialize(-18, -20, 34, 25);

    this->posI = i;
    this->posI = j;
    this->x = MAP_X0 + j*TILESIZE + TILESIZE/2;
    this->y = MAP_Y0 + i*TILESIZE + TILESIZE/2;
    this->speed = ENEMY_SPEED;
    this->vidas = 1;
    this->imortal = false;
    this->ativo = true;

    this->dir = rand() % 4;
    this->state = STATE_CHOOSING;
}

bool Enemy::CheckCollisionWithObstacles(Tilemap map, int testI, int testJ)
{
    if(map.GetTileID(testI, testJ) != GRASS)
    {
        return box[dir].CollisionWithTiles( (testJ)*TILESIZE + MAP_X0, (testI)*TILESIZE + MAP_Y0, TILESIZE, TILESIZE );
    }

    return false;
}

void Enemy::WalkOnCurrentDirection()
{
    if(dir == UP)
     y -= speed;
    else if(dir == DOWN)
     y += speed;
    else if(dir == LEFT)
     x -= speed;
    else
     x += speed;
}

bool Enemy::IsOnTheCenterOfTile()
{
    return ( (x - MAP_X0)%(TILESIZE) == TILESIZE/2 && (y - MAP_Y0)%(TILESIZE) == TILESIZE/2 );
}

void Enemy::CountPaths(Tilemap &map)
{
    numpaths = 0;

    for(int i = 0; i < 4; i++)
    arraypaths[i] = 0;

    if( !map.IsPathBlocked(posI-1, posJ) )
    {
        numpaths++;
        arraypaths[UP] = 1;
    }

    if( !map.IsPathBlocked(posI+1, posJ) )
    {
        numpaths++;
        arraypaths[DOWN] = 1;
    }

    if( !map.IsPathBlocked(posI, posJ-1) )
    {
        numpaths++;
        arraypaths[LEFT] = 1;
    }

    if( !map.IsPathBlocked(posI, posJ+1) )
    {
        numpaths++;
        arraypaths[RIGHT] = 1;
    }
}

void Enemy::Move(Tilemap &map)
{
    //Atualiza índices
    map.SetEnemyPos(posI, posJ, 0);
    posI = (y - MAP_Y0) / TILESIZE;
    posJ = (x - MAP_X0) / TILESIZE;
    map.SetEnemyPos(posI, posJ, 1);

    //Vê quantos caminhos diferentes ele tem
    CountPaths(map);

    //Se está no estado WALKING
    if(state == STATE_WALKING)
    {
        WalkOnCurrentDirection();

        if(IsOnTheCenterOfTile())
        {
            //Se o caminho está bloqueado ou chegou a uma encruzilhada
            if( (dir == UP && map.IsPathBlocked(posI-1, posJ))
             || (dir == DOWN && map.IsPathBlocked(posI+1, posJ))
             || (dir == LEFT && map.IsPathBlocked(posI, posJ-1))
             || (dir == RIGHT && map.IsPathBlocked(posI, posJ+1))
             || ( numpaths > 2 && rand()%100 <= 30) )
            {
                state = STATE_CHOOSING;
            }
        }
    }

    //Está no estado CHOOSING
    else
    {
        //Se não tem nenhum caminho não faz nada
        if(numpaths == 0);

        //Apenas 1 caminho. Segue por ele
        else if(numpaths == 1)
        {
            for(int i = 0; ; i++)
            {
                if(arraypaths[i] == 1)
                {   dir = i; break; }
            }

            state = STATE_WALKING;
        }

        //Possui 2 ou mais caminhos
        else
        {
            //Escolhe direção aleatória que não seja a de onde ele veio
            for(int i = rand()%4; ; i = rand()%4)
            {
                if(arraypaths[i] == 1 && i != oposite_direction(dir))
                {
                    dir = i; break;
                }
            }

            state = STATE_WALKING;
        }
    }
}

void Enemy::Update(Tilemap &map, std::list<Explosion> explosion_list)
{
    anim[dir].Update();
    Move(map);
    box[dir].UpdatePosition(x, y);

    //Imortalidade temporária
    if(imortal && al_get_time() - timer_imortal >= ENEMY_IMORTAL_TIME)
     imortal = false;

    //Colisão contra Explosões
    std::list<Explosion>::iterator it2;
    for(it2 = explosion_list.begin(); it2 != explosion_list.end(); it2++)
    {
        //Checa se o boneco encostou em alguma explosão
        if((box[dir].CheckCollision( (*it2).GetBoxY() ) || box[dir].CheckCollision( (*it2).GetBoxX() )) )
        {
            vidas--;
            if(vidas <= 0)
              ativo = false;

            imortal = true;
            timer_imortal = al_get_time();
        }
    }
}

void Enemy::Draw()
{
    anim[dir].Draw(x, y-15, 0.8, 0.8, 0.0, al_map_rgb(255,255,255));

    #if DEBUG
        if(debug_mode){
		box[dir].Draw();
		al_draw_filled_circle(x, y, 3, al_map_rgb(0,255,0));
		al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), x+10, y+10, ALLEGRO_ALIGN_RIGHT, "State %d", state);
		al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), x+10, y+20, ALLEGRO_ALIGN_RIGHT, "Numpaths %d", numpaths);
        }
	#endif
}
