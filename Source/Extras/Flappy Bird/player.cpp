#include "player.h"

void Player::Initialize()
{
    this->x = PLAYER_INITIAL_X;
    this->y = PLAYER_INITIAL_Y;
    this->speed_y = 0.0;
    this->score = 0;
    this->alive = true;
    this->box.Initialize(x, y, width(game_player), height(game_player));
}

void Player::WinPoint()
{
    score++;
    al_play_sample(SFX_ponto, volSFX, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Player::Die()
{
    alive = false;
}

void Player::Jump()
{
    speed_y = PLAYER_JUMP_SPEED;
}

void Player::Update()
{
    if(alive)
    {
        //Update speed and position
        speed_y += GRAVITY;
        y += speed_y;

        //Update bounding box
        box.UpdatePosition(x, y);

        //Se tocar no chão morre
        if(y > 445)
            Die();
    }
}

void Player::Draw()
{
    if(alive)
        al_draw_bitmap(game_player, x, y, 0);

    if(DEBUG)
        box.Draw(al_map_rgb(0,0,255));
}
