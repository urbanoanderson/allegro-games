#ifndef MEDIAPLAYER_HPP_INCLUDED
#define MEDIAPLAYER_HPP_INCLUDED

#include "init.hpp"

typedef struct player
{
  int ja_tocadas[12];
  int qtd_tocadas;
  int cursong;
}Mediaplayer;

Mediaplayer* create_mediaplayer();
void mediaplayer_change_song(Mediaplayer* m);
void mediaplayer_update(void* m);
void destroy_media_player(Mediaplayer* m);

#endif // MEDIAPLAYER_H_INCLUDED
