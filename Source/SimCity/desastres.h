#ifndef DESASTRES_H_INCLUDED
#define DESASTRES_H_INCLUDED

#include "cidade.h"

bool espalhamentoLegal(Cidade* cidade, int tipo, int i, int j);
int TamanhoEspalhamento();
void espalhaDesastre(Cidade* cidade);
int geraCrime(float indice);
int geraDesastre(float indice);
void nasce_calamidade(int tipo, Cidade* cidade);

#endif
