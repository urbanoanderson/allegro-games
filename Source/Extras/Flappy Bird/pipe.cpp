#include "pipe.h"

void Pipe::Initialize(float x)
{
    this->active = true;
    this->point_given = false;
    this->x = x;
    this->y = rand()%250 + 200;

    this->box_up.Initialize(x, y-SPACE_BEETWEEN_PIPES-800, PIPE_WIDTH, 800);
    this->box_down.Initialize(x, y, PIPE_WIDTH, GROUND_Y-y);
}

void Pipe::Update(Player* player)
{
    x -= BACKGROUND_SPEED;

    //Chegou ao fim da tela
    if(x+PIPE_WIDTH < 0)
      active = false;

    //Atribui pontos ao jogador
    if(!point_given && player->GetAlive() && player->GetX() > x)
    {
        player->WinPoint();
        point_given = true;
    }

    //Checa de o jogador morreu
    if(CheckCollision(box_up, player->GetBox()) || CheckCollision(box_down, player->GetBox()))
    {
        player->Die();
    }

    box_up.UpdatePosition(x, y-SPACE_BEETWEEN_PIPES-800);
    box_down.UpdatePosition(x, y);
}

void Pipe::Draw()
{
    //Cano de baixo
    al_draw_bitmap_region(game_pipe, 0, 0, width(game_pipe), GROUND_Y-y, x, y-2, 0);

    //Cano de cima
    al_draw_bitmap_region(game_pipe, 0, 0, width(game_pipe), y-SPACE_BEETWEEN_PIPES, x, 0,  ALLEGRO_FLIP_VERTICAL);

    if(DEBUG)
    {
        box_up.Draw(al_map_rgb(255,0,0));
        box_down.Draw(al_map_rgb(255,0,0));
    }
}

//------------------------------------------------------------------------------------
//Lista


void PipeList::InsertPipe(float x)
{
    Pipe novo;
    novo.Initialize(x);
    pipe_list.push_front(novo);
}

void PipeList::Initialize()
{
    InsertPipe(SCREEN_W);
    InsertPipe(SCREEN_W + PIPE_WIDTH + SPACE_BEETWEEN_PIPES);
    InsertPipe(SCREEN_W + 2*PIPE_WIDTH + 2*SPACE_BEETWEEN_PIPES);
}

void PipeList::Update(Player* player)
{
     for(it = pipe_list.begin(); it != pipe_list.end(); it++)
     {
         (*it).Update(player);

         if( (*it).GetActive() == false )
        {
            it = pipe_list.erase(it);
            InsertPipe(SCREEN_W);
        }
     }
}

void PipeList::Draw()
{
    for(it = pipe_list.begin(); it != pipe_list.end(); it++)
     {
         (*it).Draw();
     }
}

void PipeList::ResetPipes()
{
    pipe_list.clear();
    Initialize();
}
