#include "content.hpp"

Content* c;

///====================================================
///DEFAULT
///====================================================
Content* create_content()
{
    Content* c = new Content;

    c->datafile_menu = NULL;
    c->datafile_fonts = NULL;
    c->datafile_graphics = NULL;
    c->datafile_music = NULL;
    c->datafile_sfx = NULL;

    ///BITMAPS
    packfile_password("D0C6N05887");
    c->datafile_menu = load_datafile("Data/menu.dat");

    if(!c->datafile_menu)
    {
      allegro_message("Error. 'menu.dat' is missing.");
      return NULL;
    }
    packfile_password(NULL);

    c->main_BG = (BITMAP*) c->datafile_menu[MAIN_BACKGROUND].dat;
    c->main_logo = (BITMAP*) c->datafile_menu[MAIN_LOGO].dat;
    c->main_arrow = (BITMAP*) c->datafile_menu[MAIN_ARROW].dat;
    c->main_selection = NULL; c->main_selection = create_bitmap(SCREEN_W, 35); clear_to_color(c->main_selection, makecol(255,255,255));

    ///SONGS
    packfile_password("D0C6N05887");
    c->datafile_music = load_datafile("Data/music.dat");
    if(!c->datafile_music)
    {
      allegro_message("Error. 'music.dat' is missing.");
      return NULL;
    }
    packfile_password(NULL);
    c->SONG_mainmenu = (MIDI*) c->datafile_music[SONG_MAINMENU].dat;
    c->soundtrack[0] = (MIDI*) c->datafile_music[SOUNDTRACK_0].dat;
    c->soundtrack[1] = (MIDI*) c->datafile_music[SOUNDTRACK_1].dat;
    c->soundtrack[2] = (MIDI*) c->datafile_music[SOUNDTRACK_2].dat;
    c->soundtrack[3] = (MIDI*) c->datafile_music[SOUNDTRACK_3].dat;
    c->soundtrack[4] = (MIDI*) c->datafile_music[SOUNDTRACK_4].dat;
    c->soundtrack[5] = (MIDI*) c->datafile_music[SOUNDTRACK_5].dat;
    c->soundtrack[6] = (MIDI*) c->datafile_music[SOUNDTRACK_6].dat;
    c->soundtrack[7] = (MIDI*) c->datafile_music[SOUNDTRACK_7].dat;
    c->soundtrack[8] = (MIDI*) c->datafile_music[SOUNDTRACK_8].dat;
    c->soundtrack[9] = (MIDI*) c->datafile_music[SOUNDTRACK_9].dat;
    c->soundtrack[10] = (MIDI*) c->datafile_music[SOUNDTRACK_10].dat;
    c->soundtrack[11] = (MIDI*) c->datafile_music[SOUNDTRACK_11].dat;

    ///SFX
    packfile_password("D0C6N05887");
    c->datafile_sfx = load_datafile("Data/sfx.dat");
    if(!c->datafile_menu)
    {
      allegro_message("Error. 'sfx.dat' is missing.");
      return NULL;
    }
    packfile_password(NULL);
    c->FX_click1 = (SAMPLE*) c->datafile_sfx[SFX_CLICK1].dat;
    c->FX_click2 = (SAMPLE*) c->datafile_sfx[SFX_CLICK2].dat;
    c->FX_click3 = (SAMPLE*) c->datafile_sfx[SFX_CLICK3].dat;
    c->FX_click4 = (SAMPLE*) c->datafile_sfx[SFX_CLICK4].dat;
    c->FX_transition = (SAMPLE*) c->datafile_sfx[SFX_TRANSITION].dat;
    c->FX_pause = (SAMPLE*) c->datafile_sfx[SFX_PAUSE].dat;
    c->FX_tiro_lv0 = (SAMPLE*) c->datafile_sfx[SFX_TIRO_LV0].dat;
    c->FX_tiro_lv1 = (SAMPLE*) c->datafile_sfx[SFX_TIRO_LV1].dat;
    c->FX_tiro_lv2 = (SAMPLE*) c->datafile_sfx[SFX_TIRO_LV2].dat;
    c->FX_tiro_A = (SAMPLE*) c->datafile_sfx[SFX_TIRO_A].dat;
    c->FX_tiro_E = (SAMPLE*) c->datafile_sfx[SFX_TIRO_E].dat;
    c->FX_warning_F = (SAMPLE*) c->datafile_sfx[SFX_WARNING_F].dat;
    c->FX_powerup = (SAMPLE*) c->datafile_sfx[SFX_POWERUP].dat;
    c->FX_explosao_small = (SAMPLE*) c->datafile_sfx[SFX_EXPLOSAO_SMALL].dat;
    c->FX_explosao_medium = (SAMPLE*) c->datafile_sfx[SFX_EXPLOSAO_MEDIUM].dat;
    c->FX_explosao_large = (SAMPLE*) c->datafile_sfx[SFX_EXPLOSAO_LARGE].dat;
    c->FX_explosao_shield = (SAMPLE*) c->datafile_sfx[SFX_EXPLOSAO_SHIELD].dat;
    c->FX_barreira = (SAMPLE*) c->datafile_sfx[SFX_BARREIRA].dat;
    c->FX_charging = (SAMPLE*) c->datafile_sfx[SFX_CHARGING].dat;
    c->FX_fullcharge = (SAMPLE*) c->datafile_sfx[SFX_FULLCHARGE].dat;
    c->VOICE_gameover = (SAMPLE*) c->datafile_sfx[VOICE_GAMEOVER].dat;
    c->VOICE_ready = (SAMPLE*) c->datafile_sfx[VOICE_READY].dat;
    c->VOICE_go = (SAMPLE*) c->datafile_sfx[VOICE_GO].dat;

    ///FONTES
    packfile_password("D0C6N05887");
    c->datafile_fonts = load_datafile("Data/fonts.dat");
    if(!c->datafile_menu)
    {
      allegro_message("Error. 'fonts.dat' is missing.");
      return NULL;
    }
    packfile_password(NULL);
    c->font_title_options = (FONT*) c->datafile_fonts[FONT_TITLE_OPTIONS].dat;
    c->font_help = (FONT*) c->datafile_fonts[FONT_HELP].dat;
    c->font_options = (FONT*) c->datafile_fonts[FONT_OPTIONS].dat;
    c->font_pause = (FONT*) c->datafile_fonts[FONT_PAUSE].dat;
    c->font_score = (FONT*) c->datafile_fonts[FONT_SCORE].dat;
    c->font_shield = (FONT*) c->datafile_fonts[FONT_SHIELD].dat;
    c->font_time = (FONT*) c->datafile_fonts[FONT_TIME].dat;
    c->font_highscores = (FONT*) c->datafile_fonts[FONT_HIGHSCORES].dat;
    c->font_ready = (FONT*) c->datafile_fonts[FONT_READY].dat;

    return c;
}

