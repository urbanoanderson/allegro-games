#include "init.h"

///GLOBAIS=========================
int screenstate;
bool exit_program;
bool desenhar;
float volBGM;
float volSFX;
bool DEBUG;

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
    al_install_keyboard();
    al_install_joystick();
    al_install_audio();
    al_init_acodec_addon();
    al_init_ttf_addon();
    al_init_font_addon();
    al_init_image_addon();
    al_init_primitives_addon();

    //PHYSFS_init(NULL);
    //PHYSFS_addToSearchPath("data.dat", 1);
    //al_set_physfs_file_interface();

    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    display = al_create_display(SCREEN_W, SCREEN_H);
    event_queue = al_create_event_queue();
    timer_FPS = al_create_timer(1.0 / FPS);

    joy1 = al_get_joystick(0);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_joystick_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer_FPS));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_set_window_title(display, "Flappy Bird");
	icon = al_load_bitmap("Sprites/icon.png");
	al_set_display_icon(display, icon);

	exit_program = false;
	screenstate = GAMESCREEN;
	volSFX = 1.0;
	volBGM = 1.0;

    al_reserve_samples(15);
	LoadDefaultContent();

	srand(time(NULL));

	DEBUG = false;
}

void deinit()
{
    UnloadDefaultContent();
    al_destroy_timer(timer_FPS);
    al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(icon);
}

float regVolume(float value)
{
    if(value < 0.0)
     return 0.0;
    else
     return value;
}
