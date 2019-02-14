#include "content.h"

    ///-----------------------
    ///FONT POINTERS
    ///-----------------------
    FONT* textfont;
    FONT* window_title;
    FONT* sizeChoiceHighlight;
    FONT* sizeChoiceButton;
    FONT* play_button;
    FONT* optionsFont1;
    FONT* optionsFont2;
    FONT* optionsFont;
    FONT* display_cash;
    FONT* display_cityName;
    FONT* display_Paineis;
    FONT* display_weeksleft;
    FONT* display_costsubs;
    FONT* display_victory;
    FONT* display_message_board;

    ///-----------------------
    ///SAMPLE POINTERS
    ///-----------------------
    SAMPLE* click;
    SAMPLE* trafego;

    SAMPLE* invalid;
    SAMPLE* registradora;
    SAMPLE* demolition;
    SAMPLE* ambulanceSample;
    SAMPLE* policeradioSample;
    SAMPLE* firetruckSample;
    SAMPLE* aplausos;
    SAMPLE* victory;
    SAMPLE* gameover;

    SAMPLE* themeSong;
    SAMPLE* optionsSong;
    SAMPLE* gameSong1;

    ///-----------------------
    ///BITMAP POINTERS
    ///-----------------------
    BITMAP* cursor;
    BITMAP* cursorConstrucao;
    BITMAP* cursorDemolicao;

    BITMAP* mainBG;
    BITMAP* optionsBG;
    BITMAP* gameBG;

    BITMAP* logo;
    BITMAP* optionstitle;
    BITMAP* volumeOn;
    BITMAP* volumeOff;
    BITMAP* blueWindow;
    BITMAP* typingSpace;

    BITMAP* barraSuperior;
    BITMAP* matriz;
    BITMAP* selectGrade;
    BITMAP* janelaCampanhas;
    BITMAP* janelaConstrutor;
    BITMAP* janelaViaturas;
    BITMAP* janelaPequena;
    BITMAP* cashDisplay;
    BITMAP* messageBoard;

    BITMAP* mainMenuPlay;
    BITMAP* mainMenuOptions;
    BITMAP* mainMenuExit;
    BITMAP* mainMenuHighlight;
    BITMAP* optionsMenuArrow;
    BITMAP* optionsMenuArrowHighlight;
    BITMAP* optionsMenuMinus;
    BITMAP* optionsMenuMinusHighlight;
    BITMAP* optionsMenuPlus;
    BITMAP* optionsMenuPlusHighlight;
    BITMAP* optionsMenuWindowType;
    BITMAP* optionsMenuWindowTypeHighlight;
    BITMAP* playMenuNewGame;
    BITMAP* playMenuLoadGame;
    BITMAP* playMenuHighlight;
    BITMAP* close_x;
    BITMAP* close_x_highlight;

    BITMAP* backArrow;
    BITMAP* backArrowON;
    BITMAP* save;
    BITMAP* saveON;
    BITMAP* info;
    BITMAP* infoON;
    BITMAP* help;
    BITMAP* helpON;
    BITMAP* skipWeek;
    BITMAP* skipWeekON;
    BITMAP* build_house;
    BITMAP* build_water;
    BITMAP* build_forest;
    BITMAP* build_street;
    BITMAP* buy_ambulance;
    BITMAP* buy_policecar;
    BITMAP* buy_firetruck;
    BITMAP* vehicle_info;
    BITMAP* vehicle_infoON;
    BITMAP* botaoDestrutor;
    BITMAP* botaoDestrutorON;
    BITMAP* campaign_ambulance;
    BITMAP* campaign_policemen;
    BITMAP* campaign_fireman;
    BITMAP* campaign_taxes;
    BITMAP* campaign_invest;
    BITMAP* campaign_promisse;
    BITMAP* campaign_advertisement;
    BITMAP* buttonHighlight;
    BITMAP* button2_ok;
    BITMAP* button2_accept;
    BITMAP* button2_buy;
    BITMAP* button2_cancel;
    BITMAP* button2_highlight;

    BITMAP* tile_casa;
    BITMAP* tile_construcao;
    BITMAP* tile_terra;
    BITMAP* tile_floresta;
    BITMAP* tile_inexplorado;
    BITMAP* tile_rua;
    BITMAP* tile_destruicao;
    BITMAP* anim_tile_agua;
    BITMAP* desastre_mst;
    BITMAP* desastre_homicidio;
    BITMAP* anim_desastre_alien;
    BITMAP* anim_desastre_provaIP;
    BITMAP* anim_desastre_meteoro;
    BITMAP* anim_desastre_assalto;
    BITMAP* anim_desastre_chacina;
    BITMAP* anim_desastre_enchente;
    BITMAP* anim_desastre_incendio;

