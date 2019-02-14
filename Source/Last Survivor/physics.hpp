#ifndef PHYSICS_HPP_INCLUDED
#define PHYSICS_HPP_INCLUDED

#include <allegro.h>
#include "animation.hpp"


double rads(double graus);
fixed GRAUS_ALLEGRO(double graus);

int max(int a, int b);
int min(int a, int b);
int pixel_perfect_colision(BITMAP* obj1, int x1, int y1, BITMAP* obj2, int x2, int y2);
int collision_between_animations(Animation* obj1, int x1, int y1, Animation* obj2, int x2, int y2);
int collision_against_animation(Animation* obj1, int x1, int y1, BITMAP* img2, int x2, int y2);
int bounding_box_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

#endif // PHYSICS_HPP_INCLUDED
