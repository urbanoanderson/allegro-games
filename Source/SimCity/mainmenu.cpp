#include "mainmenu.h"

void mainmenu()
{
    //BOTÕES
    Button* b_play = create_button(mainMenuPlay, mainMenuHighlight, click, 270, 280, 270, 280);
    Button* b_options = create_button(mainMenuOptions, mainMenuHighlight, click, 270, 370, 270, 370);
    Button* b_exit = create_button(mainMenuExit, mainMenuHighlight, click, 270, 460, 270, 460);

    bool exit_screen = false;
    int timer_trafego = milisegundos - 30000;

    //Coloca a música pra tocar se não estiver tocando
    if(is_playing == false)
    {
      play_sample(themeSong, volume, 128, 1000, TRUE);
      is_playing = true;
    }

    //LOOP DO MENU PRINCIPAL
    while (!exit_screen && !exit_program)
    {
        ///--------------
        ///INPUT
        Receive_Mouse_Input();
        button_input(b_play);
        button_input(b_options);
        button_input(b_exit);

        ///--------------
        ///UPDATE
        if(abs(milisegundos - timer_trafego) >= 25000)  //A cada 25 segundos toca o barulho do trafego
        {
          play_sample(trafego, volume, 128, 1000, FALSE);
          timer_trafego = milisegundos;
        }

        if(b_play->ativado)
        { screenstate = PLAYMENU; exit_screen = true; }

        else if(b_options->ativado)
        { screenstate = OPTIONSCREEN; exit_screen = true; }

        else if(b_exit->ativado)
         Exit_Game();


        ///--------------
        ///DRAW
        draw_sprite(buffer, mainBG, 0, 0);
        draw_sprite(buffer, logo, (SCREEN_W - logo->w)/2, 120);
        textout_ex(buffer, textfont, "Anderson Urbano - aafu", 590, 570, makecol(250, 175, 5), -1);
        textout_ex(buffer, textfont, " Jaime de Moura - jmcn", 590, 581, makecol(250, 232, 5), -1);

        button_draw(b_play, buffer);
        button_draw(b_options, buffer);
        button_draw(b_exit, buffer);

        if(mouse_on_screen())
         draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    destroy_button(b_play);
    destroy_button(b_options);
    destroy_button(b_exit);
}
