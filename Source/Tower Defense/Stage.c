#include "Stage.h"

Stage* Create_Stage()
{
   Stage* s = (Stage*) malloc(sizeof(Stage));
   s->turno_atual = 1;

   FILE* entrada = fopen("entrada.txt", "r");
   fscanf(entrada, "%d %d %d", &s->vidas, &s->turnos, &s->dinheiro);
   s->map = Create_Tilemap(entrada);

   //Pega programação de geração de unidades por turno
   s->turnos_sol = (int*) malloc(s->turnos * sizeof(int));
   s->turnos_solf = (int*) malloc(s->turnos * sizeof(int));
   s->turnos_moto = (int*) malloc(s->turnos * sizeof(int));
   s->turnos_tank = (int*) malloc(s->turnos * sizeof(int));

   int i;
   for(i = 0; i < s->turnos; i++)
     fscanf(entrada, "%d %d %d %d", &s->turnos_sol[i], &s->turnos_solf[i], &s->turnos_moto[i], &s->turnos_tank[i]);

   fclose(entrada);

   return s;
}

void Destroy_Stage(Stage* s)
{
    Destroy_Tilemap(s->map);
    free(s->turnos_sol);
    free(s->turnos_solf);
    free(s->turnos_moto);
    free(s->turnos_tank);
    free(s);
}
