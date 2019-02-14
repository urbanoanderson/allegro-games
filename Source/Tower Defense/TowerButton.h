#ifndef TOWERBUTTON_H_INCLUDED
#define TOWERBUTTON_H_INCLUDED

#include "init.h"
#include "Torre.h"
#include "Stage.h"

typedef struct towerbutton
{
  BITMAP* img;
  int pos_x;
  int pos_y;
  int ID;

  int ativado;
}TowerButton;


TowerButton* Create_TowerButton(BITMAP* img, int x, int y, int ID);
void Update_TowerButton(TowerButton* b, Stage* s, int* usando_botao);
void Draw_TowerButton(TowerButton* b, BITMAP* buffer);
void Destroy_TowerButton(TowerButton* b);

#endif
