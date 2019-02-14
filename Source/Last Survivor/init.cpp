#include "init.hpp"

///**********************
///GLOBAIS
///**********************

///ALLEGRO
BITMAP* buffer;
volatile bool exit_program;
volatile int milisegundos;
volatile int player_time;
int timer_fps;

///USER OPTIONS
int vol_SFX;
int vol_BGM;
bool usevsync;
bool video_mode;
///***********************

void fecha_programa() { exit_program = true; }
END_OF_FUNCTION(fecha_programa)

void msec_counter() { milisegundos++; }
END_OF_FUNCTION(msec_counter)

void survival_counter() { player_time++; }
END_OF_FUNCTION(survival_counter)

int randnum(int max)
{
  int random;
  srand(time(NULL));
  for(int i = 0; i < 10; i++)
   random = rand() % max;

  return random;
}

int init()
{
  int find_settings_file = Load_user_configuration();

  if(!find_settings_file)
  {
     vol_SFX = 255;
     vol_BGM = 204;
     usevsync = true;
     video_mode = WINDOWED;
  }

  if(allegro_init() != 0)
  {
    allegro_message("Error. Unable to initialize allegro.");
    return NULL;
  }

  set_color_depth(32);
  if(set_gfx_mode(video_mode + 1, 800, 600, 0, 0) != 0)
  {
      allegro_message("Error. Unable to set graphic mode.");
      return NULL;
  }
  set_window_title("LAST SURVIVOR");

  if(!find_settings_file)
  {
    allegro_message("Error. Unable to find 'Settings.ini'. Setting default configuration values.");
    Save_user_configuration();
  }

  if(install_timer() != 0)
  {
    allegro_message("Error. Unable to install timer routines.");
    return NULL;
  }

  if(install_keyboard() != 0)
  {
    allegro_message("Error. Couldn't install keyboard handler.");
    return NULL;
  }

  if(install_joystick(JOY_TYPE_AUTODETECT) != 0)
  {
    allegro_message("Error. Couldn't install joystick handler.");
    return NULL;
  }

  if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
  {
      allegro_message("Error. Unable to initialize sound.");
      return NULL;
  }

  if(!pontuacoes.Load())
  {
    allegro_message("Unable to find 'highscores.dat'. Cleaning hiscore list.");
    pontuacoes.Save();
  }

  exit_program = false;
  LOCK_FUNCTION(fecha_programa);
  LOCK_VARIABLE(exit_program);
  set_close_button_callback(fecha_programa);

  milisegundos = 0;
  LOCK_FUNCTION(msec_counter);
  LOCK_VARIABLE(milisegundos);
  install_int_ex(msec_counter, MSEC_TO_TIMER(1));

  player_time = 0;
  LOCK_FUNCTION(survival_counter);
  LOCK_VARIABLE(player_time);

  set_volume(vol_SFX, vol_BGM);

  buffer = NULL;
  buffer = create_bitmap(SCREEN_W, SCREEN_H);
  if(!buffer)
  {
      allegro_message("Error. Couldn't create buffer.");
      return NULL;
  }

  c = create_content();
  if(!c)
   return NULL;

  srand(time(NULL));

   return 1;
}

void deinit()
{
  destroy_bitmap(buffer);
  delete c;
  clear_keybuf();
  allegro_exit();
}

int Load_user_configuration()
{
   FILE* config = fopen("Settings.ini", "r");

   if(!config)
   {
     return NULL;
   }

   else
   {
     char str[20];
     while(fscanf(config, "%[^\n]", str) != EOF)
     {
        if(strcmp(str, "[SFX VOLUME]") == 0)
          fscanf(config, "%d", &vol_SFX);
        else if(strcmp(str, "[BGM VOLUME]") == 0)
          fscanf(config, "%d", &vol_BGM);
        else if(strcmp(str, "[USE VSYNC]") == 0)
          fscanf(config, "%d", &usevsync);
        else if(strcmp(str, "[VIDEO MODE]") == 0)
          fscanf(config, "%d", &video_mode);
     }

     vol_SFX = (abs(vol_SFX) % 6) * 51;
     vol_BGM = (abs(vol_BGM) % 6) * 51;
     usevsync = usevsync%2;
     video_mode = video_mode%2;

     fclose(config);
     return 1;
   }
}

void Save_user_configuration()
{
   FILE* config = fopen("Settings.ini", "w");

   fprintf(config, "[SFX VOLUME]\n%d\n", vol_SFX/51);
   fprintf(config, "[BGM VOLUME]\n%d\n", vol_BGM/51);
   fprintf(config, "[USE VSYNC]\n%d\n", usevsync);
   fprintf(config, "[VIDEO MODE]\n%d\n", video_mode);

   fclose (config);
}
