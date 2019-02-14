#include "highscores.hpp"

Highscore pontuacoes;

void Highscore::Registrar_Recorde(string name, int time, int score, int pos, int flag)
{
   //ARCADE
   if(flag == LIST_ARCADE)
   {
     nomes_arcade[0] = name;
     times_arcade[0] = time;
     scores_arcade[0] = score;

     for(int i = 0; i < pos; i++)
     {
       string str_aux = nomes_arcade[i+1];
       int time_aux = times_arcade[i+1];
       int score_aux = scores_arcade[i+1];

       nomes_arcade[i+1] = nomes_arcade[i];
       times_arcade[i+1] = times_arcade[i];
       scores_arcade[i+1] = scores_arcade[i];

       nomes_arcade[i] = str_aux;
       times_arcade[i] = time_aux;
       scores_arcade[i] = score_aux;
     }
   }

   //CHALLENGE 1
   else if(flag == LIST_CHALLENGE1)
   {
     nomes_challenge1[0] = name;
     times_challenge1[0] = time;
     scores_challenge1[0] = score;

     for(int i = 0; i < pos; i++)
     {
       string str_aux = nomes_challenge1[i+1];
       int time_aux = times_challenge1[i+1];
       int score_aux = scores_challenge1[i+1];

       nomes_challenge1[i+1] = nomes_challenge1[i];
       times_challenge1[i+1] = times_challenge1[i];
       scores_challenge1[i+1] = scores_challenge1[i];

       nomes_challenge1[i] = str_aux;
       times_challenge1[i] = time_aux;
       scores_challenge1[i] = score_aux;
     }
   }

   //CHALLENGE 2
   else if(flag == LIST_CHALLENGE2)
   {
     nomes_challenge2[0] = name;
     times_challenge2[0] = time;
     scores_challenge2[0] = score;

     for(int i = 0; i < pos; i++)
     {
       string str_aux = nomes_challenge2[i+1];
       int time_aux = times_challenge2[i+1];
       int score_aux = scores_challenge2[i+1];

       nomes_challenge2[i+1] = nomes_challenge2[i];
       times_challenge2[i+1] = times_challenge2[i];
       scores_challenge2[i+1] = scores_challenge2[i];

       nomes_challenge2[i] = str_aux;
       times_challenge2[i] = time_aux;
       scores_challenge2[i] = score_aux;
     }
   }

   //CHALLENGE 3
   else if(flag == LIST_CHALLENGE3)
   {
     nomes_challenge3[0] = name;
     times_challenge3[0] = time;
     scores_challenge3[0] = score;

     for(int i = 0; i < pos; i++)
     {
       string str_aux = nomes_challenge3[i+1];
       int time_aux = times_challenge3[i+1];
       int score_aux = scores_challenge3[i+1];

       nomes_challenge3[i+1] = nomes_challenge3[i];
       times_challenge3[i+1] = times_challenge3[i];
       scores_challenge3[i+1] = scores_challenge3[i];

       nomes_challenge3[i] = str_aux;
       times_challenge3[i] = time_aux;
       scores_challenge3[i] = score_aux;
     }
   }
}

int Highscore::Determine_Position(int time, int flag)
{
  int pos = -1;

  //ARCADE
  if(flag == LIST_ARCADE)
  {
     for(int i = 0; i < 5; i++)
     {
        if(time > times_arcade[i])
         pos = i;
     }
  }

  //CHALLENGE 1
  else if(flag == LIST_CHALLENGE1)
  {
     for(int i = 0; i < 5; i++)
     {
        if(time > times_challenge1[i])
         pos = i;
     }
  }

  //CHALLENGE 2
  else if(flag == LIST_CHALLENGE2)
  {
     for(int i = 0; i < 5; i++)
     {
        if(time > times_challenge2[i])
         pos = i;
     }
  }

  //CHALLENGE 3
  else if(flag == LIST_CHALLENGE3)
  {
     for(int i = 0; i < 5; i++)
     {
        if(time > times_challenge3[i])
         pos = i;
     }
  }

  return pos;
}

int Highscore::Load()
{
   FILE* f = fopen("Data/highscores.dat", "rb");

   //Reseta os highscores
   if(!f)
   {
      for(int i = 0; i < 5; i++)
      {
        nomes_arcade[i] = (string) "";
        scores_arcade[i] = -1;
        times_arcade[i] = -1;

        nomes_challenge1[i] = (string) "";
        scores_challenge1[i] = -1;
        times_challenge1[i] = -1;

        nomes_challenge2[i] = (string) "";
        scores_challenge2[i] = -1;
        times_challenge2[i] = -1;

        nomes_challenge3[i] = (string) "";
        scores_challenge3[i] = -1;
        times_challenge3[i] = -1;
      }

      return NULL;
   }

   //Lê os highscores
   else
   {
      char aux[5];

      //--------------------
      //ARCADE
      for(int i = 0; i < 5; i++)
      {
        fread(aux, sizeof(char), 5, f);
        nomes_arcade[i] = (string) aux;
      }

      fread(scores_arcade, sizeof(int), 5, f);
      fread(times_arcade, sizeof(int), 5, f);


      //--------------------
      //CHALLENGE 1
      for(int i = 0; i < 5; i++)
      {
        fread(aux, sizeof(char), 5, f);
        nomes_challenge1[i] = (string) aux;
      }

      fread(scores_challenge1, sizeof(int), 5, f);
      fread(times_challenge1, sizeof(int), 5, f);


      //--------------------
      //CHALLENGE 2
      for(int i = 0; i < 5; i++)
      {
        fread(aux, sizeof(char), 5, f);
        nomes_challenge2[i] = (string) aux;
      }

      fread(scores_challenge2, sizeof(int), 5, f);
      fread(times_challenge2, sizeof(int), 5, f);


      //--------------------
      //CHALLENGE 3
      for(int i = 0; i < 5; i++)
      {
        fread(aux, sizeof(char), 5, f);
        nomes_challenge3[i] = (string) aux;
      }

      fread(scores_challenge3, sizeof(int), 5, f);
      fread(times_challenge3, sizeof(int), 5, f);

      return 1;
   }
}

void Highscore::Save()
{
    FILE* f = fopen("Data/highscores.dat", "wb");

    if(f)
    {
      //--------------------
      //ARCADE
      for(int i = 0; i < 5; i++)
       fwrite(nomes_arcade[i].c_str(), sizeof(char), 5, f);

      fwrite(scores_arcade, sizeof(int), 5, f);
      fwrite(times_arcade, sizeof(int), 5, f);

      //--------------------
      //CHALLENGE 1
      for(int i = 0; i < 5; i++)
       fwrite(nomes_challenge1[i].c_str(), sizeof(char), 5, f);

      fwrite(scores_challenge1, sizeof(int), 5, f);
      fwrite(times_challenge1, sizeof(int), 5, f);

      //--------------------
      //CHALLENGE 2
      for(int i = 0; i < 5; i++)
       fwrite(nomes_challenge2[i].c_str(), sizeof(char), 5, f);

      fwrite(scores_challenge2, sizeof(int), 5, f);
      fwrite(times_challenge2, sizeof(int), 5, f);

      //--------------------
      //CHALLENGE 3
      for(int i = 0; i < 5; i++)
       fwrite(nomes_challenge3[i].c_str(), sizeof(char), 5, f);

      fwrite(scores_challenge3, sizeof(int), 5, f);
      fwrite(times_challenge3, sizeof(int), 5, f);
    }
}
