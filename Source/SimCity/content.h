#ifndef CONTENT_H_INCLUDED
#define CONTENT_H_INCLUDED

#include <allegro.h>

///-----------------------
///FONT POINTERS
///-----------------------
extern FONT* textfont;
extern FONT* window_title;
extern FONT* sizeChoiceHighlight;
extern FONT* sizeChoiceButton;
extern FONT* play_button;
extern FONT* optionsFont1;
extern FONT* optionsFont2;
extern FONT* optionsFont;
extern FONT* display_cash;
extern FONT* display_cityName;
extern FONT* display_Paineis;
extern FONT* display_weeksleft;
extern FONT* display_costsubs;
extern FONT* display_victory;
extern FONT* display_message_board;

///-----------------------
///SAMPLE POINTERS
///-----------------------
extern SAMPLE* click;
extern SAMPLE* trafego;

extern SAMPLE* invalid;
extern SAMPLE* registradora;
extern SAMPLE* demolition;
extern SAMPLE* ambulanceSample;
extern SAMPLE* policeradioSample;
extern SAMPLE* firetruckSample;
extern SAMPLE* aplausos;
extern SAMPLE* victory;
extern SAMPLE* gameover;

extern SAMPLE* themeSong;
extern SAMPLE* optionsSong;
extern SAMPLE* gameSong1;

///-----------------------
///BITMAPS
///-----------------------
extern BITMAP* cursor;
extern BITMAP* cursorConstrucao;
extern BITMAP* cursorDemolicao;

extern BITMAP* mainBG;
extern BITMAP* optionsBG;
extern BITMAP* gameBG;

extern BITMAP* logo;
extern BITMAP* optionstitle;
extern BITMAP* volumeOn;
extern BITMAP* volumeOff;
extern BITMAP* blueWindow;
extern BITMAP* typingSpace;

extern BITMAP* barraSuperior;
extern BITMAP* matriz;
extern BITMAP* selectGrade;
extern BITMAP* janelaCampanhas;
extern BITMAP* janelaConstrutor;
extern BITMAP* janelaViaturas;
extern BITMAP* janelaPequena;
extern BITMAP* cashDisplay;
extern BITMAP* messageBoard;

extern BITMAP* mainMenuPlay;
extern BITMAP* mainMenuOptions;
extern BITMAP* mainMenuExit;
extern BITMAP* mainMenuHighlight;
extern BITMAP* optionsMenuArrow;
extern BITMAP* optionsMenuArrowHighlight;
extern BITMAP* optionsMenuMinus;
extern BITMAP* optionsMenuMinusHighlight;
extern BITMAP* optionsMenuPlus;
extern BITMAP* optionsMenuPlusHighlight;
extern BITMAP* optionsMenuWindowType;
extern BITMAP* optionsMenuWindowTypeHighlight;
extern BITMAP* playMenuNewGame;
extern BITMAP* playMenuLoadGame;
extern BITMAP* playMenuHighlight;
extern BITMAP* close_x;
extern BITMAP* close_x_highlight;

extern BITMAP* backArrow;
extern BITMAP* backArrowON;
extern BITMAP* save;
extern BITMAP* saveON;
extern BITMAP* info;
extern BITMAP* infoON;
extern BITMAP* help;
extern BITMAP* helpON;
extern BITMAP* skipWeek;
extern BITMAP* skipWeekON;
extern BITMAP* build_house;
extern BITMAP* build_water;
extern BITMAP* build_forest;
extern BITMAP* build_street;
extern BITMAP* buy_ambulance;
extern BITMAP* buy_policecar;
extern BITMAP* buy_firetruck;
extern BITMAP* vehicle_info;
extern BITMAP* vehicle_infoON;
extern BITMAP* botaoDestrutor;
extern BITMAP* botaoDestrutorON;
extern BITMAP* campaign_ambulance;
extern BITMAP* campaign_policemen;
extern BITMAP* campaign_fireman;
extern BITMAP* campaign_taxes;
extern BITMAP* campaign_invest;
extern BITMAP* campaign_promisse;
extern BITMAP* campaign_advertisement;
extern BITMAP* buttonHighlight;
extern BITMAP* button2_ok;
extern BITMAP* button2_accept;
extern BITMAP* button2_buy;
extern BITMAP* button2_cancel;
extern BITMAP* button2_highlight;

extern BITMAP* tile_casa;
extern BITMAP* tile_construcao;
extern BITMAP* tile_terra;
extern BITMAP* tile_floresta;
extern BITMAP* tile_inexplorado;
extern BITMAP* tile_rua;
extern BITMAP* tile_destruicao;
extern BITMAP* anim_tile_agua;
extern BITMAP* desastre_mst;
extern BITMAP* desastre_homicidio;
extern BITMAP* anim_desastre_alien;
extern BITMAP* anim_desastre_provaIP;
extern BITMAP* anim_desastre_meteoro;
extern BITMAP* anim_desastre_assalto;
extern BITMAP* anim_desastre_chacina;
extern BITMAP* anim_desastre_enchente;
extern BITMAP* anim_desastre_incendio;


 void LoadDefaultContent();
 void UnloadDefaultContent();
 void LoadOptionsContent();
 void UnloadOptionsContent();
 void LoadGameContent();
 void UnloadGameContent();


#endif // CONTENT_H_INCLUDED