void LoadDefaultContent()
{

    ///-------------------------
    ///FONTS
    ///-------------------------
    textfont = load_font("Fontes/nomes.PCX",NULL,NULL);
    window_title = load_font("Fontes/newload.PCX",NULL,NULL);
    sizeChoiceHighlight = load_font("Fontes/sizeChoiceHighlight.PCX", NULL, NULL);
    sizeChoiceButton = load_font("Fontes/sizeChoiceButton.PCX", NULL, NULL);
    play_button = load_font("Fontes/play.PCX",NULL,NULL);
    optionsFont1 = load_font("Fontes/options1.PCX",NULL,NULL);
    optionsFont2 = load_font("Fontes/options2.PCX",NULL,NULL);
    optionsFont = load_font("Fontes/windowed.PCX",NULL,NULL);
    display_cash = load_font("Fontes/cash.PCX",NULL,NULL);
    display_cityName = load_font("Fontes/nomeCidade.PCX",NULL,NULL);
    display_Paineis = load_font("Fontes/paineis.PCX",NULL,NULL);
    display_weeksleft = load_font("Fontes/showWeeks.PCX",NULL,NULL);
    display_costsubs = load_font("Fontes/legendaDinheiro.PCX",NULL,NULL);
    display_victory = load_font("Fontes/parabens.PCX",NULL,NULL);
    display_message_board = load_font("Fontes/textmsg.PCX",NULL,NULL);


    ///------------------------
    ///SAMPLES
    ///------------------------

    //Sound Effects
    click = load_sample("Sons/SOUNDEFFECTS/click.wav");
    trafego=load_sample("Sons/SOUNDEFFECTS/trafego.wav");

    //Songs
    themeSong = load_sample("Sons/MUSIC/mainmenu.wav");

    ///-----------------------
    ///BITMAPS
    ///-----------------------

    //Cursor
    cursor = load_bitmap("Sprites/CURSOR/general.bmp",NULL);

    //Backgrounds
    mainBG = load_bitmap("Sprites/BACKGROUND/mainmenu.bmp",NULL);


    //Objects
    logo = load_bitmap("Sprites/OBJECTS/MAINMENU/logo.bmp",NULL);
    blueWindow = load_bitmap("Sprites/OBJECTS/blue window.bmp",NULL);
    typingSpace = load_bitmap("Sprites/OBJECTS/typing space.bmp",NULL);

    //Buttons
    mainMenuPlay = load_bitmap("Sprites/BUTTON/MAINMENU/play.bmp",NULL);
    mainMenuOptions = load_bitmap("Sprites/BUTTON/MAINMENU/options.bmp",NULL);
    mainMenuExit = load_bitmap("Sprites/BUTTON/MAINMENU/exit.bmp",NULL);
    mainMenuHighlight = load_bitmap("Sprites/BUTTON/MAINMENU/highlight.bmp",NULL);
    playMenuNewGame = load_bitmap("Sprites/BUTTON/PLAYMENU/newgame.bmp",NULL);
    playMenuLoadGame = load_bitmap("Sprites/BUTTON/PLAYMENU/loadgame.bmp",NULL);
    playMenuHighlight = load_bitmap("Sprites/BUTTON/PLAYMENU/highlight.bmp",NULL);
    close_x = load_bitmap("Sprites/BUTTON/close.bmp",NULL);
    close_x_highlight = load_bitmap("Sprites/BUTTON/close_highlight.bmp",NULL);
}

