#include "desastres.h"

///*************************************************************
///Verifica se o espalhamento de um desastre é permitido
///*************************************************************
bool espalhamentoLegal(Cidade* cidade, int tipo, int i, int j)
{
    bool permitido = true;

    if( i < 0 || i >= 19 || j < 0 || j >= 17
    || cidade->calamidade[i][j] != SEM_DESASTRE
    || cidade->terreno[i][j] == NULO
    || cidade->terreno[i][j] > TERRA )
        permitido = false;

    else
    {
        if( (tipo == INCENDIO || tipo == ENCHENTE) && cidade->terreno[i][j] == AGUA)
            permitido = false;
        else if (tipo == MST && cidade->terreno[i][j] != TERRA)
            permitido = false;
        else if (tipo == PROVA_IP && cidade->terreno[i][j] != CASA)
            permitido = false;
    }

    return permitido;
}

///**************************************************
///Decide Tamanho do espalhamento de um desastre
///**************************************************
int TamanhoEspalhamento()
{

    int chance = rand() % 100;

    int espalhamento = 0;                   //35% de chance de não espalhar

    if(chance >= 35 && chance < 60)         //25% de chance de espalhar 1
        espalhamento = 1;
    else if(chance >= 60 && chance < 70)    //10% de chance de espalhar 2
        espalhamento=2;
    else if(chance >= 70 && chance < 80)    //10% de chance de espalhar 3
        espalhamento = 3;
    else if(chance >= 80 && chance < 85)    //5% de chance de espalhar 4
        espalhamento = 4;
    else if(chance >= 85 && chance < 90)    //5% de chance de espalhar 5
        espalhamento = 5;
    else if(chance >= 90 && chance < 95)    //5% de chance de espalhar 6
        espalhamento = 6;
    else if(chance >= 95 && chance < 98)    //4% de chance de espalhar 7
        espalhamento = 7;
    else if(chance >= 99 && chance < 100)   //1% de chance de espalhamento máximo
        espalhamento = 8;

    return espalhamento;
}

///**************************************************************
///Espalha Desastres
///***************************************************************
void espalhaDesastre(Cidade* cidade)
{
    int espalhamento, m, n, direcao;

    //Direções
    enum {NOROESTE, NORTE, NORDESTE, OESTE, LESTE, SUDOESTE, SUL, SUDESTE};

    ///Percorre a matriz e gera desastres filhos
    for(int i = 0; i < 19; i++)
    {
        for(int j = 0; j < 17; j++)
        {
            //Se houver desastre no ponto
            if(cidade->calamidade[i][j] >= INCENDIO && cidade->calamidade[i][j] <= PROVA_IP)
            {
                //Determina quanto vai espalhar
                espalhamento = TamanhoEspalhamento();

                while(espalhamento > 0)
                {
                    direcao = rand() % 9;
                    if(direcao == NOROESTE)
                    {m=i-1;  n=j-1;}
                    else if(direcao == NORTE)
                    {m=i-1;  n=j;}
                    else if(direcao == NORDESTE)
                    {m=i-1;  n=j+1;}
                    else if(direcao == OESTE)
                    {m=i;     n=j-1;}
                    else if(direcao == LESTE)
                    {m=i;  n=j+1;}
                    else if(direcao == SUDOESTE)
                    {m=i+1;  n=j-1;}
                    else if(direcao == SUL)
                    {m=i+1;  n=j;}
                    else if(direcao == SUDESTE)
                    {m=i+1;  n=j+1;}

                    //Se o espalhamento for permitido
                    if(espalhamentoLegal(cidade, cidade->calamidade[i][j], m, n) == true)
                    {
                        cidade->calamidade[m][n] = cidade->calamidade[i][j] + 10;
                        espalhamento--;
                    }

                    //Se não houver pra onde espalhar
                    else if(   espalhamentoLegal(cidade, cidade->calamidade[i][j], i-1, j-1) == false
                            && espalhamentoLegal(cidade, cidade->calamidade[i][j], i-1, j  ) == false
                            && espalhamentoLegal(cidade, cidade->calamidade[i][j], i-1, j+1) == false
                            && espalhamentoLegal(cidade, cidade->calamidade[i][j], i, j-1  ) == false
                            && espalhamentoLegal(cidade, cidade->calamidade[i][j], i, j+1  ) == false
                            && espalhamentoLegal(cidade, cidade->calamidade[i][j], i+1, j-1) == false
                            && espalhamentoLegal(cidade, cidade->calamidade[i][j], i+1, j  ) == false
                            && espalhamentoLegal(cidade, cidade->calamidade[i][j], i+1, j+1) == false )
                        espalhamento = 0;
                }
            }
        }
    }

    ///Percorre a matriz e substitui valor dos filhos por valor normal
    for(int i = 0; i < 19; i++)
    {
        for(int j = 0; j < 17; j++)
        {
            if(cidade->calamidade[i][j] > 13)
                cidade->calamidade[i][j] -= 10;
        }
    }
}

