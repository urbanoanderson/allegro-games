#include "mediaplayer.hpp"

///CREATE
Mediaplayer* create_mediaplayer()
{
   Mediaplayer* m = new Mediaplayer;

   int i;
   for(i = 0; i < 12; i++)
    m->ja_tocadas[i]  = FALSE;

   m->qtd_tocadas = 0;

   install_param_int_ex(mediaplayer_update, m, SECS_TO_TIMER(1));
   mediaplayer_change_song(m);

   return m;
}

///TROCAR MUSICA
void mediaplayer_change_song(Mediaplayer* m)
{
   //Se já tocou todas reseta
   if(m->qtd_tocadas == 12)
   {
     int i;
     for(i = 0; i < 12; i++)
     m->ja_tocadas[i]  = FALSE;
   }

   //Procura uma que não foi tocada
   do{
    m->cursong = randnum(12);
   }while(m->ja_tocadas[m->cursong] == TRUE);

   m->ja_tocadas[m->cursong] = TRUE;
   m->qtd_tocadas++;

  play_midi(c->soundtrack[m->cursong], FALSE);
}

///UPDATE
void mediaplayer_update(void* m)
{
  //Checa se a musica acabou
  if(midi_pos < 0)
   mediaplayer_change_song((Mediaplayer*)m);

}END_OF_FUNCTION();


///DESTROY
void destroy_media_player(Mediaplayer* m)
{
  remove_param_int(mediaplayer_update, m);
  stop_midi();
  delete m;
}
