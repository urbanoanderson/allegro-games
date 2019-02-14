#include <time.h>
#include <stdlib.h>
#include <allegro.h>

//Enum das direções (melhora a legibilidade, e facilita quaisquer modificações)
enum{ UP, DOWN, LEFT, RIGHT };

//Testa colisão entre dois bitmaps. Retorna true ou false
int bounding_box_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if( (x1 > x2 + w2) || (y1 > y2 + h2) || (x2 > x1 + w1) || (y2 > y1 + h1) )
     return FALSE;
    else
     return TRUE;
}

//Gera posição aleatória para a bola mas que não esteja diretamente em contato com o boneco
void Reposicionar_Bola(int* bola_x, int* bola_y, int pos_x, int pos_y, BITMAP* bola, BITMAP* boneco)
{
    do
    {
      *bola_x = rand() % (SCREEN_W - bola->w);
      *bola_y = rand() % (SCREEN_H - bola->h);
    }while(bounding_box_collision(pos_x, pos_y, boneco->w, boneco->h, *bola_x, *bola_y, bola->w, bola->h));
}

//Variável global para controlar a saída do programa
volatile int exit_program;
void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

//Variável global temporizadora
volatile int milisegundos;
void msec_counter() { milisegundos++; }
END_OF_FUNCTION(msec_counter)

int main()
{
  allegro_init();
  install_timer();
  install_keyboard();
  install_sound(MIDI_AUTODETECT, DIGI_AUTODETECT, NULL);
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
  set_window_title("Exercicio Allegro");
  srand(time(NULL));

  exit_program = FALSE;
  LOCK_FUNCTION(fecha_programa);
  LOCK_VARIABLE(exit_program);
  set_close_button_callback(fecha_programa);

  milisegundos = 0;
  LOCK_FUNCTION(msec_counter);
  LOCK_VARIABLE(milisegundos);
  install_int_ex(msec_counter, MSEC_TO_TIMER(1));

  ///FONTES
  FONT* fonte = load_font("Fontes/fonte.pcx", NULL, NULL);

  ///SONS
  SAMPLE* efeito = load_sample("Sons/efeito.wav");
  MIDI* musica = load_midi("Sons/musica.mid");

  ///BITMAPS
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
  BITMAP* background = load_bitmap("Sprites/background.bmp", NULL);
  BITMAP* bola = load_bitmap("Sprites/pokebola.bmp", NULL);

  /*Vetor de ponteiros para bitmap do boneco.
  Em cada posição do vetor é carregada uma imagem
  dele virado em uma direção diferente. Para acessar eu
  uso o índice da direção correspondente. Ex: boneco[UP]*/
  BITMAP* boneco[4] =
  {
    load_bitmap("Sprites/cima.bmp", NULL),
    load_bitmap("Sprites/baixo.bmp", NULL),
    load_bitmap("Sprites/esquerda.bmp", NULL),
    load_bitmap("Sprites/direita.bmp", NULL)
  };

  //Posição e direção do boneco (começa no centro da tela e virado para baixo)
  int pos_x = SCREEN_W/2 - boneco[DOWN]->w/2;
  int pos_y = SCREEN_H/2 - boneco[DOWN]->h/2;
  int dir = DOWN;

  //Velocidade do movimento do boneco
  int speed = 6;

  //Posição da bola
  int bola_x, bola_y;
  Reposicionar_Bola(&bola_x, &bola_y, pos_x, pos_y, bola, boneco[dir]);

  //Score do jogador
  int score = 0;

  //Variável para controle de FPS
  int timer_fps = milisegundos - 10;

  //tocando a música do fundo
  play_midi(musica, TRUE); 

  ///GAME LOOP
  while(!exit_program)
  {
     ///CONTROLE DE FPS (100 FPS)
     if(abs(milisegundos - timer_fps) >= 10)
     {
        ///----------
        ///INPUT
        if(key[KEY_ESC])
          fecha_programa();

        //Alt + Enter  alterna entre windowed e fullscreen
        if(key[KEY_ENTER] && (key_shifts & KB_ALT_FLAG))
        {
            if(is_windowed_mode())
              set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCREEN_W, SCREEN_H, 0, 0);
            else
              set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);
        }

        //Movimentação
        if(key[KEY_UP])
        {
            dir = UP;
            pos_y -= speed;

            //Checagem de limites da tela
            if(pos_y < -boneco[dir]->h)
              pos_y = SCREEN_H;
        }

        else if(key[KEY_DOWN])
        {
            dir = DOWN;
            pos_y += speed;

            if(pos_y > SCREEN_H)
             pos_y = -boneco[dir]->h;
        }

        else if(key[KEY_LEFT])
        {
            dir = LEFT;
            pos_x -= speed;

            if(pos_x < -boneco[dir]->w)
             pos_x = SCREEN_W;
        }

        else if(key[KEY_RIGHT])
        {
            dir = RIGHT;
            pos_x += speed;

            if(pos_x > SCREEN_W)
             pos_x = -boneco[dir]->w;
        }


        ///----------
        ///UPDATE

        //testa a colisão do boneco com a bola
        if(bounding_box_collision(pos_x, pos_y, boneco[dir]->w, boneco[dir]->h, bola_x, bola_y, bola->w, bola->h) == TRUE)
        {
            score++;     //Jogador ganha 1 ponto
            play_sample(efeito, 255, 128, 1000, FALSE); //toca efeito sonoro

            //Gera uma nova posição da bola (em que não haja colisão de imediato com o boneco)
            Reposicionar_Bola(&bola_x, &bola_y, pos_x, pos_y, bola, boneco[dir]);
        }


        ///----------
        ///DRAW
        draw_sprite(buffer, background, 0, 0);                                        	//Desenha background
        draw_sprite(buffer, boneco[dir], pos_x, pos_y);                               	//Desenha boneco
        draw_sprite(buffer, bola, bola_x, bola_y);                                    	//Desenha bola
        textprintf_ex(buffer, fonte, 10, 10, makecol(0,0,0), -1, "SCORE: %d", score); 	//Desenha texto do score
        draw_sprite(screen, buffer, 0, 0); 												//Desenha o buffer na screen
        clear(buffer);                     												//Limpa o buffer
        vsync(); //Só pra melhorar a imagem, não é realmente necessário. A sincronização vertical diminui a tremulação entre frames

        timer_fps = milisegundos;
     }
	 
  }//Fim do gameloop
  
  //Para a música
  stop_midi();

  ///FINALIZAÇÂO

  //Destroy as mídias, liberando a memória
  //OBS: Recomendo destruir logo as midias utilizadas quando você for carregá-las para não esquecer
  destroy_bitmap(buffer);
  destroy_bitmap(background);
  destroy_bitmap(bola);
  destroy_font(fonte);
  destroy_sample(efeito);
  destroy_midi(musica);
  destroy_bitmap(boneco[0]);
  destroy_bitmap(boneco[1]);
  destroy_bitmap(boneco[2]);
  destroy_bitmap(boneco[3]);

  return 0;
}
END_OF_MAIN();
