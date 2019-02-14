#include "upgrade.h"

void Upgrade::Initialize(int x, int y)
{
    this->x = x;
    this->y = y;
    this->ID = GerarID();

    if(ID == EXTRA_BOMB)
     this->anim.Initialize(game_upgrade_bomba_extra, 2, 0.1, true);
    else if(ID == FIRE)
     this->anim.Initialize(game_upgrade_fogo, 2, 0.1, true);
    else if(ID == SPEED)
     this->anim.Initialize(game_upgrade_patins, 2, 0.1, true);
    else if(ID == EXTRA_LIFE)
     this->anim.Initialize(game_upgrade_vida, 2, 0.1, true);
    else if(ID == REMOTE_BOMB)
     this->anim.Initialize(game_upgrade_bomba_relogio, 2, 0.1, true);
    else if(ID == SPIKE_BOMB)
     this->anim.Initialize(game_upgrade_bomba_espinho, 2, 0.1, true);
    else if(ID == KICK_BOMBS)
     this->anim.Initialize(game_upgrade_chuta_bomba, 2, 0.1, true);

    this->box.Initialize2(x, y, anim.Width(), anim.Height());

    this->indestrutivel = true;
    this->timer_indestrutivel = al_get_time();
}

int Upgrade::GerarID()
{
     int novoID = rand() % 100 + 1;

     if(novoID <= 5)
       novoID = EXTRA_LIFE;
     else if(novoID > 5 && novoID <= 10)
       novoID = REMOTE_BOMB;
     else if(novoID > 10 && novoID <= 15)
       novoID = KICK_BOMBS;
     else if(novoID > 15 && novoID <= 25)
       novoID = SPIKE_BOMB;
     else if(novoID > 25 && novoID <= 35)
       novoID = SPEED;
     else if(novoID > 35 && novoID <= 70)
       novoID = FIRE;
     else if(novoID > 70 && novoID <= 100)
       novoID = EXTRA_BOMB;

     return novoID;
}

void Upgrade::Update()
{
    if(al_get_time() - timer_indestrutivel >= TEMPO_INDESTRUTIVEL)
     indestrutivel = false;

    anim.Update();
}

void Upgrade::Draw()
{
    anim.Draw(x+TILESIZE/2, y+TILESIZE/2, 1.0, 1.0, 0.0, al_map_rgb(255,255,255));
}