void UnloadDefaultContent()
{
    ///-------------------------
    ///FONTS
    ///-------------------------
    destroy_font(textfont);
    destroy_font(window_title);
    destroy_font(sizeChoiceButton);
    destroy_font(sizeChoiceHighlight);
    destroy_font(play_button);
    destroy_font(optionsFont1);
    destroy_font(optionsFont2);
    destroy_font(optionsFont);
    destroy_font(display_cash);
    destroy_font(display_cityName);
    destroy_font(display_Paineis);
    destroy_font(display_weeksleft);
    destroy_font(display_costsubs);
    destroy_font(display_victory);
    destroy_font(display_message_board);

    ///------------------------
    ///SAMPLES
    ///------------------------

    //Sound Effects
    destroy_sample(click);
    destroy_sample(trafego);

    //Songs
    destroy_sample(themeSong);


    ///-----------------------
    ///BITMAPS
    ///-----------------------

    //Cursor
    destroy_bitmap(cursor);

    //Backgrounds
    destroy_bitmap(mainBG);

    //Objects
    destroy_bitmap(logo);
    destroy_bitmap(blueWindow);
    destroy_bitmap(typingSpace);

    //Buttons
    destroy_bitmap(mainMenuPlay);
    destroy_bitmap(mainMenuOptions);
    destroy_bitmap(mainMenuExit);
    destroy_bitmap(mainMenuHighlight);
    destroy_bitmap(playMenuNewGame);
    destroy_bitmap(playMenuLoadGame);
    destroy_bitmap(playMenuHighlight);
    destroy_bitmap(close_x);
    destroy_bitmap(close_x_highlight);
}

void LoadOptionsContent()
{
   optionsSong = load_sample("Sons/MUSIC/optionscreen.wav");

   optionsBG = load_bitmap("Sprites/BACKGROUND/options.bmp",NULL);
   optionstitle = load_bitmap("Sprites/OBJECTS/OPTIONS/title.bmp",NULL);
   volumeOn = load_bitmap("Sprites/OBJECTS/OPTIONS/volumeOn.bmp",NULL);
   volumeOff = load_bitmap("Sprites/OBJECTS/OPTIONS/volumeOff.bmp",NULL);
   optionsMenuArrow = load_bitmap("Sprites/BUTTON/OPTIONS/arrow.bmp",NULL);
   optionsMenuArrowHighlight = load_bitmap("Sprites/BUTTON/OPTIONS/arrow highlight.bmp",NULL);
   optionsMenuMinus = load_bitmap("Sprites/BUTTON/OPTIONS/minus.bmp",NULL);
   optionsMenuMinusHighlight = load_bitmap("Sprites/BUTTON/OPTIONS/minus highlight.bmp",NULL);
   optionsMenuPlus = load_bitmap("Sprites/BUTTON/OPTIONS/plus.bmp",NULL);
   optionsMenuPlusHighlight = load_bitmap("Sprites/BUTTON/OPTIONS/plus highlight.bmp",NULL);
   optionsMenuWindowType = load_bitmap("Sprites/BUTTON/OPTIONS/window type.bmp",NULL);
   optionsMenuWindowTypeHighlight = load_bitmap("Sprites/BUTTON/OPTIONS/window type highlight.bmp",NULL);
}

void UnloadOptionsContent()
{
   destroy_sample(optionsSong);

   destroy_bitmap(optionsBG);
   destroy_bitmap(optionstitle);
   destroy_bitmap(volumeOn);
   destroy_bitmap(volumeOff);
   destroy_bitmap(optionsMenuArrow);
   destroy_bitmap(optionsMenuArrowHighlight);
   destroy_bitmap(optionsMenuMinus);
   destroy_bitmap(optionsMenuMinusHighlight);
   destroy_bitmap(optionsMenuPlus);
   destroy_bitmap(optionsMenuPlusHighlight);
   destroy_bitmap(optionsMenuWindowType);
   destroy_bitmap(optionsMenuWindowTypeHighlight);
}

