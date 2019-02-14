#ifndef UPGRADE_H_INCLUDED
#define UPGRADE_H_INCLUDED

#include "Torre.h"

typedef struct b_upgrade
{
    int x;
    int y;
    int highlight;
    int ativado;
    int bip;
}Button_Upgrade;

Button_Upgrade* Create_Button_Upgrade(int x, int y);
void Update_Button_Upgrade(Button_Upgrade* b, Stage* s);
void Draw_Button_Upgrade(Button_Upgrade* b, BITMAP* buffer);
void Destroy_Button_Upgrade(Button_Upgrade* b);


#endif // UPGRADE_H_INCLUDED
