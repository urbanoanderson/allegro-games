#include "init.h"

///GLOBAIS=========================
int screenstate;
bool exit_program;
bool desenhar;
float volBGM;
float volSFX;
bool debug_mode;

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_EVENT ev;
ALLEGRO_TIMER* timer_FPS;
ALLEGRO_BITMAP* icon;
ALLEGRO_KEYBOARD_STATE keystate;
ALLEGRO_JOYSTICK* joy1;
ALLEGRO_JOYSTICK_STATE joy1_state;
///================================

int width(ALLEGRO_BITMAP* img) { return al_get_bitmap_width(img); }
int height(ALLEGRO_BITMAP* img) { return al_get_bitmap_height(img); }

void init()
{
    al_init();
    //al_install_mouse();
    al_install_keyboard();
    al_install_joystick();
    al_install_audio();
    al_init_acodec_addon();
    al_init_ttf_addon();
    al_init_font_addon();
    al_init_image_addon();
    al_init_primitives_addon();

    //PHYSFS_init(NULL);
    //PHYSFS_addToSearchPath("data.zip", 1);
    //al_set_physfs_file_interface();

    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    display = al_create_display(SCREEN_W, SCREEN_H);
    event_queue = al_create_event_queue();
    timer_FPS = al_create_timer(1.0 / FPS);

    joy1 = al_get_joystick(0);

    //al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_joystick_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer_FPS));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	//al_hide_mouse_cursor(display);

	al_set_window_title(display, "Bomberman");
	icon = al_load_bitmap("Sprites/icon.png");
	al_set_display_icon(display, icon);

	exit_program = false;
	screenstate = MAINMENU;
	volSFX = 1.0;
	volBGM = 0.8;

    al_reserve_samples(15);
	LoadDefaultContent();

	srand(time(NULL));

	debug_mode = false;
}

void deinit()
{
    UnloadDefaultContent();
    al_destroy_timer(timer_FPS);
    al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(icon);
}

void fade(int r, int g, int b, float speed)
{
    int alpha = 0;
    float timer = al_get_time();

    while(alpha <= 50)
    {
        if(al_get_time() - timer >= speed)
        {
          alpha++;
          al_draw_filled_rectangle(0, 0, SCREEN_W, SCREEN_H, al_map_rgba(r, g, b, alpha));
          al_flip_display();
          timer = al_get_time();
        }
    }
}

int max(int a, int b)
{
    if(a > b)
     return a;
    else
     return b;
}

int min(int a, int b)
{
    if(a < b)
     return a;
    else
     return b;
}

int oposite_direction(int dir)
{
    if(dir == UP)
     return DOWN;
    else if(dir == DOWN)
     return UP;
    else if(dir == LEFT)
     return RIGHT;
    else
     return LEFT;
}
