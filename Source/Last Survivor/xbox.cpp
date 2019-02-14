#include "xbox.hpp"

int xbox_prev_state[TAM_MAX];
int xbox[TAM_MAX];

void xbox_input()
{
  if(num_joysticks > 0)
  {
    for(int i = 0; i < TAM_MAX; i++)
      xbox_prev_state[i] = xbox[i];

    poll_joystick();

    xbox[BUTTON_A] = joy[0].button[0].b;
    xbox[BUTTON_B] = joy[0].button[1].b;
    xbox[BUTTON_X] = joy[0].button[2].b;
    xbox[BUTTON_Y] = joy[0].button[3].b;
    xbox[BUTTON_LB] = joy[0].button[4].b;
    xbox[BUTTON_RB] = joy[0].button[5].b;
    xbox[BUTTON_BACK] = joy[0].button[6].b;
    xbox[BUTTON_START] = joy[0].button[7].b;
    xbox[BUTTON_LS] = joy[0].button[8].b;
    xbox[BUTTON_RS] = joy[0].button[9].b;

    xbox[DPAD_UP] = (joy[0].stick[1].axis[1].d1 == -1);
    xbox[DPAD_DOWN] = (joy[0].stick[1].axis[1].d2 == -1);
    xbox[DPAD_LEFT] = (joy[0].stick[1].axis[0].d1 == -1);
    xbox[DPAD_RIGHT] = (joy[0].stick[1].axis[0].d2 == -1);

    xbox[LSTICK_UP] = (joy[0].stick[0].axis[1].pos < 0);
    xbox[LSTICK_DOWN] = (joy[0].stick[0].axis[1].pos > 0);
    xbox[LSTICK_LEFT] = (joy[0].stick[0].axis[0].pos < 0);
    xbox[LSTICK_RIGHT] = (joy[0].stick[0].axis[0].pos > 0);
  }
}

int xbox_just_released(int botao)
{
  return(xbox_prev_state[botao] == 1 && xbox[botao] == 0);
}

int xbox_holding(int botao)
{
  return (xbox_prev_state[botao] == 1 && xbox[botao] == 1);
}

int xbox_just_pressed(int botao)
{
  return(xbox_prev_state[botao] == 0 && xbox[botao] == 1);
}

int xbox_just_pressed_any_button()
{
    int resultado = 0;

    for(int i = 0; i <= BUTTON_START && !resultado; i++)
    {
       if(xbox[i] == 1)
         resultado = 1;
    }

    return resultado;
}
