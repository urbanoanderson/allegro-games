#ifndef GAMESCREEN_HPP_INCLUDED
#define GAMESCREEN_HPP_INCLUDED

#include "shot.hpp"
#include "homing_shot.hpp"
#include "bomba.hpp"
#include "spaceship.hpp"
#include "shield.hpp"
#include "powerup.hpp"
#include "enemy.hpp"
#include "enemy_A.hpp"
#include "enemy_B.hpp"
#include "enemy_C.hpp"
#include "enemy_D.hpp"
#include "enemy_E.hpp"
#include "enemy_F.hpp"
#include "explosion.hpp"
#include "background.hpp"
#include "mediaplayer.hpp"
#include "gameover.hpp"
#include "pause.hpp"

int gera_id(int player_level, int porcentagem[5]);
void gamescreen(int flag);

#endif // GAMESCREEN_H_INCLUDED
