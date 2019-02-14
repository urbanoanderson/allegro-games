#ifndef VENDER_H_INCLUDED
#define VENDER_H_INCLUDED

#include "Torre.h"

typedef struct b_venda
{
    int x;
    int y;
    int highlight;
    int ativado;
}Button_Venda;

Button_Venda* Create_Button_Venda(int x, int y);
void Update_Button_Venda(Button_Venda* b, Stage* s);
void Draw_Button_Venda(Button_Venda* b, BITMAP* buffer);
void Destroy_Button_Venda(Button_Venda* b);

#endif // VENDER_H_INCLUDED
