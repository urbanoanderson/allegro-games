#include "screeneffects.hpp"



void fade_in_black(BITMAP *bmp, int velocidade)
{
    BITMAP *buffer;

    if ((buffer = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        int a;
        if (velocidade <= 0) velocidade = 16;

        for (a = 0; a < 256; a+=velocidade)
        {
            clear(buffer);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(buffer, bmp, 0, 0);
            vsync();
            blit(buffer, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(buffer);
    }

    blit(bmp, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
}


void fade_out_black(int velocidade)
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
