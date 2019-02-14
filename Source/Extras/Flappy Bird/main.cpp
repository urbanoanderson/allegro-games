#include "init.h"
#include "mainmenu.h"
#include "gamescreen.h"

int main()
{
    init();

    while(!exit_program)
    {
       if(screenstate == MAINMENU)
        mainmenu();
       else if(screenstate == GAMESCREEN)
        gamescreen();
    }

    deinit();

	return 0;
}
