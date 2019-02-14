#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

#include "init.h"
#include "button.h"
#include "cidade.h"
#include "func_allegro.h"
#include "desastres.h"

#define TILESIZE 25
#define X0 168
#define Y0 58
#define TEMPO_MENSAGEM 10000
#define PRECO_CASA 500.0
#define PRECO_RUA 200.0
#define PRECO_AGUA 50.0
#define PRECO_FLORESTA 100.0
#define PRECO_DESCONSTRUCAO 100.0
#define TEMPO_LEGENDA_PRECO 1000


enum MENSAGENS
{
    MSG_SEM_MENSAGEM,
    MSG_SAVE,
    MSG_DINHEIRO_INSUFICIENTE,
    MSG_DINHEIRO_INSUFICIENTE2,
    MSG_TERRENO_IMPROPRIO,
    MSG_NAO_CONSTRUIR_SOB_CALAMIDADE,
    MSG_CASA_CONSTRUIDA,
    MSG_RUA_CONSTRUIDA,
    MSG_FLORESTA_CONSTRUIDA,
    MSG_AGUA_CONSTRUIDA,
    MSG_DESCONSTRUCAO,
    MSG_NAO_DESCONSTRUIR_SOB_CALAMIDADE,
    MSG_TERRENO_LIVRE,
    MSG_BUY_POLICE,
    MSG_BUY_FIRETRUCK,
    MSG_BUY_AMBULANCE,
    MSG_FIRE,
    MSG_FLOOD,
    MSG_METEOR,
    MSG_MST,
    MSG_ALIEN,
    MSG_IP_TEST
};

void gamescreen();
void ExibirMensagem(int* mensagem, int* timer_msg);
bool msg_okcancel(BITMAP* fundo);
void tela_ajuda(BITMAP* fundo);
void tela_informacoes(int tipoInfo, BITMAP* fundo);
void tela_gameover(BITMAP* fundo, int tipoMensagem);
bool tela_aceitaCampanha_compraViatura(int tipo_campanha, BITMAP* fundo);

#endif // GAMESCREEN_H_INCLUDED
