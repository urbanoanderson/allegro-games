#include "init.h"
#include "mainmenu.h"
#include "gamescreen.h"
#include "gameover.h"
#include "victory.h"

int main()
{
    init();

    while(!exit_program)
    {
       if(screenstate == MAINMENU)
        mainmenu();
       else if(screenstate == GAMESCREEN)
        gamescreen();
       else if(screenstate == GAMEOVER)
        gameover();
       else if(screenstate == VICTORY)
        victory();
    }

    deinit();

	return 0;
}
