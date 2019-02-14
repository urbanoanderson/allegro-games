#include "Vender.h"

Button_Venda* Create_Button_Venda(int x, int y)
{
    Button_Venda* b = (Button_Venda*) malloc(sizeof(Button_Venda));

    b->x = x;
    b->y = y;
    b->highlight = FALSE;
    b->ativado = FALSE;

    return b;
}

void Update_Button_Venda(Button_Venda* b, Stage* s)
{
    if(selecao != NULL)
    {
      b->ativado = TRUE;
    }
    else
      b->ativado = FALSE;

    //Se o botão está ativo
    if( b->ativado
    && mouse_x > b->x && mouse_x < b->x + vender->w
    && mouse_y > b->y && mouse_y < b->y + vender->h
    && getpixel(vender, mouse_x - b->x, mouse_y - b->y) != makecol(255,0,255) )
    {
        if(b->highlight == FALSE)
         play_sample(FX_click, 255, 128, 1000, FALSE);

        b->highlight = TRUE;

        //Se clicou
        if(mouse_b == 1)
        {
            b->ativado = FALSE;
            play_sample(FX_sell, 255, 128, 1000, FALSE);

            int i, j;
            for(i = 0; i < NUMTILESI; i++)
            {
                for(j = 0; j < NUMTILESJ; j++)
                {
                    if(selecao == mtx[i][j])
                    {

                       if(selecao->ID == TORRE_NORMAL)
                          s->dinheiro += TNPRECO/2 + ((selecao->level-1)*TNPRECOUP)/2;

                       else if(selecao->ID == TORRE_SLOW)
                       {
                          if(selecao->target != NULL)
                           selecao->target->slow = FALSE;

                          s->dinheiro += TSPRECO/2 + ((selecao->level-1)*TSPRECOUP)/2;
                       }

                       else if(selecao->ID == TORRE_ANTITANQUE)
                          s->dinheiro += TAPRECO/2 + ((selecao->level-1)*TAPRECOUP)/2;

                       else if(selecao->ID == TORRE_VENENO)
                          s->dinheiro += TVPRECO/2 + ((selecao->level-1)*TVPRECOUP)/2;

                      Destroy_Torre(mtx[i][j]);
                      mtx[i][j] = NULL;
                      selecao = NULL;
                      j = NUMTILESJ;
                      i = NUMTILESI;
                    }
                }
            }
        }
    }
    else
      b->highlight = FALSE;
}

void Draw_Button_Venda(Button_Venda* b, BITMAP* buffer)
{
    if(b->ativado)
    {
        draw_sprite(buffer, vender, b->x, b->y);

        if(b->highlight)
         draw_sprite(buffer, vender_h, b->x, b->y);
    }
    else
      draw_sprite(buffer, vender_desativado, b->x, b->y);
}

void Destroy_Button_Venda(Button_Venda* b)
{
    free(b);
}
