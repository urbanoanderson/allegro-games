#include "TowerButton.h"


TowerButton* Create_TowerButton(BITMAP* img, int x, int y, int ID)
{
   TowerButton* b = (TowerButton*) malloc(sizeof(TowerButton));
   b->img = img;
   b->ID = ID;
   b->pos_x = x;
   b->pos_y = y;
   b->ativado = FALSE;

   return b;
}


void Update_TowerButton(TowerButton* b, Stage* s, int* usando_botao)
{
   //Se está em cima do botão
  if(mouse_x > b->pos_x && mouse_x < b->pos_x + b->img->w
  && mouse_y > b->pos_y && mouse_y < b->pos_y + b->img->h
  && getpixel(b->img, mouse_x - b->pos_x, mouse_y - b->pos_y) != makecol(255,0,255)
  && !(*usando_botao)   )
  {
    //Se o botão ainda não está ativo e clicou em cima
    if(mouse_b == 1 && !b->ativado)
    {
       play_sample(FX_click, 255, 128, 1000, FALSE);
       b->ativado = TRUE;
       *usando_botao = TRUE;
    }
  }

  //Se a pessoa soltou o clique
  if(b->ativado == TRUE && mouse_b == 0)
  {
     b->ativado = FALSE;
     *usando_botao = FALSE;

     int able_to_insert = FALSE;

     int i = (mouse_y - Y0)/TILESIZE;
     int j = (mouse_x - X0)/TILESIZE;

     if(i >= 0 && i < NUMTILESI
     && j >= 0 && j < NUMTILESJ
     && mtx[i][j] == NULL
     && s->map->matriz[i][j] == 0)
     {
       if(b->ID == TORRE_NORMAL && s->dinheiro >= 4)
       { able_to_insert = TRUE; s->dinheiro -= 4; }
       else if(b->ID == TORRE_SLOW && s->dinheiro >= 6)
       { able_to_insert = TRUE; s->dinheiro -= 6; }
       else if(b->ID == TORRE_ANTITANQUE && s->dinheiro >= 8)
       { able_to_insert = TRUE; s->dinheiro -= 8; }
       else if(b->ID == TORRE_VENENO && s->dinheiro >= 12)
       { able_to_insert = TRUE; s->dinheiro -= 12; }
     }

     if(able_to_insert){
      Insert_Tower_on_Matrix(b->ID, i, j);
      play_sample(FX_buy, 255, 128, 1000, FALSE);
     }
     else
      play_sample(FX_error, 255, 128, 1000, FALSE);
  }
}


void Draw_TowerButton(TowerButton* b, BITMAP* buffer)
{
     draw_sprite(buffer, b->img, b->pos_x,  b->pos_y);

    if(b->ativado)
    {
       //Highlight no botão
       draw_sprite(buffer,  b_torre_h, b->pos_x,  b->pos_y);

       if(mouse_x >= X0 && mouse_x <= X0 + TILESIZE*NUMTILESJ
       && mouse_y >= Y0 && mouse_y <= Y0 + TILESIZE*NUMTILESI  )
       {
           int mouse_j = (mouse_x - X0)/TILESIZE;
           int mouse_i = (mouse_y - Y0)/TILESIZE;

           draw_trans_sprite(buffer, b->img, mouse_j*TILESIZE + X0, mouse_i*TILESIZE + Y0);
       }

    }
}


void Destroy_TowerButton(TowerButton* b)
{
    free(b);
}
