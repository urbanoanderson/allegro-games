#ifndef CIDADE_H_INCLUDED
#define CIDADE_H_INCLUDED

#include "init.h"

typedef struct cidade
{
    std::string nome;
    int semanas;
    int populacao;
    int populacao_min;

    int terreno[19][17];    //Matriz de impressão de terrenos
    int calamidade[19][17]; //Matriz de impressão de desastres

    float imposto;
    float dinheiro_em_caixa;
    float idh;
    float indice_crime;
    float indice_desastre;
    float emigracao;
    float imigracao;

    float areaVerde;
    float areaTerra;
    float areaConstruida;

    int qtdResi;
    int qtdAgua;
    int qtdArvore;
    int qtdRua;
    int qtdTerra;
    int qtdNulo;

    float preco_bomb;
    float preco_bomb_mens;
    float preco_poli;
    float preco_poli_mens;
    float preco_ambu;
    float preco_ambu_mens;

    int num_ambu;
    int num_poli;
    int num_bomb;
}Cidade;

extern Cidade cidade;

int create_cidade(int tamanho, std::string nome);
int load_cidade(std::string nome_arquivo);
void salva_cidade();
void desenha_cidade(Cidade* cidade, BITMAP* buffer);
void TerminarConstruicao(Cidade* cidade);


#endif
