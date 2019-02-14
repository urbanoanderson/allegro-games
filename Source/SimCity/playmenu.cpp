#include "playmenu.h"

void playmenu()
{
    bool exit_screen = false;

    //BOTÕES
    Button* b_newgame = create_button(playMenuNewGame, playMenuHighlight, click, 295, 285, 295, 285);
    Button* b_loadgame = create_button(playMenuLoadGame, playMenuHighlight, click, 295, 415, 295, 415);
    Button* b_X = create_button(close_x, close_x_highlight, click, 539, 240, 539, 240);

    ///GAMELOOP
    while(!exit_screen && !exit_program)
    {
        ///----------
        ///INPUT
        Receive_Keyboard_Input();
        Receive_Mouse_Input();

        button_input(b_newgame);
        button_input(b_loadgame);
        button_input(b_X);

        ///----------
        ///UPDATE

        if(b_X->ativado || Pressed(KEY_ESC))
        {
           exit_screen = true;
           screenstate = MAINMENU;
        }

        else if(b_newgame->ativado)
        {
           exit_screen = true;
           screenstate = NEWGAME;
        }

        else if(b_loadgame->ativado)
        {
           exit_screen = true;
           screenstate = LOADGAME;
        }

        ///----------
        ///DRAW
        draw_sprite(buffer, mainBG, 0, 0);
        draw_sprite(buffer, logo, (SCREEN_W - logo->w)/2, 120);
        draw_sprite(buffer, blueWindow, (SCREEN_W - blueWindow->w)/2, 240);
        textout_ex(buffer, textfont, "Anderson Urbano - aafu", 590, 570, makecol(250, 175, 5), -1);
        textout_ex(buffer, textfont, " Jaime de Moura - jmcn", 590, 581, makecol(250, 232, 5), -1);

        button_draw(b_newgame, buffer);
        button_draw(b_loadgame, buffer);
        button_draw(b_X, buffer);

        if(mouse_on_screen())
         draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    destroy_button(b_newgame);
    destroy_button(b_loadgame);
    destroy_button(b_X);
}


void newgame()
{
    bool exit_screen = false;
    std::string texto = "";

    Button* b_X = create_button(close_x, close_x_highlight, click, 539, 240, 539, 240);
    Button* b_digitar = create_button(typingSpace, NULL, NULL, 240, 320, 240, 320);
    TextButton* tb_small = create_textbutton("SMALL", sizeChoiceButton, sizeChoiceHighlight, sizeChoiceButton, SCREEN_W/2 - 100, 430);
    TextButton* tb_medium = create_textbutton("MEDIUM", sizeChoiceButton, sizeChoiceHighlight, sizeChoiceButton, SCREEN_W/2, 430);
    TextButton* tb_large = create_textbutton("LARGE", sizeChoiceButton, sizeChoiceHighlight, sizeChoiceButton, SCREEN_W/2 + 100, 430);
    TextButton* tb_play = create_textbutton("PLAY", play_button, play_button, play_button, SCREEN_W/2, 470);

    int sizeMap = NONE;

    while(!exit_screen && !exit_program)
    {
        ///-----------
        ///INPUT
        Receive_Keyboard_Input();
        Receive_Mouse_Input();

        button_input(b_X);
        button_input(b_digitar);
        textbutton_input(tb_small);
        textbutton_input(tb_medium);
        textbutton_input(tb_large);
        textbutton_input(tb_play);

        if(!((getpixel(buffer, mouse_x, mouse_y) != makecol(255, 0, 255))
         &&((mouse_x >= 240 && mouse_x <= 240 + typingSpace->w) && (mouse_y >= 320 && mouse_y <= 320 + typingSpace->h)))
         && (mouse_b & 1) )
         b_digitar->ativado = FALSE;

        ///-----------
        ///UPDATE

        if(b_X->ativado || Pressed(KEY_ESC))
        {
           exit_screen = true;
           screenstate = PLAYMENU;
        }

        else if(tb_small->ativado)
        {
           sizeMap = SMALL;
           tb_medium->ativado = false;
           tb_large->ativado = false;
        }

        else if(tb_medium->ativado)
        {
           sizeMap = MEDIUM;
           tb_small->ativado = false;
           tb_large->ativado = false;
        }

        else if(tb_large->ativado)
        {
           sizeMap = LARGE;
           tb_medium->ativado = false;
           tb_small->ativado = false;
        }

        //Apertou no PLAY ou ENTER
        if( (tb_play->ativado || Pressed(KEY_ENTER)) && texto != "" && sizeMap != NONE)
        {
            if(create_cidade(sizeMap, texto) == 1)  //Deu certo
            {
              stop_sample(themeSong);
              stop_sample(trafego);
              screenstate = GAMESCREEN;
            }

            else
            {
                erro_newload = 0;
                screenstate = TELA_ERRO;
            }

            exit_screen = true;
        }

        if(keypressed() && b_digitar->ativado)
         PegaTexto(&texto);

        ///------------
        ///DRAW
        draw_sprite(buffer, mainBG, 0, 0);
        draw_sprite(buffer, logo, (SCREEN_W - logo->w)/2, 120);
        draw_sprite(buffer, blueWindow, (SCREEN_W - blueWindow->w)/2, 240);
        textout_ex(buffer, textfont, "Anderson Urbano - aafu", 590, 570, makecol(250, 175, 5), -1);
        textout_ex(buffer, textfont, " Jaime de Moura - jmcn", 590, 581, makecol(250, 232, 5), -1);
        textout_ex(buffer, textfont, "Enter the city's name:", 245, 300, makecol(255, 255, 255), -1);
        textout_ex(buffer, window_title, "NEW GAME", 265, 270, makecol(255, 255, 255), -1);
        button_draw(b_X, buffer);
        button_draw(b_digitar, buffer);
        textbutton_draw(tb_small, buffer);
        textbutton_draw(tb_medium, buffer);
        textbutton_draw(tb_large, buffer);
        textbutton_draw(tb_play, buffer);

        //Texto digitado
        textout_ex(buffer, font, texto.c_str(), 251, 338, makecol(0, 0, 0), -1);

        //Linha de marcação
        if( ((milisegundos / 300) % 2 == 0)  &&  b_digitar->ativado)
          vline(buffer, (texto.length() * 8) + 251, (338 - 2), (338 + 8), makecol(0,0,0));

        if(mouse_on_screen())
         draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    destroy_button(b_X);
    destroy_button(b_digitar);
    destroy_textbutton(tb_small);
    destroy_textbutton(tb_medium);
    destroy_textbutton(tb_large);
    destroy_textbutton(tb_play);
}


void loadgame()
{
    bool exit_screen = false;
    std::string texto = "";

    Button* b_X = create_button(close_x, close_x_highlight, click, 539, 240, 539, 240);
    Button* b_digitar = create_button(typingSpace, NULL, NULL, 240, 320, 240, 320);

    while(!exit_screen && !exit_program)
    {
        ///-----------
        ///INPUT
        Receive_Keyboard_Input();
        Receive_Mouse_Input();

        button_input(b_X);
        button_input(b_digitar);

        if(!((getpixel(buffer, mouse_x, mouse_y) != makecol(255, 0, 255))
         &&((mouse_x >= 240 && mouse_x <= 240 + typingSpace->w) && (mouse_y >= 320 && mouse_y <= 320 + typingSpace->h)))
         && (mouse_b & 1) )
         b_digitar->ativado = FALSE;

        //TENTA ABRIR O ARQUIVO DE CIDADE
        if(Pressed(KEY_ENTER))
        {
           //Sucesso
           if(load_cidade("Arquivos/" + texto + ".txt") != NULL)
           {
               stop_sample(themeSong);
               stop_sample(trafego);
               screenstate = GAMESCREEN;
           }

           //Falha
           else
           {
               erro_newload = 1;
               screenstate = TELA_ERRO;
           }

           exit_screen = true;
        }

        ///-----------
        ///UPDATE

        if(b_X->ativado || Pressed(KEY_ESC))
        {
           exit_screen = true;
           screenstate = PLAYMENU;
        }

        if(keypressed() && b_digitar->ativado)
         PegaTexto(&texto);
        else
         clear_keybuf();

        ///------------
        ///DRAW
        draw_sprite(buffer, mainBG, 0, 0);
        draw_sprite(buffer, logo, (SCREEN_W - logo->w)/2, 120);
        draw_sprite(buffer, blueWindow, (SCREEN_W - blueWindow->w)/2, 240);
        textout_ex(buffer, textfont, "Anderson Urbano - aafu", 590, 570, makecol(250, 175, 5), -1);
        textout_ex(buffer, textfont, " Jaime de Moura - jmcn", 590, 581, makecol(250, 232, 5), -1);
        textout_ex(buffer, textfont, "Enter the city's name:", 245, 300, makecol(255, 255, 255), -1);
        textout_ex(buffer, window_title, "LOAD GAME", 265, 270, makecol(255, 255, 255), -1);
        button_draw(b_X, buffer);
        button_draw(b_digitar, buffer);

        //Texto digitado
        textout_ex(buffer, font, texto.c_str(), 251, 338, makecol(0, 0, 0), -1);

        //Linha de marcação
        if( ((milisegundos / 300) % 2 == 0)  &&  b_digitar->ativado)
          vline(buffer, (texto.length() * 8) + 251, (338 - 2), (338 + 8), makecol(0,0,0));

        if(mouse_on_screen())
         draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    destroy_button(b_X);
    destroy_button(b_digitar);
}


///***************************************
///TELA DE ERRO DE NEW GAME/LOAD GAME
///***************************************
void telaerro()
{

    bool exit_screen = false;
    Button* b_X = create_button(close_x, close_x_highlight, click, 539, 240, 539, 240);

    ///GAMELOOP
    while(!exit_screen && !exit_program)
    {
        ///-----------
        ///INPUT
        Receive_Keyboard_Input();
        Receive_Mouse_Input();
        button_input(b_X);

        if(Pressed(KEY_ESC) || b_X->ativado)
        {
            screenstate = PLAYMENU;
            exit_screen = true;
        }

        ///-----------
        ///DRAW
        draw_sprite(buffer, mainBG, 0, 0);
        draw_sprite(buffer, logo, (SCREEN_W - logo->w)/2, 120);
        draw_sprite(buffer, blueWindow, (SCREEN_W - blueWindow->w)/2, 240);
        textout_ex(buffer, textfont, "Anderson Urbano - aafu", 590, 570, makecol(250, 175, 5), -1);
        textout_ex(buffer, textfont, " Jaime de Moura - jmcn", 590, 581, makecol(250, 232, 5), -1);
        textout_ex(buffer, textfont, "ERROR:", 260, 300, makecol(237, 28, 36), -1);
        button_draw(b_X, buffer);

        if(erro_newload == 0)
         textout_ex(buffer, textfont, "City name already exists", 260, 315, makecol(255, 255, 255), -1);
        else
         textout_ex(buffer, textfont, "City name does not exist", 260, 315, makecol(255, 255, 255), -1);

        if(mouse_on_screen())
         draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    ///FINALIZAÇÃO
    destroy_button(b_X);
}
