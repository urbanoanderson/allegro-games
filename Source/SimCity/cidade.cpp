#include "cidade.h"

Cidade cidade;

///*****************************************************
///CREATE NEW CITY
///*****************************************************
int create_cidade(int tamanho, std::string nome)
{
    ///Testa se a cidade já existe
    std::string filename = "Arquivos/";
    filename += nome;
    filename += ".txt";
    FILE* f = fopen(filename.c_str(), "r");

    if(f) //Conseguiu encontrar o arquivo já existente
    {
       fclose(f);
       return 0;    //Erro
    }
    fclose(f);

    ///------------------------------------
    ///Inicializa atributos da cidade
    cidade.nome = nome;
    cidade.semanas = 50;
    cidade.dinheiro_em_caixa = 4000.00;
    cidade.imposto = 0.10;
    cidade.populacao = 70;
    //cidade.populacao_min = 10;
    cidade.num_ambu = 0;
    cidade.num_bomb = 0;
    cidade.num_poli = 0;
    cidade.preco_ambu = 300;
    cidade.preco_bomb = 400;
    cidade.preco_poli = 200;
    cidade.preco_ambu_mens = 120;
    cidade.preco_poli_mens = 80;
    cidade.preco_bomb_mens = 150;

    ///Inicializa as calamidades como nulas
    for(int i = 0; i < 19; i++)
    {
      for(int j = 0; j < 17; j++)
       cidade.calamidade[i][j] = SEM_DESASTRE;
    }

    ///----------------------------
    ///Escolhe mapa aleatoriamente
    std::string mapaEscolhido = "Arquivos/Mapas/";
    mapaEscolhido = mapaEscolhido + (char)(((rand() % mapNum) + 1) + '0');
    mapaEscolhido = mapaEscolhido + ".txt";

    FILE* mapFile = fopen(mapaEscolhido.c_str(), "r");

    for(int i = 0; i < 19; i++)
    {
       for(int j = 0; j < 17; j++)
        fscanf(mapFile, "%d", &cidade.terreno[i][j]);
    }

    //---------------------------------------------
    ///Acrescenta a borda no mapa (size SMALL/MEDIUM)
    int borda = 0; //Define quantos espaços ficarão desabilitados
    if(tamanho == SMALL)
     borda = 3;
    else if(tamanho==MEDIUM)
     borda = 2;

    if(borda > 0)
    {
        for (int i = 0; i < 19 && borda != 0; i++)
        {
            for(int j = 0; j < 17; j++)
            {
                if(i < borda || i > 18-borda || j < borda || j > 16-borda)
                 cidade.terreno[i][j] = NULO;
            }
        }
    }

    return 1;  //Tudo certo
}

///*****************************************************
///LOAD GAME from file
///*****************************************************
int load_cidade(std::string nome_arquivo)
{
    FILE* jogo_salvo = fopen(nome_arquivo.c_str(), "r");

    if(jogo_salvo == NULL)   //O arquivo de cidade não existe
     return NULL;

    ///Lê a matriz de terrenos da cidade
    for(int i = 0; i < 19; i++)
    {
       for(int j = 0; j < 17; j++)
        fscanf(jogo_salvo, "%d", &cidade.terreno[i][j]);
    }
    fgetc(jogo_salvo);

    ///Lê a matriz de Calamidades
    for(int i = 0; i < 19; i++)
    {
       for(int j = 0; j < 17; j++)
         fscanf(jogo_salvo, "%d", &cidade.calamidade[i][j]);
    }
    fgetc(jogo_salvo);

    ///Lê o nome da cidade
    char straux[100];
    fscanf(jogo_salvo, "%[^\n]", straux);
    cidade.nome = straux;
    ///Lê a populacao inicial
    fscanf(jogo_salvo, "%d", &cidade.populacao);
    ///Lê o dinheiro em caixa
    fscanf(jogo_salvo, "%f", &cidade.dinheiro_em_caixa);
    ///custo bombeiros
    fscanf(jogo_salvo, "%f %f", &cidade.preco_bomb, &cidade.preco_bomb_mens);
    ///Custo policia
    fscanf(jogo_salvo, "%f %f", &cidade.preco_poli, &cidade.preco_poli_mens);
    ///Custo ambulancia
    fscanf(jogo_salvo, "%f %f", &cidade.preco_ambu, &cidade.preco_ambu_mens);
    ///Lê o mínimo de habitantes
    fscanf(jogo_salvo, "%d", &cidade.populacao_min);
    ///Semanas restantes
    fscanf(jogo_salvo, "%d", &cidade.semanas);
    ///Índices de crimes e desastres
    fscanf(jogo_salvo, "%f %f", &cidade.indice_crime, &cidade.indice_desastre);
    ///IDH
    fscanf(jogo_salvo, "%f", &cidade.idh);
    ///Taxa de Impostos
    fscanf(jogo_salvo, "%f", &cidade.imposto);
    ///Taxa de Imigração e Emigração
    fscanf(jogo_salvo, "%f %f", &cidade.imigracao, &cidade.emigracao);
    ///Área verde, Área de Terra, Área Construida
    fscanf(jogo_salvo, "%f %f %f", &cidade.areaVerde, &cidade.areaTerra, &cidade.areaConstruida);
    ///Número de ambulancia, bombeiros e polícia
    fscanf(jogo_salvo, "%d %d %d", &cidade.num_ambu, &cidade.num_bomb, &cidade.num_poli);

    fclose(jogo_salvo);
    return 1;
}

