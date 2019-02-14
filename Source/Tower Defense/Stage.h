#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED

#include "init.h"
#include "Tilemap.h"

typedef struct stage
{
    int vidas;
    int turnos;
    int dinheiro;
    Tilemap* map;

    int* turnos_sol;
    int* turnos_solf;
    int* turnos_moto;
    int* turnos_tank;

    int turno_atual;
}Stage;

Stage* Create_Stage();
void Destroy_Stage(Stage* s);

#endif // STAGE_H_INCLUDED
