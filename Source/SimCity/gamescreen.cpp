#include "gamescreen.h"

void gamescreen()
{
    fade_out(20);

    LoadGameContent();

    //BOTÕES
    Button* b_backarrow = create_button(backArrow, backArrowON, click, 10, 5, 8, 3);
    Button* b_save = create_button(save, saveON, click, 60, 5, 55, 1);
    Button* b_info = create_button(info, infoON, click, 100, 7, 98, 5);
    Button* b_help = create_button(help, helpON, click, 140, 6, 136, 0);
    Button* b_campanhaAmbulancia = create_button(campaign_ambulance, buttonHighlight, click, 655, 145, 655, 145);
    Button* b_campanhaPolicia = create_button(campaign_policemen, buttonHighlight, click, 720, 145, 720, 145);
    Button* b_campanhaBombeiros = create_button(campaign_fireman, buttonHighlight, click, 655, 200, 655, 200);
    Button* b_campanhaInvestimento = create_button(campaign_invest, buttonHighlight, click, 720, 200, 720, 200);
    Button* b_campanhaPromessa = create_button(campaign_promisse, buttonHighlight, click, 655, 255, 655, 255);
    Button* b_campanhaPropaganda = create_button(campaign_advertisement, buttonHighlight, click, 720, 255, 720, 255);
    Button* b_campanhaTaxas = create_button(campaign_taxes, buttonHighlight, click, 655, 310, 655, 310);
    Button* b_buildHouse = create_button(build_house, buttonHighlight, click, 25, 110, 25, 110);
    Button* b_buildWater = create_button(build_water, buttonHighlight, click, 25, 165, 25, 165);
    Button* b_buildForest = create_button(build_forest, buttonHighlight, click, 90, 110, 90, 110);
    Button* b_buildStreet = create_button(build_street, buttonHighlight, click, 90, 165,  90, 165);
    Button* b_buyAmbulance = create_button(buy_ambulance, buttonHighlight, click, 25, 345,  25, 345);
    Button* b_buyFiretruck = create_button(buy_firetruck, buttonHighlight, click, 90, 345,  90, 345);
    Button* b_buyPoliceCar = create_button(buy_policecar, buttonHighlight, click, 25, 400, 25, 400);
    Button* b_vehicleInfo = create_button(vehicle_info, vehicle_infoON, click, 102, 412, 102, 412);
    Button* b_skipWeek = create_button(skipWeek, skipWeekON, click, 25, 460, 25, 460);
    Button* b_deconstruct = create_button(botaoDestrutor, botaoDestrutorON, click, 40, 250, 40, 250);

    //Variáveis
    BITMAP* fundo = create_bitmap(SCREEN_W, SCREEN_H);
    bool exit_screen = false;
    bool draw_selecao = false;
    int selecao_x;
    int selecao_y;
    int modo_construcao = NAO_CONSTRUIR;
    int mensagem = MSG_SEM_MENSAGEM;
    int timer_msg = milisegundos;

    play_sample(gameSong1, volume, 128, 1000, TRUE);

    //GAMELOOP
    while (!exit_screen && !exit_program)
    {
        ///--------------
        ///INPUT
        Receive_Keyboard_Input();
        Receive_Mouse_Input();

        //Input dos Botões
        button_input(b_backarrow);
        button_input(b_save);
        button_input(b_info);
        button_input(b_help);
        button_input(b_campanhaAmbulancia);
        button_input(b_campanhaPolicia);
        button_input(b_campanhaBombeiros);
        button_input(b_campanhaInvestimento);
        button_input(b_campanhaPromessa);
        button_input(b_campanhaPropaganda);
        button_input(b_campanhaTaxas);
        button_input(b_buildHouse);
        button_input(b_buildWater);
        button_input(b_buildForest);
        button_input(b_buildStreet);
        button_input(b_buyAmbulance);
        button_input(b_buyFiretruck);
        button_input(b_buyPoliceCar);
        button_input(b_vehicleInfo);
        button_input(b_skipWeek);
        button_input(b_deconstruct);

        ///--------------
        ///UPDATE

        //Botão de voltar
        if(b_backarrow->ativado || Pressed(KEY_ESC))
        {
            exit_screen = msg_okcancel(fundo);
            modo_construcao = NAO_CONSTRUIR;
            b_backarrow->ativado = false;
        }

        //Botão de salvar
        if(b_save->ativado || Pressed(KEY_F2))
        {
            salva_cidade();
            mensagem = MSG_SAVE;
            modo_construcao = NAO_CONSTRUIR;
            b_save->ativado = false;
        }

        //Botão de ajuda
        else if(b_help->ativado || Pressed(KEY_F1))
        {
            tela_ajuda(fundo);
            modo_construcao = NAO_CONSTRUIR;
            b_help->ativado = false;
        }

        //Botão de Informações da barra superior
        else if(b_info->ativado || Pressed(KEY_F3))
        {
            tela_informacoes(1, fundo);
            modo_construcao = NAO_CONSTRUIR;
            b_info->ativado = false;
        }

        //Botão de Informações das viaturas
        else if(b_vehicleInfo->ativado || Pressed(KEY_F4))
        {
            tela_informacoes(2, fundo);
            modo_construcao = NAO_CONSTRUIR;
            b_vehicleInfo->ativado = false;
        }

        //Botão SKIP WEEK
        else if(b_skipWeek->ativado || Pressed(KEY_F12))
        {
            modo_construcao = NAO_CONSTRUIR;

            fade_out(15);

            //Atualiza Taxas
            //atualizar_taxas(&cidade);

            //Recolhe os impostos
            cidade.dinheiro_em_caixa += cidade.populacao * cidade.imposto * 100;

            //Atualiza número de semans restantes
            cidade.semanas--;

            //Termina as construções/demolições
            TerminarConstruicao(&cidade);

            //Executa ações referentes a de desastres
            espalhaDesastre(&cidade);
            int tipoDesastre = geraDesastre(cidade.indice_desastre);

            if(tipoDesastre == INCENDIO)
                mensagem = MSG_FIRE;
            else if(tipoDesastre == ENCHENTE)
                mensagem = MSG_FLOOD;
            else if(tipoDesastre == METEORITOS)
                mensagem = MSG_METEOR;
            else if(tipoDesastre == MST)
                mensagem = MSG_MST;
            else if(tipoDesastre == ALIEN)
                mensagem = MSG_ALIEN;
            else if(tipoDesastre == PROVA_IP)
                mensagem = MSG_IP_TEST;

            nasce_calamidade(tipoDesastre, &cidade);//Gera um novo desastre
            nasce_calamidade(geraCrime(cidade.indice_crime), &cidade);//Gera um novo crime

            b_skipWeek->ativado = false;
        }

        //-----------------------
        //COMPRA DE VIATURAS
        //-----------------------

        //Botão comprar ambulancia
        else if(b_buyAmbulance->ativado || Pressed(KEY_M))
        {
            bool comprou = tela_aceitaCampanha_compraViatura(8, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= cidade.preco_ambu;
               play_sample(ambulanceSample, volume, 128, 1000, FALSE);
               mensagem = MSG_BUY_AMBULANCE;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_buyAmbulance->ativado = false;
        }

        //Botão de comprar policia
        else if(b_buyPoliceCar->ativado || Pressed(KEY_P))
        {
            bool comprou = tela_aceitaCampanha_compraViatura(9, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= cidade.preco_poli;
               play_sample(policeradioSample, volume, 128, 1000, FALSE);
               mensagem = MSG_BUY_POLICE;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_buyPoliceCar->ativado = false;
        }

        //Botão de comprar carro de bombeiros
        else if(b_buyFiretruck->ativado || Pressed(KEY_F))
        {
            bool comprou = tela_aceitaCampanha_compraViatura(10, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= cidade.preco_bomb;
               play_sample(firetruckSample, volume, 128, 1000, FALSE);
               mensagem = MSG_BUY_FIRETRUCK;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_buyFiretruck->ativado = false;
        }


        //-----------------------
        //CAMPANHAS
        //-----------------------

        //Botão de Campanha Ambulancia
        else if(b_campanhaAmbulancia->ativado)
        {
            bool comprou = tela_aceitaCampanha_compraViatura(1, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= 1850.0;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_campanhaAmbulancia->ativado = false;
        }

        //Botão de Campanha Policia
        else if(b_campanhaPolicia->ativado)
        {
            bool comprou = tela_aceitaCampanha_compraViatura(2, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= 1000.0;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_campanhaPolicia->ativado = false;
        }

        //Botão de Campanha Bombeiros
        else if(b_campanhaBombeiros->ativado)
        {
            bool comprou = tela_aceitaCampanha_compraViatura(3, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= 1500.0;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_campanhaBombeiros->ativado = false;
        }

        //Botão de Campanha Investimento
        else if(b_campanhaInvestimento->ativado)
        {
            bool comprou = tela_aceitaCampanha_compraViatura(4, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= 3000.0;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_campanhaInvestimento->ativado = false;
        }

        //Botão de Campanha Impostos
        else if(b_campanhaTaxas->ativado)
        {
            bool comprou = tela_aceitaCampanha_compraViatura(5, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= 200.0;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_campanhaTaxas->ativado = false;
        }

        //Botão de Campanha Promessas
        else if(b_campanhaPromessa->ativado)
        {
            bool comprou = tela_aceitaCampanha_compraViatura(6, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= 1000.0;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_campanhaPromessa->ativado = false;
        }

        //Botão de Campanha Propaganda
        else if(b_campanhaPropaganda->ativado)
        {
            bool comprou = tela_aceitaCampanha_compraViatura(7, fundo);

            if(comprou)
            {
               cidade.dinheiro_em_caixa -= 4000.0;
            }

            modo_construcao = NAO_CONSTRUIR;
            b_campanhaPropaganda->ativado = false;
        }

        //-----------------------
        //BOTÕES De CONSTRUÇÂO/DESCONSTRUÇÃO
        //-----------------------

        //Botão de construção de casa
        else if(b_buildHouse->ativado || Pressed(KEY_H))
        {
            if(modo_construcao == CONSTRUIR_CASA)
                modo_construcao = NAO_CONSTRUIR;
            else
                modo_construcao = CONSTRUIR_CASA;

            b_buildHouse->ativado = false;
        }

        //Botão de construção de rua
        else if(b_buildStreet->ativado || Pressed(KEY_R))
        {
            if(modo_construcao == CONSTRUIR_RUA)
                modo_construcao = NAO_CONSTRUIR;
            else
                modo_construcao = CONSTRUIR_RUA;

            b_buildStreet->ativado = false;
        }

        //Botão de construção de água
        else if(b_buildWater->ativado || Pressed(KEY_A))
        {
            if(modo_construcao == CONSTRUIR_AGUA)
                modo_construcao = NAO_CONSTRUIR;
            else
                modo_construcao = CONSTRUIR_AGUA;

            b_buildWater->ativado = false;
        }

        //Botão de construção de floresta
        else if(b_buildForest->ativado || Pressed(KEY_G))
        {
            if(modo_construcao == CONSTRUIR_FLORESTA)
                modo_construcao = NAO_CONSTRUIR;
            else
                modo_construcao = CONSTRUIR_FLORESTA;

            b_buildForest->ativado = false;
        }

        //Botão de demolição
        else if(b_deconstruct->ativado || Pressed(KEY_D))
        {
            if(modo_construcao == DESCONSTRUIR)
                modo_construcao = NAO_CONSTRUIR;
            else
                modo_construcao = DESCONSTRUIR;

            b_deconstruct->ativado = false;
        }

        //-----------------------
        //MODO DE CONSTRUÇÃO
        //-----------------------
        if(modo_construcao != NAO_CONSTRUIR)
        {
            if( Clicou(1)
            && (mouse_x >= (X0+4)  && mouse_x <= (X0+4)+(matriz->w-8))
            && (mouse_y >= (Y0+4)  && mouse_y <= (Y0+4)+(matriz->h-8)) )
            {
                //mouse_b = 0;
                int tile_j = (mouse_x - (X0+4))/(TILESIZE+2);
                int tile_i = (mouse_y - (Y0+4))/(TILESIZE+2);

                //CASA
                if(modo_construcao == CONSTRUIR_CASA)
                {
                    if(cidade.dinheiro_em_caixa < PRECO_CASA){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_DINHEIRO_INSUFICIENTE;
                    }
                    else if(cidade.terreno[tile_i][tile_j] != TERRA){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_TERRENO_IMPROPRIO;
                    }
                    else if(cidade.calamidade[tile_i][tile_j] != SEM_DESASTRE){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_NAO_CONSTRUIR_SOB_CALAMIDADE;
                    }
                    else
                    {
                        cidade.dinheiro_em_caixa -= PRECO_CASA;
                        cidade.terreno[tile_i][tile_j] = CONSTRUCAO_CASA;
                        modo_construcao = NAO_CONSTRUIR;
                        play_sample(registradora, volume, 128, 1000, FALSE);
                        mensagem = MSG_CASA_CONSTRUIDA;
                    }
                    timer_msg = milisegundos;
                }

                //RUA
                else if(modo_construcao == CONSTRUIR_RUA)
                {
                    if(cidade.dinheiro_em_caixa < PRECO_RUA){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_DINHEIRO_INSUFICIENTE;
                    }
                    else if(cidade.terreno[tile_i][tile_j] != TERRA){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_TERRENO_IMPROPRIO;
                    }
                    else if(cidade.calamidade[tile_i][tile_j] != SEM_DESASTRE){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_NAO_CONSTRUIR_SOB_CALAMIDADE;
                    }
                    else
                    {
                        cidade.dinheiro_em_caixa -= PRECO_RUA;
                        cidade.terreno[tile_i][tile_j] = CONSTRUCAO_RUA;
                        modo_construcao = NAO_CONSTRUIR;
                        play_sample(registradora, volume, 128, 1000, FALSE);
                        mensagem = MSG_RUA_CONSTRUIDA;
                    }
                    timer_msg = milisegundos;
                }

                //ÁGUA
                else if(modo_construcao == CONSTRUIR_AGUA)
                {
                    if(cidade.dinheiro_em_caixa < PRECO_AGUA){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_DINHEIRO_INSUFICIENTE;
                    }
                    else if(cidade.terreno[tile_i][tile_j] != TERRA){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_TERRENO_IMPROPRIO;
                    }
                    else if(cidade.calamidade[tile_i][tile_j] != SEM_DESASTRE){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_NAO_CONSTRUIR_SOB_CALAMIDADE;
                    }
                    else
                    {
                        cidade.dinheiro_em_caixa -= PRECO_AGUA;
                        cidade.terreno[tile_i][tile_j] = CONSTRUCAO_AGUA;
                        modo_construcao = NAO_CONSTRUIR;
                        play_sample(registradora, volume, 128, 1000, FALSE);
                        mensagem = MSG_AGUA_CONSTRUIDA;
                    }
                    timer_msg = milisegundos;
                }

                //FLORESTA
                else if(modo_construcao == CONSTRUIR_FLORESTA)
                {
                    if(cidade.dinheiro_em_caixa < PRECO_FLORESTA){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_DINHEIRO_INSUFICIENTE;
                    }
                    else if(cidade.terreno[tile_i][tile_j] != TERRA){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_TERRENO_IMPROPRIO;
                    }
                    else if(cidade.calamidade[tile_i][tile_j] != SEM_DESASTRE){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_NAO_CONSTRUIR_SOB_CALAMIDADE;
                    }
                    else
                    {
                        cidade.dinheiro_em_caixa -= PRECO_FLORESTA;
                        cidade.terreno[tile_i][tile_j] = CONSTRUCAO_FLORESTA;
                        modo_construcao = NAO_CONSTRUIR;
                        play_sample(registradora, volume, 128, 1000, FALSE);
                        mensagem = MSG_FLORESTA_CONSTRUIDA;
                    }
                    timer_msg = milisegundos;
                }

                //DEMOLIR
                else if(modo_construcao == DESCONSTRUIR)
                {
                    if(cidade.dinheiro_em_caixa < PRECO_DESCONSTRUCAO){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_DINHEIRO_INSUFICIENTE2;
                    }
                    else if(cidade.terreno[tile_i][tile_j] == TERRA){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_TERRENO_LIVRE;
                    }
                    else if(cidade.calamidade[tile_i][tile_j] != SEM_DESASTRE){
                        play_sample(invalid, volume, 128, 1000, FALSE);
                        mensagem = MSG_NAO_DESCONSTRUIR_SOB_CALAMIDADE;
                    }
                    else
                    {
                        cidade.dinheiro_em_caixa -= PRECO_DESCONSTRUCAO;
                        cidade.terreno[tile_i][tile_j] = DESTRUICAO;
                        modo_construcao = NAO_CONSTRUIR;
                        play_sample(registradora, volume, 128, 1000, FALSE);
                        mensagem = MSG_DESCONSTRUCAO;
                    }
                    timer_msg = milisegundos;
                }
            }
        }

        //-----------------------
        //OUTROS
        //-----------------------

        //Se o cursor estiver sobre algum ponto da grade ela acende
        if( (mouse_x >= (X0+4)  && mouse_x <= (X0+4)+(matriz->w-8))
         && (mouse_y >= (Y0+4)  && mouse_y <= (Y0+4)+(matriz->h-8)) )
        {
            selecao_x = 170 + (((mouse_x-172)/27)*27);
            selecao_y = 60 + (((mouse_y-62)/27)*27);
            draw_selecao = true;
        }

        //Fim de jogo
        if(cidade.semanas <= 0 || cidade.populacao <= cidade.populacao_min)
        {
            if(cidade.semanas <= 0)
                tela_gameover(fundo, 1);
            else
                tela_gameover(fundo, 0);

            exit_screen = true;
        }

        ///--------------
        ///DRAW
        draw_sprite(buffer, gameBG, 0, 0);
        draw_sprite(buffer, barraSuperior,0,0);
        draw_sprite(buffer, janelaCampanhas, 640, 115);
        draw_sprite(buffer, janelaConstrutor, 10, 80);
        draw_sprite(buffer, janelaViaturas, 10, 318);
        draw_sprite(buffer, matriz, X0, Y0);
        draw_sprite(buffer, cashDisplay, 10, 550);
        draw_sprite(buffer, messageBoard, 640, 440);
        textprintf_centre_ex(buffer, display_cityName, 400, 7, makecol(255,255,255), -1, "%s", cidade.nome.c_str());
        textout_ex(buffer, display_Paineis, "BUILDER", 55, 85, makecol(255, 255, 255), -1);
        textout_ex(buffer, display_Paineis, "VEHICLE", 60, 320, makecol(255, 255, 255), -1);
        textout_ex(buffer, display_Paineis, "DECONSTRUCT", 45, 225, makecol(255, 255, 255), -1);
        textout_ex(buffer, display_Paineis, "CAMPAIGN", 680, 120, makecol(255, 255, 255), -1);
        textout_ex(buffer, display_Paineis, "MESSAGE BOARD", 660, 443, makecol(255, 255, 255), -1);
        textout_ex(buffer, display_weeksleft, "WEEKS LEFT", 720, 5, makecol(255, 255, 255), -1);
        textprintf_ex(buffer, display_weeksleft, 750, 20,makecol(255,255,255) , -1, "%d", cidade.semanas);

        //Cor do dinheiro fica vermelha se tiver abaixo de 1000
        if(cidade.dinheiro_em_caixa < 1000)
         textprintf_ex(buffer, display_cash, 25, 560,makecol(233,13,1) , -1, "IP$ %.2f", cidade.dinheiro_em_caixa);
        else
         textprintf_ex(buffer, display_cash, 25, 560,makecol(255,255,255) , -1, "IP$ %.2f", cidade.dinheiro_em_caixa);

        //Desenha Botões
        button_draw(b_backarrow, buffer);
        button_draw(b_save, buffer);
        button_draw(b_info, buffer);
        button_draw(b_help, buffer);
        button_draw(b_campanhaAmbulancia, buffer);
        button_draw(b_campanhaPolicia, buffer);
        button_draw(b_campanhaBombeiros, buffer);
        button_draw(b_campanhaInvestimento, buffer);
        button_draw(b_campanhaPromessa, buffer);
        button_draw(b_campanhaPropaganda, buffer);
        button_draw(b_campanhaTaxas, buffer);
        button_draw(b_buildHouse, buffer);
        button_draw(b_buildWater, buffer);
        button_draw(b_buildForest, buffer);
        button_draw(b_buildStreet, buffer);
        button_draw(b_buyAmbulance, buffer);
        button_draw(b_buyFiretruck, buffer);
        button_draw(b_buyPoliceCar, buffer);
        button_draw(b_vehicleInfo, buffer);
        button_draw(b_skipWeek, buffer);
        button_draw(b_deconstruct, buffer);

        //Mapa de tiles
        desenha_cidade(&cidade, buffer);

        //Mensagens no quadro de mensagens
        ExibirMensagem(&mensagem, &timer_msg);

        //Fundo auxiliar
        draw_sprite(fundo, buffer, 0, 0);

        //Seleção na grade
        if(draw_selecao)
        {
           draw_sprite(buffer, selectGrade, selecao_x, selecao_y);
           draw_selecao = false;
        }

        //Legendas dos preços
        if(is_on_button(b_buildHouse) && milisegundos - b_buildHouse->tempoEmCima >= TEMPO_LEGENDA_PRECO)
            textprintf_ex(buffer, display_costsubs, mouse_x+25, mouse_y+38, makecol(0,0,0), makecol(255,255,255), "IP$%.2f", PRECO_CASA);
        else if(is_on_button(b_buildStreet) && milisegundos - b_buildStreet->tempoEmCima >= TEMPO_LEGENDA_PRECO)
            textprintf_ex(buffer, display_costsubs, mouse_x+25, mouse_y+38, makecol(0,0,0), makecol(255,255,255), "IP$%.2f", PRECO_RUA);
        else if(is_on_button(b_buildWater) && milisegundos - b_buildWater->tempoEmCima >= TEMPO_LEGENDA_PRECO)
            textprintf_ex(buffer, display_costsubs, mouse_x+25, mouse_y+38, makecol(0,0,0), makecol(255,255,255), "IP$%.2f", PRECO_AGUA);
        else if(is_on_button(b_buildForest) && milisegundos - b_buildForest->tempoEmCima >= TEMPO_LEGENDA_PRECO)
            textprintf_ex(buffer, display_costsubs, mouse_x+25, mouse_y+38, makecol(0,0,0), makecol(255,255,255), "IP$%.2f", PRECO_FLORESTA);

        //Cursor
        if(mouse_on_screen())
        {
            if(modo_construcao == DESCONSTRUIR && mouse_y > barraSuperior->h)
                draw_sprite(buffer, cursorDemolicao, mouse_x, mouse_y-13);
            else if(modo_construcao != NAO_CONSTRUIR && mouse_y > barraSuperior->h)
                draw_sprite(buffer, cursorConstrucao, mouse_x, mouse_y-13);
            else
                draw_sprite(buffer, cursor, mouse_x, mouse_y);
        }

        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    stop_sample(gameSong1);

    //LIBERA BOTÕES
    destroy_button(b_backarrow);
    destroy_button(b_save);
    destroy_button(b_info);
    destroy_button(b_help);
    destroy_button(b_campanhaAmbulancia);
    destroy_button(b_campanhaPolicia);
    destroy_button(b_campanhaPolicia);
    destroy_button(b_campanhaInvestimento);
    destroy_button(b_campanhaPromessa);
    destroy_button(b_campanhaPropaganda);
    destroy_button(b_campanhaTaxas);
    destroy_button(b_buildHouse);
    destroy_button(b_buildWater);
    destroy_button(b_buildForest);
    destroy_button(b_buildStreet);
    destroy_button(b_buyAmbulance);
    destroy_button(b_buyFiretruck);
    destroy_button(b_buyPoliceCar);
    destroy_button(b_vehicleInfo);
    destroy_button(b_skipWeek);
    destroy_button(b_deconstruct);

    destroy_bitmap(fundo);
    UnloadGameContent();

    screenstate = MAINMENU;
    is_playing = false;
    fade_out(15);
}



///*****************************************************
///EXIBE MENSAGEM NO QUADRO DE MENSAGENS
///*****************************************************
void ExibirMensagem(int* mensagem, int* timer_msg)
{
    if(*mensagem != MSG_SEM_MENSAGEM)
    {
        if(*mensagem == MSG_DINHEIRO_INSUFICIENTE)
        {
          textout_ex(buffer, display_message_board, "Insuficient IP$ to", 645, 465, makecol(255, 0, 0), -1);
          textout_ex(buffer, display_message_board, "build this.", 645, 480, makecol(255, 0, 0), -1);
        }

        else if(*mensagem == MSG_DINHEIRO_INSUFICIENTE2)
        {
          textout_ex(buffer, display_message_board, "Insuficient IP$ to", 645, 465, makecol(255, 0, 0), -1);
          textout_ex(buffer, display_message_board, "demolish this.", 645, 480, makecol(255, 0, 0), -1);
        }

        else if(*mensagem == MSG_TERRENO_IMPROPRIO)
            textout_ex(buffer, display_message_board, "You can't build in there.", 645, 465, makecol(255, 0, 0), -1);

        else if(*mensagem == MSG_NAO_CONSTRUIR_SOB_CALAMIDADE)
        {
            textout_ex(buffer, display_message_board, "You cannot build over", 645, 465, makecol(255, 0, 0), -1);
            textout_ex(buffer, display_message_board, "disaster.", 645, 480, makecol(255, 0, 0), -1);
        }

        else if(*mensagem == MSG_SAVE)
            textout_ex(buffer, display_message_board, "GAME SAVED!!!", 645, 465, makecol(0, 0, 0), -1);

        else if(*mensagem == MSG_CASA_CONSTRUIDA)
            textout_ex(buffer, display_message_board, "Residence was built.", 645, 465, makecol(0, 0, 0), -1);

        else if(*mensagem == MSG_AGUA_CONSTRUIDA)
            textout_ex(buffer, display_message_board, "Water was built.", 645, 465, makecol(0, 0, 0), -1);

        else if(*mensagem == MSG_RUA_CONSTRUIDA)
            textout_ex(buffer, display_message_board, "Road was built.", 645, 465, makecol(0, 0, 0), -1);

        else if(*mensagem == MSG_FLORESTA_CONSTRUIDA)
            textout_ex(buffer, display_message_board, "Forest was built.", 645, 465, makecol(0, 0, 0), -1);

        else if(*mensagem == MSG_DESCONSTRUCAO)
        {
          textout_ex(buffer, display_message_board, "Terrain will  be free to", 645, 465, makecol(0, 0, 0), -1);
          textout_ex(buffer, display_message_board, "build after a week.", 645, 480, makecol(0, 0, 0), -1);
        }

        else if(*mensagem == MSG_TERRENO_LIVRE)
          textout_ex(buffer, display_message_board, "Terrain already cleared.", 645, 465, makecol(255, 0, 0), -1);

        else if(*mensagem == MSG_NAO_DESCONSTRUIR_SOB_CALAMIDADE)
        {
          textout_ex(buffer, display_message_board, "Cannot clear disaster", 645, 465, makecol(255, 0, 0), -1);
          textout_ex(buffer, display_message_board, "area.", 645, 480, makecol(255, 0, 0), -1);
        }

        else if(*mensagem == MSG_BUY_AMBULANCE)
          textout_ex(buffer, display_message_board, "Ambulance was bought.", 645, 465, makecol(0, 0, 0), -1);

        else if(*mensagem == MSG_BUY_POLICE)
          textout_ex(buffer, display_message_board, "Police car was bought.", 645, 465, makecol(0, 0, 0), -1);

        else if(*mensagem == MSG_BUY_FIRETRUCK)
          textout_ex(buffer, display_message_board, "Firetruck was bought.", 645, 465, makecol(0, 0, 0), -1);

        else if(*mensagem == MSG_FIRE)
          textout_ex(buffer, display_message_board, "FIRE!!!", 645, 465, makecol(255, 0, 0), -1);

        else if(*mensagem == MSG_FLOOD)
          textout_ex(buffer, display_message_board, "FLOOD!!!", 645, 465, makecol(255, 0, 0), -1);

        else if(*mensagem == MSG_METEOR)
          textout_ex(buffer, display_message_board, "METEOR!!!", 645, 465, makecol(255, 0, 0), -1);

        else if(*mensagem == MSG_MST)
          textout_ex(buffer, display_message_board, "MST!!!", 645, 465, makecol(255, 0, 0), -1);

        else if(*mensagem == MSG_ALIEN)
          textout_ex(buffer, display_message_board, "ALIEN INVASION!!!", 645, 465, makecol(255, 0, 0), -1);

        else if(*mensagem == MSG_IP_TEST)
          textout_ex(buffer, display_message_board, "PROGRAMMING TEST!!!", 645, 465, makecol(255, 0, 0), -1);

        if(milisegundos - *timer_msg >= TEMPO_MENSAGEM)
        {
            *mensagem = MSG_SEM_MENSAGEM;
            *timer_msg = milisegundos;
        }
    }
}



///*****************************************************
/// MENSAGEM COM OK/CANCEL
///*****************************************************
bool tela_aceitaCampanha_compraViatura(int tipo_campanha, BITMAP* fundo)
{
    bool exit_screen = false;
    bool escolha = false;
    bool tem_dinheiro_suficiente = true;

    Button* b_cancel = create_button(button2_cancel, button2_highlight, click, 415, 280, 415, 280);
    Button* b_yes;

    if(tipo_campanha < 8)
     b_yes = create_button(button2_accept, button2_highlight, click, 300, 280, 300, 280);
    else
     b_yes = create_button(button2_buy, button2_highlight, click, 300, 280, 300, 280);

    while (!exit_screen && !exit_program)
    {
        ///---------------
        ///INPUT
        Receive_Mouse_Input();
        Receive_Keyboard_Input();
        button_input(b_yes);
        button_input(b_cancel);

        ///---------------
        ///UPDATE

        //Botão Positivo
        if(b_yes->ativado && tem_dinheiro_suficiente)
        {
           play_sample(registradora, volume, 128, 1000, FALSE);
           exit_screen = true;
           escolha = true;
        }
        else if(b_yes->ativado && !tem_dinheiro_suficiente){
           play_sample(invalid, volume, 128, 1000, FALSE);
           b_yes->ativado = false;
        }

        //Botão CANCEL
        if(b_cancel->ativado || Pressed(KEY_ESC))
        {
           exit_screen = true;
           escolha = false;
        }

        ///---------------
        ///DRAW

        draw_sprite(buffer, fundo, 0, 0);
        draw_sprite(buffer, janelaPequena, 225, 180);
        button_draw(b_yes, buffer);
        button_draw(b_cancel, buffer);

        ///Campanha De ambulancia
        if (tipo_campanha==1)
        {
            textout_ex(buffer, textfont, "Extra 15% over ambulance", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "conservation state.", 250, 235, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "Cost: IP$1850,00", 250, 255, makecol(255, 255, 255), -1);

            if(cidade.dinheiro_em_caixa < 1850.0)
              tem_dinheiro_suficiente = false;
        }
        ///Campanha De polícia
        else if (tipo_campanha==2)
        {
            textout_ex(buffer, textfont, "Extra 15% over police car", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "conservation state.", 250, 235, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "Cost: IP$1000,00", 250, 255, makecol(255, 255, 255), -1);

            if(cidade.dinheiro_em_caixa < 1000.0)
              tem_dinheiro_suficiente = false;
        }
        ///Campanha De bombeiros
        else if (tipo_campanha==3)
        {
            textout_ex(buffer, textfont, "Extra 15% over fire truck ", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "conservation state.", 250, 235, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "Cost: IP$1500,00", 250, 255, makecol(255, 255, 255), -1);

            if(cidade.dinheiro_em_caixa < 1500.0)
              tem_dinheiro_suficiente = false;
        }
        ///Campanha De Investimento em infra-estrutura
        else if (tipo_campanha==4)
        {
            textout_ex(buffer, textfont, "15% reduction over city emigration tax.", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "for 2 weeks.", 250, 235, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "Cost: IP$3000,00", 250, 255, makecol(255, 255, 255), -1);

            if(cidade.dinheiro_em_caixa < 3000.0)
              tem_dinheiro_suficiente = false;
        }
        ///Campanha De Impostos
        else if (tipo_campanha==5)
        {
            textout_ex(buffer, textfont, "5% reduction over city taxes.", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "Cost: IP$200,00", 250, 240, makecol(255, 255, 255), -1);

            if(cidade.dinheiro_em_caixa < 200.0)
              tem_dinheiro_suficiente = false;
        }
        ///Campanha De Promessas
        else if (tipo_campanha==6)
        {
            textout_ex(buffer, textfont, "Extra 5% over city taxes.", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "Cost: IP$1000,00", 250, 240, makecol(255, 255, 255), -1);

            if(cidade.dinheiro_em_caixa < 1000.0)
              tem_dinheiro_suficiente = false;
        }

        ///Campanha De Propaganda
        else if (tipo_campanha==7)
        {
            textout_ex(buffer, textfont, "Extra 15% over city imigration tax", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "for 2 weeks.", 250, 235, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "Cost: IP$4000,00", 255, 255, makecol(255, 255, 255), -1);

            if(cidade.dinheiro_em_caixa < 4000.0)
              tem_dinheiro_suficiente = false;
        }

        ///--------------------------
        ///Compra de Viaturas

        ///Compra de Ambulância
        else if (tipo_campanha==8)
        {
            textout_ex(buffer, textfont, "Ambulance helps rescuing people", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "that were hurt by crimes or disasters.", 250, 235, makecol(255, 255, 255), -1);
            textprintf_ex(buffer, textfont, 255,255,makecol(255,255,255) , -1, "Cost: IP$%.2f", cidade.preco_ambu);

            if(cidade.dinheiro_em_caixa < cidade.preco_ambu)
              tem_dinheiro_suficiente = false;
        }

        ///Compra de carros da Polícia
        else if (tipo_campanha==9)
        {
            textout_ex(buffer, textfont, "Police cars protect people from", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "city crimes.", 250, 235, makecol(255, 255, 255), -1);
            textprintf_ex(buffer, textfont, 255,255,makecol(255,255,255) , -1, "Cost: IP$%.2f", cidade.preco_poli);

            if(cidade.dinheiro_em_caixa < cidade.preco_poli)
              tem_dinheiro_suficiente = false;
        }

        ///Compra de caminhão de Bombeiros
        else if (tipo_campanha==10)
        {
            textout_ex(buffer, textfont, "Fire trucks can control disaster effects", 250, 220, makecol(255, 255, 255), -1);
            textout_ex(buffer, textfont, "and rescue people affected.", 250, 235, makecol(255, 255, 255), -1);
            textprintf_ex(buffer, textfont, 255,255,makecol(255,255,255) , -1, "Cost: IP$%.2f", cidade.preco_bomb);

            if(cidade.dinheiro_em_caixa < cidade.preco_bomb)
              tem_dinheiro_suficiente = false;
        }

        //Cursor
        if(mouse_on_screen())
         draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer,0,0);
        clear(buffer);
    }

    destroy_button(b_yes);
    destroy_button(b_cancel);

    return escolha;
}


///*****************************************************
/// MENSAGEM COM OK/CANCEL
///*****************************************************
bool msg_okcancel(BITMAP* fundo)
{
    bool exit_screen = false;
    bool escolha = false;
    Button* b_ok = create_button(button2_ok, button2_highlight, click, 300, 280, 300, 280);
    Button* b_cancel = create_button(button2_cancel, button2_highlight, click, 415, 280, 415, 280);

    while (!exit_screen && !exit_program)
    {
        ///---------------
        ///INPUT
        Receive_Mouse_Input();
        Receive_Keyboard_Input();
        button_input(b_ok);
        button_input(b_cancel);

        ///---------------
        ///UPDATE

        //Botão OK
        if(b_ok->ativado)
        {
           exit_screen = true;
           escolha = true;
        }

        //Botão CANCEL
        if(b_cancel->ativado || Pressed(KEY_ESC))
        {
           exit_screen = true;
           escolha = false;
        }

        ///---------------
        ///DRAW

        draw_sprite(buffer, fundo, 0, 0);
        draw_sprite(buffer, janelaPequena, 225, 180);
        textout_ex(buffer, textfont, "Are you sure?", 250, 220, makecol(255, 255, 255), -1);
        textout_ex(buffer, textfont, "All your current progress will be lost.", 250, 235, makecol(255, 255, 255), -1);
        button_draw(b_ok, buffer);
        button_draw(b_cancel, buffer);

        //Cursor
        if(mouse_on_screen())
         draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer,0,0);
        clear(buffer);
    }

    destroy_button(b_ok);
    destroy_button(b_cancel);

    return escolha;
}



///*****************************************************
/// TELA DE AJUDA AO JOGADOR
///*****************************************************
void tela_ajuda(BITMAP* fundo)
{
    bool exit_screen = false;
    Button* b_X = create_button(close_x, close_x_highlight, click, 539, 180, 538, 180);

    while (!exit_screen && !exit_program)
    {
        ///---------------
        ///INPUT
        Receive_Mouse_Input();
        Receive_Keyboard_Input();
        button_input(b_X);

        ///---------------
        ///UPDATE

        //Botão X
        if(b_X->ativado || Pressed(KEY_ESC))
        {
           exit_screen = true;
        }

        ///---------------
        ///DRAW
        draw_sprite(buffer, fundo, 0, 0);
        draw_sprite(buffer, blueWindow, 225, 180);
        button_draw(b_X, buffer);
        textout_ex(buffer, window_title, "HELP", 350, 210, makecol(255, 255, 255), -1);
        textprintf_ex(buffer, textfont, 255, 240,makecol(255,255,255) , -1, "SHORTCUTS:");
        textprintf_ex(buffer, textfont, 255, 260,makecol(255,242,0) , -1, "F1   - Help");
        textprintf_ex(buffer, textfont, 255, 275,makecol(255,242,0) , -1, "F2   - Save");
        textprintf_ex(buffer, textfont, 255, 290,makecol(255,242,0) , -1, "F3   - City Info");
        textprintf_ex(buffer, textfont, 255, 305,makecol(255,242,0) , -1, "F4   - Vehicle Info");
        textprintf_ex(buffer, textfont, 255, 320,makecol(255,242,0) , -1, "F5   - Exit");
        textprintf_ex(buffer, textfont, 255, 335,makecol(255,242,0) , -1, "F12  - Skip Week");
        textprintf_ex(buffer, textfont, 255, 350,makecol(255,242,0) , -1, "H    - Build House");
        textprintf_ex(buffer, textfont, 255, 365,makecol(255,242,0) , -1, "R    - Build Road");
        textprintf_ex(buffer, textfont, 255, 380,makecol(255,242,0) , -1, "A    - Build Water");
        textprintf_ex(buffer, textfont, 255, 395,makecol(255,242,0) , -1, "G    - Build Forest");
        textprintf_ex(buffer, textfont, 255, 410,makecol(255,242,0) , -1, "D    - Deconstruct");
        textprintf_ex(buffer, textfont, 255, 425,makecol(255,242,0) , -1, "M    - Buy Ambulance");
        textprintf_ex(buffer, textfont, 255, 440,makecol(255,242,0) , -1, "P    - Buy Police Car");
        textprintf_ex(buffer, textfont, 255, 455,makecol(255,242,0) , -1, "F    - Buy Fire Truck");

        //Cursor
        if(mouse_on_screen())
         draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer,0,0);
        clear(buffer);
    }

    destroy_button(b_X);
}


///*****************************************************
/// TELA DE INFORMAÇÕES (As duas telas são nessa função)
///*****************************************************
void tela_informacoes(int tipoInfo, BITMAP* fundo)
{
    bool exit_screen = false;
    Button* b_X = create_button(close_x, close_x_highlight, click, 539, 180, 538, 180);

    while (!exit_screen && !exit_program)
    {
        ///---------------
        ///INPUT
        Receive_Mouse_Input();
        Receive_Keyboard_Input();
        button_input(b_X);

        ///---------------
        ///UPDATE

        //Botão X
        if(b_X->ativado || Pressed(KEY_ESC))
        {
           exit_screen = true;
        }

        ///---------------
        ///DRAW
        draw_sprite(buffer, fundo, 0, 0);
        draw_sprite(buffer, blueWindow, 225, 180);
        button_draw(b_X, buffer);

        //Se for informação da cidade
        if (tipoInfo == 1)
        {
            textout_ex(buffer, window_title, "CITY INFO", 320, 210, makecol(255, 255, 255), -1);
            textprintf_ex(buffer, textfont, 255, 240,makecol(255,255,255) , -1, "POPULATION:");

            if(cidade.populacao > cidade.populacao_min + 10)
             textprintf_ex(buffer, textfont, 370, 240,makecol(255,255,255) , -1, "%d", cidade.populacao);
            else
            textprintf_ex(buffer, textfont, 370, 240, makecol(240,75,85) , -1, "%d", cidade.populacao);

            textprintf_ex(buffer, textfont, 255, 255,makecol(255,255,255) , -1, "MINUMUM POPULATION: %d", cidade.populacao_min);
            textprintf_ex(buffer, textfont, 255, 270,makecol(255,255,255) , -1, "IMIGRATION RATE: %.2f%%", cidade.imigracao*100);
            textprintf_ex(buffer, textfont, 255, 285,makecol(255,255,255) , -1, "EMIGRATION RATE: %.2f%%", cidade.emigracao*100);
            textprintf_ex(buffer, textfont, 255, 300,makecol(255,255,255) , -1, "CRIME RATE: %.2f%%", cidade.indice_crime*100);
            textprintf_ex(buffer, textfont, 255, 315,makecol(255,255,255) , -1, "DISASTER RATE: %.2f%%", cidade.indice_desastre*100);
            textprintf_ex(buffer, textfont, 255, 330,makecol(255,255,255) , -1, "IDH: %.1f", cidade.idh);
            textprintf_ex(buffer, textfont, 255, 345,makecol(255,255,255) , -1, "TAX: %.2f%%", cidade.imposto*100);
            textprintf_ex(buffer, textfont, 255, 360,makecol(255,255,255) , -1, "GREEN AREA: %.2f%%", cidade.areaVerde*100);
            textprintf_ex(buffer, textfont, 255, 375,makecol(255,255,255) , -1, "GROUND AREA: %.2f%%", cidade.areaTerra*100);
            textprintf_ex(buffer, textfont, 255, 390,makecol(255,255,255) , -1, "BUILT AREA: %.2f%%", cidade.areaConstruida*100.0);
        }

        //Se for informação das viaturas
        else
        {
            textout_ex(buffer, window_title, "CITY VEHICLES", 280, 210, makecol(255, 255, 255), -1);
            textprintf_ex(buffer, textfont, 255, 240,makecol(255,255,255) , -1, "Number of Ambulances: %d", cidade.num_ambu);
            textprintf_ex(buffer, textfont, 255, 255,makecol(255,255,255) , -1, "Number of Police cars:  %d", cidade.num_poli);
            textprintf_ex(buffer, textfont, 255, 270,makecol(255,255,255) , -1, "Number of Firetrucks:  %d", cidade.num_bomb);
            textprintf_ex(buffer, textfont, 255, 305,makecol(255,255,255) , -1, "COST PER MONTH:");
            textprintf_ex(buffer, textfont, 265, 320,makecol(255,255,255) , -1, "-Ambulance: IP$%.2f", cidade.preco_ambu_mens);
            textprintf_ex(buffer, textfont, 265, 335,makecol(255,255,255) , -1, "-Police: IP$%.2f", cidade.preco_poli_mens);
            textprintf_ex(buffer, textfont, 265, 350,makecol(255,255,255) , -1, "-Fire Department: IP$%.2f", cidade.preco_bomb_mens);
        }

        //Cursor
        if(mouse_on_screen())
         draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer,0,0);
        clear(buffer);
    }

    destroy_button(b_X);
}


///************************************************
/// MENSAGEM DE FIM DE JOGO
///************************************************
void tela_gameover(BITMAP* fundo, int tipoMensagem)
{
    bool exit_screen = false;
    int timer_gameover = milisegundos;

    //Música
    if (tipoMensagem == true)
    {
        play_sample(aplausos, volume, 128, 1000, FALSE);
        play_sample(victory, volume, 128, 1000, FALSE);
    }
    else
        play_sample(gameover, volume, 128, 1000, FALSE);

    //GAMELOOP
    while (!exit_screen && !exit_program)
    {
        ///---------------
        ///INPUT
        Receive_Keyboard_Input();
        Receive_Mouse_Input();

        if(Pressed_Any_Key())
        {
          stop_sample(victory);
          stop_sample(gameover);
          exit_screen = true;
        }

        if(milisegundos - timer_gameover >= 5000)
        {
            exit_screen = true;
        }

        ///---------------
        ///DRAW
        draw_sprite(buffer, fundo, 0, 0);
        draw_sprite(buffer, janelaPequena, SCREEN_W/2 - janelaPequena->w/2, 180);

        ///Se o usuário venceu o jogo
        if (tipoMensagem == true)
        {
            textout_centre_ex(buffer, display_victory, "Congratulations!", SCREEN_W/2, 235, makecol(255, 255, 255), -1);
            textout_centre_ex(buffer, display_victory, "You won the game.", SCREEN_W/2, 270, makecol(255, 255, 255), -1);
        }

        ///Se o usuário perdeu o jogo
        else
        {
            textout_centre_ex(buffer, display_victory, "Game Over", SCREEN_W/2, 220, makecol(255, 255, 255), -1);
            textout_centre_ex(buffer, textfont, "I'm not voting on you again.", SCREEN_W/2, 270, makecol(255, 255, 255), -1);
        }

        //Cursor
        if(mouse_on_screen())
            draw_sprite(buffer, cursor, mouse_x, mouse_y);


        draw_sprite(screen, buffer,0,0);
        clear(buffer);
    }
}