///*****************************************************
///SAVE GAME to file
///*****************************************************
void salva_cidade()
{
    ///Abre o arquivo de cidade(se não houver cria um novo)
    std::string nome_arquivo = "Arquivos/" + cidade.nome + ".txt";

    FILE* arquivo_cidade = fopen(nome_arquivo.c_str(), "w");


    ///Grava a matriz de terrenos da cidade
    for (int i = 0; i < 19; i++)
    {
        for(int j = 0; j < 17; j++)
         fprintf(arquivo_cidade, "%d ", cidade.terreno[i][j]);

        fputc('\n', arquivo_cidade);
    }
    fputc('\n', arquivo_cidade);


    ///Grava a matriz de calamidades
    for (int i = 0; i < 19; i++)
    {
        int j;
        for(j = 0; j < 17; j++)
        {
            fprintf(arquivo_cidade, "%d", cidade.calamidade[i][j]);

            if(i != 18 || j != 16)
             fprintf(arquivo_cidade, " ");
        }

        if(i != 18 || j != 19)
         fputc('\n', arquivo_cidade);
    }

    ///Grava o nome da cidade
    fprintf(arquivo_cidade, "%s\n", cidade.nome.c_str());
    ///Grava a populacao inicial
    fprintf(arquivo_cidade, "%d\n", cidade.populacao);
    ///Grava o dinheiro em caixa
    fprintf(arquivo_cidade, "%.2f\n", cidade.dinheiro_em_caixa);
    ///Grava custo bombeiros
    fprintf(arquivo_cidade, "%.0f  %.0f\n", cidade.preco_bomb, cidade.preco_bomb_mens);
    ///Custo policia
    fprintf(arquivo_cidade, "%.0f  %.0f\n", cidade.preco_poli, cidade.preco_poli_mens);
    ///Custo ambulancia
    fprintf(arquivo_cidade, "%.0f  %.0f\n", cidade.preco_ambu, cidade.preco_ambu_mens);
    ///Grava o mínimo de habitantes
    fprintf(arquivo_cidade, "%d\n", cidade.populacao_min);
    ///Semanas restantes
    fprintf(arquivo_cidade, "%d\n", cidade.semanas);
    ///Índices de crimes e desastres
    fprintf(arquivo_cidade, "%.2f  %.2f\n", cidade.indice_crime, cidade.indice_desastre);
    ///IDH
    fprintf(arquivo_cidade, "%.1f\n", cidade.idh);
    ///Taxa de Impostos
    fprintf(arquivo_cidade, "%.2f\n", cidade.imposto);
    ///Taxa de Imigração e Emigração
    fprintf(arquivo_cidade, "%.2f  %.2f\n", cidade.imigracao, cidade.emigracao);
    ///Área verde, Área de Terra, Área Construida
    fprintf(arquivo_cidade, "%.2f  %.2f  %.2f\n", cidade.areaVerde, cidade.areaTerra, cidade.areaConstruida);
    ///Número de ambulancia, bombeiros e polícia
    fprintf(arquivo_cidade, "%d  %d  %d", cidade.num_ambu, cidade.num_bomb, cidade.num_poli);

    fclose(arquivo_cidade);
}