void LoadGameContent()
{
    ///-----------------------
    ///SAMPLES
    ///-----------------------
    invalid = load_sample("Sons/SOUNDEFFECTS/invalid.wav");
    registradora = load_sample("Sons/SOUNDEFFECTS/registradora.wav");
    demolition = load_sample("Sons/SOUNDEFFECTS/demolition.wav");
    ambulanceSample = load_sample("Sons/SOUNDEFFECTS/ambulanceSample.wav");
    policeradioSample = load_sample("Sons/SOUNDEFFECTS/policeradioSample.wav");
    firetruckSample = load_sample("Sons/SOUNDEFFECTS/firetruckSample.wav");
    aplausos = load_sample("Sons/SOUNDEFFECTS/aplausos.wav");
    victory = load_sample("Sons/SOUNDEFFECTS/victory.wav");
    gameover = load_sample("Sons/SOUNDEFFECTS/gameover.wav");

    gameSong1 = load_sample("Sons/MUSIC/gamescreen1.wav");

    ///-----------------------
    ///BITMAPS
    ///-----------------------

    //Background
    gameBG = load_bitmap("Sprites/BACKGROUND/gamescreen.bmp", NULL);

    //Cursors
    cursorDemolicao = load_bitmap("Sprites/CURSOR/demolish.bmp",NULL);
    cursorConstrucao = load_bitmap("Sprites/CURSOR/build.bmp",NULL);

    //Objects
    barraSuperior = load_bitmap("Sprites/OBJECTS/GAMESCREEN/barraSuperior.bmp",NULL);
    matriz = load_bitmap("Sprites/OBJECTS/GAMESCREEN/matriz.bmp",NULL);
    selectGrade = load_bitmap("Sprites/OBJECTS/GAMESCREEN/selectGrade.bmp",NULL);
    janelaCampanhas = load_bitmap("Sprites/OBJECTS/GAMESCREEN/janelaCampanhas.bmp",NULL);
    janelaConstrutor = load_bitmap("Sprites/OBJECTS/GAMESCREEN/janelaConstrutor.bmp",NULL);
    janelaViaturas = load_bitmap("Sprites/OBJECTS/GAMESCREEN/janelaViaturas.bmp",NULL);
    janelaPequena = load_bitmap("Sprites/OBJECTS/GAMESCREEN/janela.bmp",NULL);
    cashDisplay = load_bitmap("Sprites/OBJECTS/GAMESCREEN/cashDisplay.bmp",NULL);
    messageBoard = load_bitmap("Sprites/OBJECTS/GAMESCREEN/messageBoard.bmp",NULL);

    //Buttons
    backArrow = load_bitmap("Sprites/BUTTON/GAMESCREEN/backarrow.bmp",NULL);
    backArrowON = load_bitmap("Sprites/BUTTON/GAMESCREEN/backarrowON.bmp",NULL);
    save = load_bitmap("Sprites/BUTTON/GAMESCREEN/save.bmp",NULL);
    saveON = load_bitmap("Sprites/BUTTON/GAMESCREEN/saveON.bmp",NULL);
    info = load_bitmap("Sprites/BUTTON/GAMESCREEN/info.bmp",NULL);
    infoON = load_bitmap("Sprites/BUTTON/GAMESCREEN/infoON.bmp",NULL);
    help = load_bitmap("Sprites/BUTTON/GAMESCREEN/help.bmp",NULL);
    helpON = load_bitmap("Sprites/BUTTON/GAMESCREEN/helpON.bmp",NULL);
    skipWeek = load_bitmap("Sprites/BUTTON/GAMESCREEN/skipWeek.bmp",NULL);
    skipWeekON = load_bitmap("Sprites/BUTTON/GAMESCREEN/skipWeekON.bmp",NULL);
    build_house = load_bitmap("Sprites/BUTTON/GAMESCREEN/build_house.bmp",NULL);
    build_water = load_bitmap("Sprites/BUTTON/GAMESCREEN/build_water.bmp",NULL);
    build_forest = load_bitmap("Sprites/BUTTON/GAMESCREEN/build_forest.bmp",NULL);
    build_street = load_bitmap("Sprites/BUTTON/GAMESCREEN/build_street.bmp",NULL);
    buy_ambulance = load_bitmap("Sprites/BUTTON/GAMESCREEN/buy_ambulance.bmp",NULL);
    buy_policecar = load_bitmap("Sprites/BUTTON/GAMESCREEN/buy_policecar.bmp",NULL);
    buy_firetruck = load_bitmap("Sprites/BUTTON/GAMESCREEN/buy_firetruck.bmp",NULL);
    vehicle_info = load_bitmap("Sprites/BUTTON/GAMESCREEN/vehicle_info.bmp",NULL);
    vehicle_infoON = load_bitmap("Sprites/BUTTON/GAMESCREEN/vehicle_infoON.bmp",NULL);
    botaoDestrutor = load_bitmap("Sprites/BUTTON/GAMESCREEN/destrutor.bmp",NULL);
    botaoDestrutorON = load_bitmap("Sprites/BUTTON/GAMESCREEN/destrutorON.bmp",NULL);
    campaign_ambulance = load_bitmap("Sprites/BUTTON/GAMESCREEN/campaign_ambulance.bmp",NULL);
    campaign_policemen = load_bitmap("Sprites/BUTTON/GAMESCREEN/campaign_policemen.bmp",NULL);
    campaign_fireman = load_bitmap("Sprites/BUTTON/GAMESCREEN/campaign_fireman.bmp",NULL);
    campaign_taxes = load_bitmap("Sprites/BUTTON/GAMESCREEN/campaign_taxes.bmp",NULL);
    campaign_invest = load_bitmap("Sprites/BUTTON/GAMESCREEN/campaign_invest.bmp",NULL);
    campaign_promisse = load_bitmap("Sprites/BUTTON/GAMESCREEN/campaign_promisse.bmp",NULL);
    campaign_advertisement = load_bitmap("Sprites/BUTTON/GAMESCREEN/campaign_advertisement.bmp",NULL);
    buttonHighlight = load_bitmap("Sprites/BUTTON/GAMESCREEN/button highlight.bmp",NULL);
    button2_ok = load_bitmap("Sprites/BUTTON/GAMESCREEN/ok.bmp",NULL);
    button2_accept=load_bitmap("Sprites/BUTTON/GAMESCREEN/accept.bmp",NULL);
    button2_buy=load_bitmap("Sprites/BUTTON/GAMESCREEN/buy.bmp",NULL);
    button2_cancel= load_bitmap("Sprites/BUTTON/GAMESCREEN/cancel.bmp",NULL);
    button2_highlight = load_bitmap("Sprites/BUTTON/GAMESCREEN/button2 highlight.bmp",NULL);

    //Tiles
    tile_casa = load_bitmap("Sprites/TILES/TERRENOS/casa.bmp",NULL);
    tile_construcao = load_bitmap("Sprites/TILES/TERRENOS/construcao.bmp",NULL);
    tile_terra = load_bitmap("Sprites/TILES/TERRENOS/terra.bmp",NULL);
    tile_floresta = load_bitmap("Sprites/TILES/TERRENOS/floresta.bmp",NULL);
    tile_inexplorado = load_bitmap("Sprites/TILES/TERRENOS/inexplorado.bmp",NULL);
    tile_rua = load_bitmap("Sprites/TILES/TERRENOS/rua.bmp",NULL);
    tile_destruicao = load_bitmap("Sprites/TILES/TERRENOS/demolicao.bmp",NULL);
    anim_tile_agua = load_bitmap("Sprites/TILES/TERRENOS/agua.bmp",NULL);
    desastre_mst =load_bitmap("Sprites/TILES/DESASTRES/mst.bmp",NULL);
    desastre_homicidio = load_bitmap("Sprites/TILES/DESASTRES/homicidio.bmp",NULL);
    anim_desastre_alien = load_bitmap("Sprites/TILES/DESASTRES/alien.bmp",NULL);
    anim_desastre_provaIP = load_bitmap("Sprites/TILES/DESASTRES/provaIP.bmp",NULL);
    anim_desastre_meteoro = load_bitmap("Sprites/TILES/DESASTRES/meteoro.bmp",NULL);
    anim_desastre_assalto = load_bitmap("Sprites/TILES/DESASTRES/assalto.bmp",NULL);
    anim_desastre_chacina = load_bitmap("Sprites/TILES/DESASTRES/chacina.bmp",NULL);
    anim_desastre_enchente = load_bitmap("Sprites/TILES/DESASTRES/enchente.bmp",NULL);
    anim_desastre_incendio = load_bitmap("Sprites/TILES/DESASTRES/fogo.bmp",NULL);

}

