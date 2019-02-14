#include "optionscreen.h"

void optionscreen()
{
    fade_out(20);

    LoadOptionsContent();
    bool exit_screen = false;
    int vol = (volume - 5) / 50;

    //BOTÕES
    Button* b_plus = create_button(optionsMenuPlus, optionsMenuPlusHighlight, click, 550, 250, 550, 250);
    Button* b_minus = create_button(optionsMenuMinus, optionsMenuMinusHighlight, click, 180, 250, 179, 250);
    Button* b_fullscreen = create_button(optionsMenuWindowType, optionsMenuWindowTypeHighlight, click, 450, 370, 450, 370);
    Button* b_windowed = create_button(optionsMenuWindowType, optionsMenuWindowTypeHighlight, click, 225, 370, 225, 370);
    Button* b_backarrow = create_button(optionsMenuArrow, optionsMenuArrowHighlight, click, 20, 485, 20, 485);

    stop_sample(themeSong);
    is_playing = false;
    play_sample(optionsSong, volume, 128, 1000, TRUE);

    ///GAMELOOP
    while(!exit_screen && !exit_program)
    {
        ///------------
        ///INPUT
        Receive_Mouse_Input();
        button_input(b_plus);
        button_input(b_minus);
        button_input(b_windowed);
        button_input(b_fullscreen);
        button_input(b_backarrow);

        ///------------
        ///UPDATE

        if(b_backarrow->ativado)
        { screenstate = MAINMENU; exit_screen = true; }

        else if(b_plus->ativado)
        {
            play_sample(click, volume, 128, 1000, FALSE);
            vol++;
            if(vol > 5)
             vol = 5;
            b_plus->ativado = FALSE;
        }

        else if(b_minus->ativado)
        {
            play_sample(click, volume, 128, 1000, FALSE);
            vol--;
            if(vol < 0)
             vol = 0;
            b_minus->ativado = FALSE;
        }

        else if(b_windowed->ativado)
        {
            if(!is_windowed_mode())
             set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);
            b_windowed->ativado = FALSE;
            screenmode = WINDOWED;
        }

        else if(b_fullscreen->ativado)
        {
            if(is_windowed_mode())
             set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCREEN_W, SCREEN_H, 0, 0);
            b_fullscreen->ativado = FALSE;
            screenmode = FULLSCREEN;
        }

        //Ajusta o volume
        if(vol != 0)
         volume = (vol * 50) + 5;
        else
         volume = 0;

        adjust_sample(optionsSong, volume, 128, 1000, TRUE);

        ///------------
        ///DRAW
        draw_sprite(buffer, optionsBG, 0, 0);
        draw_sprite(buffer, optionstitle, 115, 70);
        textout_ex(buffer, optionsFont, "VOLUME", 50, 265, makecol(255, 201, 14), -1);
        textout_ex(buffer, optionsFont, "VIDEO MODE", 35, 400, makecol(255, 201, 14), -1);
        button_draw(b_plus, buffer);
        button_draw(b_minus, buffer);
        button_draw(b_windowed, buffer);
        button_draw(b_fullscreen, buffer);
        button_draw(b_backarrow, buffer);
        textout_ex(buffer, optionsFont, "WINDOWED", 250, 395, makecol(255, 255, 255), -1);
        textout_ex(buffer, optionsFont, "FULLSCREEN", 475, 395, makecol(255, 255, 255), -1);

        //sprites das barras de volume
        for(int cont = 0; cont < 5; cont++)
          draw_sprite(buffer, volumeOff, 280 + (50 * cont), 230);
        for(int cont = 0; cont < vol; cont++)
          draw_sprite(buffer, volumeOn, 280 + (50 * cont), 230);

        if(mouse_on_screen())
        draw_sprite(buffer, cursor, mouse_x, mouse_y);

        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    //FINALIZAÇÃO
    destroy_button(b_plus);
    destroy_button(b_minus);
    destroy_button(b_windowed);
    destroy_button(b_fullscreen);
    destroy_button(b_backarrow);
    UnloadOptionsContent();

    Save_user_configuration();
    fade_out(25);
}
