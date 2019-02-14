#include "Upgrade.h"


Button_Upgrade* Create_Button_Upgrade(int x, int y)
{
    Button_Upgrade* b = (Button_Upgrade*) malloc(sizeof(Button_Upgrade));

    b->x = x;
    b->y = y;
    b->highlight = FALSE;
    b->ativado = FALSE;
    b->bip = 0;

    return b;
}

void Update_Button_Upgrade(Button_Upgrade* b, Stage* s)
{
    if(selecao != NULL && selecao->level < 3)
    {
      if((selecao->ID == TORRE_NORMAL && s->dinheiro >= TNPRECOUP)
      || (selecao->ID == TORRE_SLOW && s->dinheiro >= TSPRECOUP)
      || (selecao->ID == TORRE_ANTITANQUE && s->dinheiro >= TAPRECOUP)
      || (selecao->ID == TORRE_VENENO && s->dinheiro >= TVPRECOUP)  )
       b->ativado = TRUE;
      else
       b->ativado = FALSE;
    }
    else
      b->ativado = FALSE;

    //Se o botão está ativo
    if( b->ativado
    && mouse_x > b->x && mouse_x < b->x + upgrade->w
    && mouse_y > b->y && mouse_y < b->y + upgrade->h
    && getpixel(upgrade, mouse_x - b->x, mouse_y - b->y) != makecol(255,0,255) )
    {
        b->highlight = TRUE;
        b->bip++;

        if(b->bip == 1)
          play_sample(FX_click, 255, 128, 1000, FALSE);

        //Se clicou
        if(mouse_b == 1)
        {
            mouse_b = 0;
            play_sample(FX_upgrade, 255, 128, 1000, FALSE);

            selecao->level++;

            if(selecao->ID == TORRE_NORMAL)
            {
                s->dinheiro -= TNPRECOUP;
                if(selecao->level == 2)
                {
                    selecao->dano = TNDANOLV2;
                    selecao->raio = TNRAIOLV2;
                }
                else if(selecao->level == 3)
                {
                   selecao->dano = TNDANOLV3;
                   selecao->raio = TNRAIOLV3;
                }
            }

            else if(selecao->ID == TORRE_SLOW)
            {
                s->dinheiro -= TSPRECOUP;
                if(selecao->level == 2)
                {
                    selecao->dano = TSSLOWLV2;
                    selecao->raio = TSRAIOLV2;
                }
                else if(selecao->level == 3)
                {
                   selecao->dano = TSSLOWLV3;
                   selecao->raio = TSRAIOLV3;
                }
            }

            else if(selecao->ID == TORRE_ANTITANQUE)
            {
                s->dinheiro -= TAPRECOUP;
                if(selecao->level == 2)
                {
                    selecao->dano = TADANOLV2;
                    selecao->raio = TARAIOLV2;
                }
                else if(selecao->level == 3)
                {
                   selecao->dano = TADANOLV3;
                   selecao->raio = TARAIOLV3;
                }
            }

            else if(selecao->ID == TORRE_VENENO)
            {
                s->dinheiro -= TVPRECOUP;
                if(selecao->level == 2)
                {
                    selecao->dano = TVDANOLV2;
                    selecao->raio = TVRAIOLV2;
                }
                else if(selecao->level == 3)
                {
                   selecao->dano = TVDANOLV3;
                   selecao->raio = TVRAIOLV3;
                }
            }
        }
    }
    else
    { b->highlight = FALSE; b->bip = 0; }
}

void Draw_Button_Upgrade(Button_Upgrade* b, BITMAP* buffer)
{
    if(b->ativado)
    {
        draw_sprite(buffer, upgrade, b->x, b->y);

        if(b->highlight)
         draw_sprite(buffer, upgrade_h, b->x, b->y);
    }
    else
      draw_sprite(buffer, upgrade_desativado, b->x, b->y);
}

void Destroy_Button_Upgrade(Button_Upgrade* b)
{
    free(b);
}