void UnloadGameContent()
{
    ///-----------------------
    ///SAMPLES
    ///-----------------------
    destroy_sample(invalid);
    destroy_sample(registradora);
    destroy_sample(demolition);
    destroy_sample(ambulanceSample);
    destroy_sample(policeradioSample);
    destroy_sample(firetruckSample);
    destroy_sample(aplausos);
    destroy_sample(victory);
    destroy_sample(gameover);

    destroy_sample(gameSong1);

    ///-----------------------
    ///BITMAPS
    ///-----------------------

    //Background
    destroy_bitmap(gameBG);

    //Cursors
    destroy_bitmap(cursorDemolicao);
    destroy_bitmap(cursorConstrucao);

    //Objects

    destroy_bitmap(barraSuperior);
    destroy_bitmap(matriz);
    destroy_bitmap(selectGrade);
    destroy_bitmap(janelaCampanhas);
    destroy_bitmap(janelaConstrutor);
    destroy_bitmap(janelaViaturas);
    destroy_bitmap(janelaPequena);
    destroy_bitmap(cashDisplay);
    destroy_bitmap(messageBoard);

    //Buttons
    destroy_bitmap(backArrow);
    destroy_bitmap(backArrowON);
    destroy_bitmap(save);
    destroy_bitmap(saveON);
    destroy_bitmap(info);
    destroy_bitmap(infoON);
    destroy_bitmap(help);
    destroy_bitmap(helpON);
    destroy_bitmap(skipWeek);
    destroy_bitmap(skipWeekON);
    destroy_bitmap(build_house);
    destroy_bitmap(build_water);
    destroy_bitmap(build_forest);
    destroy_bitmap(build_street);
    destroy_bitmap(buy_ambulance);
    destroy_bitmap(buy_policecar);
    destroy_bitmap(buy_firetruck);
    destroy_bitmap(vehicle_info);
    destroy_bitmap(vehicle_infoON);
    destroy_bitmap(botaoDestrutor);
    destroy_bitmap(botaoDestrutorON);
    destroy_bitmap(campaign_ambulance);
    destroy_bitmap(campaign_policemen);
    destroy_bitmap(campaign_fireman);
    destroy_bitmap(campaign_taxes);
    destroy_bitmap(campaign_invest);
    destroy_bitmap(campaign_promisse);
    destroy_bitmap(campaign_advertisement);
    destroy_bitmap(buttonHighlight);
    destroy_bitmap(button2_ok);
    destroy_bitmap(button2_accept);
    destroy_bitmap(button2_buy);
    destroy_bitmap(button2_cancel);
    destroy_bitmap(button2_highlight);

    //Tiles
    destroy_bitmap(tile_casa);
    destroy_bitmap(tile_construcao);
    destroy_bitmap(tile_terra);
    destroy_bitmap(tile_floresta);
    destroy_bitmap(tile_inexplorado);
    destroy_bitmap(tile_rua);
    destroy_bitmap(tile_destruicao);
    destroy_bitmap(anim_tile_agua);
    destroy_bitmap(desastre_mst);
    destroy_bitmap(desastre_homicidio);
    destroy_bitmap(anim_desastre_alien);
    destroy_bitmap(anim_desastre_provaIP);
    destroy_bitmap(anim_desastre_meteoro);
    destroy_bitmap(anim_desastre_assalto);
    destroy_bitmap(anim_desastre_chacina);
    destroy_bitmap(anim_desastre_enchente);
    destroy_bitmap(anim_desastre_incendio);
}