///*****************************************************
///DESENHAR CIDADE
///*****************************************************
void desenha_cidade(Cidade* cidade, BITMAP* buffer)
{
    int x = 172, y = 62;

    for(int i = 0; i < 19; i++)
    {
        x = 172;

        for(int j = 0; j < 17; j++)
        {
                //------------------------------
                //Desenha os Terrenos
                if (cidade->terreno[i][j] == TERRA){
                    cidade->qtdTerra++; draw_sprite(buffer, tile_terra, x, y);}
                else if (cidade->terreno[i][j] == AGUA){
                    cidade->qtdAgua++;masked_blit(anim_tile_agua, buffer, ((milisegundos/175) % 7) * 25, 0, x, y, 25, 25);}
                else if (cidade->terreno[i][j] == NULO)
                    draw_sprite(buffer, tile_inexplorado, x, y);
                else if (cidade->terreno[i][j] == CASA){
                    cidade->qtdResi++; draw_sprite(buffer, tile_casa, x, y);}
                else if (cidade->terreno[i][j] == FLORESTA){
                    cidade->qtdArvore++;draw_sprite(buffer, tile_floresta, x, y);}
                else if (cidade->terreno[i][j] == RUA){
                    cidade->qtdRua++;draw_sprite(buffer, tile_rua, x, y);}
                else if (cidade->terreno[i][j] >= CONSTRUCAO_CASA && cidade->terreno[i][j]<DESTRUICAO)
                    { draw_sprite(buffer, tile_construcao, x, y);}
                else if (cidade->terreno[i][j] ==  DESTRUICAO)
                    draw_sprite(buffer, tile_destruicao, x, y);

                //------------------------------
                //Desenha os Desastres

                set_trans_blender(255, 255, 255, 225);

                if (cidade->calamidade[i][j] == ASSALTO)
                    masked_blit(anim_desastre_assalto, buffer, ((milisegundos/150)%4)*25, 0, x, y, 25, 25);
                else if (cidade->calamidade[i][j] == HOMICIDIO)
                    draw_sprite(buffer, desastre_homicidio, x, y);
                else if (cidade->calamidade[i][j] == CHACINA)
                    masked_blit(anim_desastre_chacina, buffer, ((milisegundos/150)%3)*25, 0, x, y, 25, 25);
                else if (cidade->calamidade[i][j] == INCENDIO)
                    masked_blit(anim_desastre_incendio, buffer, ((milisegundos/175)%4)*25, 0, x, y, 25, 25);
                else if (cidade->calamidade[i][j] == ENCHENTE)
                    masked_blit(anim_desastre_enchente, buffer, ((milisegundos/150)%7)*25, 0, x, y, 25, 25);
                else if (cidade->calamidade[i][j] == METEORITOS)
                    masked_blit(anim_desastre_meteoro, buffer, ((milisegundos/150)%7)*25, 0, x, y, 25, 25);
                else if (cidade->calamidade[i][j] == MST)
                    draw_sprite(buffer, desastre_mst, x, y);
                else if (cidade->calamidade[i][j] == ALIEN)
                    masked_blit(anim_desastre_alien, buffer, ((milisegundos/150)%2)*25, 0, x, y, 25, 25);
                else if (cidade->calamidade[i][j] == PROVA_IP)
                    masked_blit(anim_desastre_provaIP, buffer, ((milisegundos/150)%4)*25, 0, x, y, 25, 25);

                x += 27;
        }

        y += 27;
    }
}

void TerminarConstruicao(Cidade* cidade)
{
    for(int i = 0; i < 19; i++)
    {
        for(int j = 0; j < 17; j++)
        {
            if(cidade->terreno[i][j] == CONSTRUCAO_CASA)
                cidade->terreno[i][j] = CASA;
            else if(cidade->terreno[i][j] == CONSTRUCAO_RUA)
                cidade->terreno[i][j] = RUA;
            else if(cidade->terreno[i][j] == CONSTRUCAO_AGUA)
                cidade->terreno[i][j] = AGUA;
            else if(cidade->terreno[i][j] == CONSTRUCAO_FLORESTA)
                cidade->terreno[i][j] = FLORESTA;
            else if(cidade->terreno[i][j] == DESTRUICAO)
                cidade->terreno[i][j] = TERRA;
        }
    }
}