void destroy_content(Content* c)
{
    ///BITMAPS
   if(!c->datafile_menu)
    unload_datafile(c->datafile_menu);
   if(!c->main_selection)
    destroy_bitmap(c->main_selection);

   ///SONGS
   if(!c->datafile_music)
    unload_datafile(c->datafile_music);

   ///SFX
   if(!c->datafile_sfx)
    unload_datafile(c->datafile_sfx);

   ///FONTES
   if(!c->datafile_fonts)
    unload_datafile(c->datafile_fonts);

   delete c;
}


///====================================================
///GAMESCREEN
///====================================================
int Load_Gamescreen_Content(Content* c)
{
    packfile_password("D0C6N05887");
    c->datafile_graphics = load_datafile("Data/graphics.dat");
    if(!c->datafile_graphics)
    {
      allegro_message("Error. 'graphics.dat' is missing.");
      return NULL;
    }
    packfile_password(NULL);

    c->pause_window = (BITMAP*) c->datafile_graphics[GS_PAUSE_WINDOW].dat;
    c->pause_b_mainmenu = (BITMAP*) c->datafile_graphics[GS_PAUSE_B_MAINMENU].dat;
    c->pause_b_resume = (BITMAP*) c->datafile_graphics[GS_PAUSE_B_RESUME].dat;
    c->pause_b_h = (BITMAP*) c->datafile_graphics[GS_PAUSE_B_H].dat;
    c->game_timebar = (BITMAP*) c->datafile_graphics[GS_GAME_TIMEBAR].dat;
    c->game_nave = (BITMAP*) c->datafile_graphics[GS_GAME_NAVE].dat;
    c->game_imortal = (BITMAP*) c->datafile_graphics[GS_GAME_IMORTAL].dat;
    c->game_barreira = (BITMAP*) c->datafile_graphics[GS_GAME_BARREIRA].dat;
    c->game_life_counter = (BITMAP*) c->datafile_graphics[GS_GAME_LIFE_COUNTER].dat;
    c->game_charging1 = (BITMAP*) c->datafile_graphics[GS_GAME_CHARGING1].dat;
    c->game_charging2 = (BITMAP*) c->datafile_graphics[GS_GAME_CHARGING2].dat;
    c->game_shot_lv0 = (BITMAP*) c->datafile_graphics[GS_GAME_SHOT_LV0].dat;
    c->game_shot_lv1 = (BITMAP*) c->datafile_graphics[GS_GAME_SHOT_LV1].dat;
    c->game_shot_lv2 = (BITMAP*) c->datafile_graphics[GS_GAME_SHOT_LV2].dat;
    c->game_shield_bar = (BITMAP*) c->datafile_graphics[GS_GAME_SHIELD_BAR].dat;
    c->game_shield_bar_pts = (BITMAP*) c->datafile_graphics[GS_GAME_SHIELD_BAR_PTS].dat;
    c->game_enemyA = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_A].dat;
    c->game_enemyA_tiro = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_A_TIRO].dat;
    c->game_enemyB = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_B].dat;
    c->game_enemyB_dano = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_B_DANO].dat;
    c->game_enemyB_tiro = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_B_TIRO].dat;
    c->game_enemyC = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_C].dat;
    c->game_enemyC_dano = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_C_DANO].dat;
    c->game_enemyC_tiro = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_C_TIRO].dat;
    c->game_enemyD = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_D].dat;
    c->game_enemyD_dano = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_D_DANO].dat;
    c->game_enemyD_tiro = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_D_TIRO].dat;
    c->game_enemyE = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_E].dat;
    c->game_enemyE_dano = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_E_DANO].dat;
    c->game_enemyE_tiro = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_E_TIRO].dat;
    c->game_enemyF = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_F].dat;
    c->game_enemyF_dano = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_F_DANO].dat;
    c->game_enemyF_warning = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_F_WARNING].dat;
    c->game_enemyF_tiro = (BITMAP*) c->datafile_graphics[GS_GAME_ENEMY_F_TIRO].dat;
    c->game_teleport = (BITMAP*) c->datafile_graphics[GS_GAME_TELEPORT].dat;
    c->game_gameover_msg  = (BITMAP*) c->datafile_graphics[GS_GAME_GAMEOVER_MSG].dat;
    c->game_powerup_extra_life = (BITMAP*) c->datafile_graphics[GS_GAME_POWERUP_EXTRA_LIFE].dat;
    c->game_powerup_shield_recharge = (BITMAP*) c->datafile_graphics[GS_GAME_POWERUP_SHIELD_RECHARGE].dat;
    c->game_powerup_speed_boost = (BITMAP*) c->datafile_graphics[GS_GAME_POWERUP_SPEED_BOOST].dat;
    c->game_explosion_small = (BITMAP*) c->datafile_graphics[GS_GAME_EXPLOSION_SMALL].dat;
    c->game_explosion_medium = (BITMAP*) c->datafile_graphics[GS_GAME_EXPLOSION_MEDIUM].dat;
    c->game_explosion_large = (BITMAP*) c->datafile_graphics[GS_GAME_EXPLOSION_LARGE].dat;
    c->game_explosion_shield = (BITMAP*) c->datafile_graphics[GS_GAME_EXPLOSION_SHIELD].dat;
    c->game_BG[0] = (BITMAP*) c->datafile_graphics[GS_GAME_BG_0].dat;
    c->game_BG[1] = (BITMAP*) c->datafile_graphics[GS_GAME_BG_1].dat;
    c->game_BG[2] = (BITMAP*) c->datafile_graphics[GS_GAME_BG_2].dat;
    c->game_BG[3] = (BITMAP*) c->datafile_graphics[GS_GAME_BG_3].dat;
    c->game_planetas[0] = (BITMAP*) c->datafile_graphics[GS_GAME_PLANETAS_0].dat;
    c->game_planetas[1] = (BITMAP*) c->datafile_graphics[GS_GAME_PLANETAS_1].dat;
    c->game_planetas[2] = (BITMAP*) c->datafile_graphics[GS_GAME_PLANETAS_2].dat;
    c->game_planetas[3] = (BITMAP*) c->datafile_graphics[GS_GAME_PLANETAS_3].dat;
    c->game_planetas[4] = (BITMAP*) c->datafile_graphics[GS_GAME_PLANETAS_4].dat;

    return 1;
}

void Unload_Gamescreen_Content(Content* c)
{
    unload_datafile(c->datafile_graphics);
}

