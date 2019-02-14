#include "init.h"

///*******************
///VARIÁVEIS GLOBAIS
volatile bool exit_program;
int screenstate; //Controla as telas do jogo
int screenmode;              //Controla a Janela (WINDOWED ou FULLSCREEN)
int volume;                 //Variável global dos sons
int mapNum;                 //Quantos mapas padrão existem
volatile int milisegundos;
bool is_playing;
bool erro_newload;
BITMAP* buffer;
int prev_mouse_b;


///**************************************************
///TIMER DE MILISEGUNDOS
void contaMilisegundos() { milisegundos++; }
END_OF_FUNCTION(contaMilisegundos);

///**************************************************
///EXIT CALLBACK
void Exit_Game() { exit_program = true; }
END_OF_FUNCTION(Exit_Game)

///***************************************************
///MOUSE
bool Clicou(int b)
{
    return ( (mouse_b & b) && !(prev_mouse_b & b) );
}

void Receive_Mouse_Input()
{
    prev_mouse_b = mouse_b;
    poll_mouse();
}

///**************************************************
///Inicia o Allegro
///**************************************************
void init()
{
    Load_user_configuration();

    allegro_init();
    install_timer();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    set_color_depth(32);
    srand(time(NULL));

    if(screenmode == WINDOWED)
     set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    else
     set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 800, 600, 0, 0);

    set_window_title("Sim City - Projeto IP");

    exit_program = false;
    LOCK_FUNCTION(Exit_Game);
    LOCK_VARIABLE(exit_program);
    set_close_button_callback(Exit_Game);

    milisegundos = 0;
    LOCK_FUNCTION(contaMilisegundos);
    LOCK_VARIABLE(milisegundos);
    install_int_ex(contaMilisegundos, MSEC_TO_TIMER(1));

    screenstate = MAINMENU;
    is_playing = false;

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
}

void deinit()
{
    destroy_bitmap(buffer);
    clear_keybuf();
    allegro_exit();
}

///**************************************************
///Carrega Arquivo de Configurações do Usuário
///**************************************************
void Load_user_configuration()
{
    FILE* config = fopen("Arquivos/config.txt", "r");
    fscanf(config, "%d", &volume);
    fscanf(config, "%d", &screenmode);
    fscanf(config, "%d", &mapNum);
    fclose(config);
}

///**************************************************
///Salva configurações do Usuário em arquivo
///**************************************************
void Save_user_configuration()
{
    FILE* config = fopen("Arquivos/config.txt", "w");
    fprintf(config, "%d\n", volume);
    fprintf(config, "%d\n", screenmode);
    fprintf(config, "%d", mapNum);
    fclose(config);
}


