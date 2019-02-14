#include "init.h"
#include "mainmenu.h"
#include "playmenu.h"
#include "optionscreen.h"
#include "gamescreen.h"

int main()
{
    init();
    LoadDefaultContent();

    while(!exit_program)
    {
        if(screenstate == MAINMENU)
            mainmenu();
        else if(screenstate == PLAYMENU)
            playmenu();
        else if(screenstate == NEWGAME)
            newgame();
        else if(screenstate == LOADGAME)
            loadgame();
        else if(screenstate == GAMESCREEN)
            gamescreen();
        else if(screenstate == OPTIONSCREEN)
            optionscreen();
        else if(screenstate == TELA_ERRO)
            telaerro();
    }

    UnloadDefaultContent();
    deinit();

    return 0;
}
END_OF_MAIN()
