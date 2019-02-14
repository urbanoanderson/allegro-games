#ifndef HIGHSCORES_HPP_INCLUDED
#define HIGHSCORES_HPP_INCLUDED

#include <cstdio>
#include <string>

using namespace std;

enum { LIST_ARCADE = 0, LIST_CHALLENGE1 = 1, LIST_CHALLENGE2 = 2, LIST_CHALLENGE3 = 3 };

class Highscore
{
   public:
    string nomes_arcade[5];
    int scores_arcade[5];
    int times_arcade[5];

    string nomes_challenge1[5];
    int scores_challenge1[5];
    int times_challenge1[5];

    string nomes_challenge2[5];
    int scores_challenge2[5];
    int times_challenge2[5];

    string nomes_challenge3[5];
    int scores_challenge3[5];
    int times_challenge3[5];

    int Determine_Position(int time, int flag);
    void Registrar_Recorde(string name, int time, int score, int pos, int flag);
    int Load();
    void Save();
};

extern Highscore pontuacoes;


#endif // HIGHSCORES_HPP_INCLUDED
