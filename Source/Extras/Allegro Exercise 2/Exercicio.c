#include <allegro.h>

//Botão de fechar
volatile int exit_program;
void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

//Timer
volatile int milisegundos;
void GameTimeCounter() { milisegundos++; }
END_OF_FUNCTION(GameTimeCounter)

//Estrutura de Animação
typedef struct animation
{
     BITMAP* image;     //Imagem com os frames
     BITMAP* imageaux;  //Bitmap auxiliar pra dar flip

     int numframes;     //Número de imagens da animação
     int switchtime;    //Tempo de espera antes de trocar o frame
     int curframe;      //Frame atual
     int curtime;       //Tempo atual

     int frame_w;       //Largura de 1 frame
     int frame_h;       //Altura de 1 frame (é a da imagem)

     int loop;          //Se a animação funciona em loop
     int finish;        //Se a animação acabou
}Animation;

//Aloca e inicializa animação
Animation* Create_Animation(BITMAP* image, int numframes, int switchtime, int loop)
{
   Animation* a = (Animation*) malloc(sizeof(Animation));

   a->image = image;
   a->numframes = numframes;
   a->switchtime = switchtime;
   a->loop = loop;
   a->finish = FALSE;
   a->curframe = 0;
   a->curtime = milisegundos;
   a->frame_w = image->w / numframes;
   a->frame_h = image->h;
   a->imageaux = create_bitmap(a->frame_w, a->frame_h);

   return a;
}

//Atualiza animação
void Update_Animation(Animation* a)
{
   if(!a->finish)
   {
      //Hora de trocar o frame
      if(milisegundos - a->curtime >= a->switchtime)
      {
          a->curframe++;
          a->curtime = milisegundos;

          if(a->curframe >= a->numframes)
          {
             if(a->loop == TRUE)
              a->curframe = 0;
            else
              a->finish = TRUE;
          }
      }
   }
}

//Desenha animação de forma normal
void Draw_Animation(Animation* a, BITMAP* buffer, int pos_x, int pos_y)
{
   if(!a->finish)
   {
     masked_blit(a->image, buffer, a->curframe * a->frame_w, 0, pos_x, pos_y, a->frame_w, a->image->h);
   }
}

//Desenha animação virada horizontalmente
void Draw_Animation_H_Flip(Animation* a, BITMAP* buffer, int pos_x, int pos_y)
{
   if(!a->finish)
   {
     blit(a->image, a->imageaux, a->curframe * a->frame_w, 0, 0, 0, a->frame_w, a->image->h);
     draw_sprite_h_flip(buffer, a->imageaux, pos_x, pos_y);
   }
}

//Desaloca animação
void Destroy_Animation(Animation* a)
{
    destroy_bitmap(a->imageaux);
    free(a);
}

void init()
{
	allegro_init();
	install_timer();
	install_keyboard();
	install_mouse();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_window_title("Exercicio Timer");

	exit_program = FALSE;
    LOCK_FUNCTION(fecha_programa);
    LOCK_VARIABLE(exit_program);
    set_close_button_callback(fecha_programa);

	milisegundos = 0;
	LOCK_VARIABLE(milisegundos);
	LOCK_FUNCTION(GameTimeCounter);
	install_int_ex(GameTimeCounter, MSEC_TO_TIMER(1));
}

int main()
{
  init();

  ///BITMAPS
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
  BITMAP* andando = load_bitmap("Sprites/andando.bmp", NULL);
  BITMAP* cursor = load_bitmap("Sprites/mouse_cursor.bmp", NULL);

  ///VARIÁVEIS
  int pos_x = SCREEN_W/2 - 48;
  int pos_y = SCREEN_H/2 - andando->h/2;
  int dir = 1;
  int timer_movimento = milisegundos;
  Animation* anim_andando = Create_Animation(andando, 4, 175, TRUE);

  ///GAME LOOP
  while(!exit_program)
  {
     ///ENTRADA
     if(key[KEY_ESC])
      exit_program = TRUE;

     ///ATUALIZAÇÃO
     Update_Animation(anim_andando);

     //Ele vira se chegar no fim da tela
     if( (dir == -1 && pos_x < 0) || (dir == 1 && (pos_x+anim_andando->frame_w) > SCREEN_W) )
       dir = -dir;

     //Ele vira se clicar atras dele
     if( mouse_b & 1 && ((dir == -1 && mouse_x > pos_x+anim_andando->frame_w) || (dir == 1 && mouse_x < pos_x)) )
        dir = -dir;

     //Hora de se mover um pouco
     if(milisegundos - timer_movimento >= 15)
     {
         pos_x += dir;
         timer_movimento = milisegundos;
     }

     ///DESENHO

     //Desenha boneco dependendo de sua direção
     if(dir == 1)
        Draw_Animation(anim_andando, buffer, pos_x, pos_y);
     else
        Draw_Animation_H_Flip(anim_andando, buffer, pos_x, pos_y);

     //Desenha Cursor
     if(mouse_on_screen())
        draw_sprite(buffer, cursor, mouse_x, mouse_y);

     draw_sprite(screen, buffer, 0, 0);
     clear(buffer);
  }

  ///FINALIZAÇÂO
  Destroy_Animation(anim_andando);
  destroy_bitmap(buffer);
  destroy_bitmap(andando);
  destroy_bitmap(cursor);

  allegro_exit();

  return 0;
}
END_OF_MAIN();
