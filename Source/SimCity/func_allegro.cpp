#include "func_allegro.h"

///*****************************************************
///RECEBE TEXTO DO USUÁRIO
///*****************************************************
void PegaTexto(std::string* text)
{
    int tecla = readkey();
    int valor = tecla >> 8;
    char caracter = tecla & 0xff;

    if(valor == KEY_BACKSPACE)
    {
        if(text->length() > 0)
          *text = text->substr(0, text->length() - 1);
    }

    else if(valor == KEY_ENTER)
    {
        //rest(1);
    }

    else if(text->length() < 36)
    {
       *text += caracter;//letra;
    }
}


///*********************************************
///FADE OUT FROM BLACK
///*********************************************
void fade_out(int velocidade)
{
    BITMAP *origem, *buffer;

    if ((origem = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        if ((buffer = create_bitmap(SCREEN_W, SCREEN_H)))
        {
            int a;
            blit(screen, origem, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (velocidade <= 0) velocidade = 16;

            for (a = 255-velocidade; a > 0; a -= velocidade)
            {
                clear(buffer);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(buffer, origem, 0, 0);
                vsync();
                blit(buffer, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(buffer);
        }
        destroy_bitmap(origem);
    }

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));
}