///**************************************************
///Calcula se vai ocorrer um crime
///e se sim, determina qual
///**************************************************
int geraCrime(float indice)
{
    int resultado; //Define o tipo do crime

    int chance = rand() % 100;      //Calcula uma porcentagem aleatoriamente
    int probabilidade = indice*100; //Recebe a porcentagem eferente ao índice de criminalidade

    if (chance > probabilidade)     //Não ocorre nada
        resultado = 0;

    //Caso ocorra um crime, decide qual será
    else
    {
        chance = rand() % 100;

        if(chance >= 0 && chance < 10)          //10% de chance de ocorrer chacina
            resultado = 1;
        else if (chance >= 10 && chance <34)    //25% de chance de ocorrer homicídio
            resultado = 2;
        else                                    //65% de chance de ocorrer assalto
            resultado = 3;
    }

    return resultado;                           //Retorna o tipo do crime ocorrido
}

///**************************************************
///Calcula se vai ocorrer um desastre
///e se sim, determina qual
///**************************************************
int geraDesastre(float indice)
{
    int resultado;                      //Define o tipo do desastre

    int chance = rand() % 100;            //Calcula uma porcentagem aleatoriamente
    int probabilidade = indice * 100;     //Recebe a porcentagem eferente ao índice de desastres

    if(chance > probabilidade)
        resultado = 0;                  //Não ocorre nada

    //Caso ocorra um desastre, decide qual será
    else
    {
        chance = rand() % 1000;

        if (chance >= 0 && chance < 400)        //40% de chance de ocorrer incendio
            resultado = INCENDIO;
        else if (chance >= 400 && chance <750)  //35% de chance de ocorrer enchente
            resultado = ENCHENTE;
        else if (chance >= 750 && chance <900)  //15% de chance de cairem meteoros
            resultado = METEORITOS;
        else if (chance >= 900 && chance <980)  //8% de chance de ocorrer invasão do MST
            resultado = MST;
        else if (chance >= 980 && chance <991)  //1.1% de chance de ocorrer invasão Alienígena
            resultado = ALIEN;
        else                                    //0.9% de chance de ocorrer prova de IP
            resultado = PROVA_IP;
    }

    return resultado;
}

void nasce_calamidade(int tipo, Cidade* cidade)
{
   if(tipo != SEM_DESASTRE)
   {
        //Calcula uma posição aleatória na matriz
        int i = rand()%19;
        int j = rand()%17;

        bool ocorreu = false;
        int tentativas = 0;

        while(!ocorreu)
        {
            //Se não estiver acontecendo desastre nesse bloco
            if(cidade->calamidade[i][j] == SEM_DESASTRE)
            {
                if(tipo == ASSALTO
                && (cidade->terreno[i][j]==CASA || cidade->terreno[i][j]==FLORESTA || cidade->terreno[i][j]==RUA) )
                {
                    cidade->calamidade[i][j]=ASSALTO;
                    ocorreu = true;
                }

                else if(tipo == HOMICIDIO
                && (cidade->terreno[i][j] == CASA || cidade->terreno[i][j]==FLORESTA || cidade->terreno[i][j]==RUA || cidade->terreno[i][j]==TERRA))
                {
                    cidade->calamidade[i][j] = HOMICIDIO;
                    ocorreu = true;
                }

                else if(tipo == CHACINA
                && (cidade->terreno[i][j]==CASA || cidade->terreno[i][j]==FLORESTA || cidade->terreno[i][j]==RUA || cidade->terreno[i][j]==TERRA))
                {
                    cidade->calamidade[i][j] = CHACINA;
                    ocorreu = true;
                }

                else if(tipo == INCENDIO
                && (cidade->terreno[i][j]==CASA || cidade->terreno[i][j]==FLORESTA || cidade->terreno[i][j]==RUA || cidade->terreno[i][j]==TERRA))
                {
                    cidade->calamidade[i][j] = INCENDIO;
                    ocorreu = true;
                }

                else if(tipo == ENCHENTE
                && (cidade->terreno[i][j]==CASA || cidade->terreno[i][j]==FLORESTA || cidade->terreno[i][j]==RUA || cidade->terreno[i][j]==TERRA))
                {
                    cidade->calamidade[i][j] = ENCHENTE;
                    ocorreu = true;
                }

                else if(tipo == METEORITOS
                && (cidade->terreno[i][j]==CASA || cidade->terreno[i][j]==FLORESTA || cidade->terreno[i][j]==AGUA || cidade->terreno[i][j]==RUA || cidade->terreno[i][j]==TERRA))
                {
                    cidade->calamidade[i][j] = METEORITOS;
                    ocorreu = true;
                }

                else if(tipo == MST
                && cidade->terreno[i][j]==TERRA)
                {
                    cidade->calamidade[i][j] = MST;
                    ocorreu = true;
                }

                else if(tipo == ALIEN
                && (cidade->terreno[i][j]==CASA || cidade->terreno[i][j]==FLORESTA || cidade->terreno[i][j]==AGUA || cidade->terreno[i][j]==RUA || cidade->terreno[i][j]==TERRA))
                {
                    cidade->calamidade[i][j] = ALIEN;
                    ocorreu=TRUE;
                }

                else if(tipo == PROVA_IP
                && cidade->terreno[i][j]==CASA)
                {
                    cidade->calamidade[i][j] = PROVA_IP;
                    ocorreu=TRUE;
                }
            }

            //Continua a percorrer a matriz se não encontrar um alvo
            if(!ocorreu)
            {
                if(j < 17)
                    j++;
                else
                {
                    i++; j = 0;
                }

                if(i == 18)
                    i = 0;

                if(tentativas == 324)
                    ocorreu = true;

                tentativas++;
            }
        }
   }
}
