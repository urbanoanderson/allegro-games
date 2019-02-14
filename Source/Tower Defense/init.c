#include "init.h"

void* malloc2 (size_t size)
{
  contador++;
  return malloc(size);
}

void free2 (void* ptr)
{
 contador--;
 free(ptr);
}

///TIMER
void GameTimeCounter() { gametime++; }
END_OF_FUNCTION(GameTimeCounter)

///EXIT CALLBACK
void Exit_Game() { exit_program = TRUE; }
END_OF_FUNCTION(Exit_Game)

void init()
{
   allegro_init();
   install_timer();
   install_keyboard();
   install_mouse();
   set_color_depth(32);
   set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 728, 0, 0);
   install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
   set_window_title("Tower Defense");

   gametime = 0;
   LOCK_FUNCTION(GameTimeCounter);
   LOCK_VARIABLE(gametime);
   install_int_ex(GameTimeCounter, MSEC_TO_TIMER(1));

   exit_program = FALSE;
   LOCK_FUNCTION(Exit_Game);
   LOCK_VARIABLE(exit_program);
   set_close_button_callback(Exit_Game);

   srand(time(NULL));
   set_trans_blender(255,255,255,128);

   screen_state = MAINMENU;

   Load_Content();
}

void deinit()
{
    Unload_Content();
    clear_keybuf();
    allegro_exit();
}

float Distancia(float x1, float y1, float x2, float y2)
{
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

double graus(double rads)
{
    return rads * (180.0 / 3.14159265);
}

fixed GRAUS_ALLEGRO(float graus)
{
   return ftofix(graus * (256.0 / 360.0));
}

double rads(double graus)
{
   return (graus * 3.14159265) / 180.0;
}


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
