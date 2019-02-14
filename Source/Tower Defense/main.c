#include "init.h"
#include "Mainmenu.h"
#include "Gamescreen.h"
#include "Gameover.h"
#include "Vitoria.h"

int main()
{
   init();

   while(!exit_program)
   {
      if(screen_state == MAINMENU)
       mainmenu();
      else if(screen_state == GAMESCREEN)
       gamescreen();
      else if(screen_state == GAMEOVER)
       gameover();
      else if(screen_state == VITORIA)
       vitoria();
   }

  deinit();

  return 0;
}
END_OF_MAIN();
