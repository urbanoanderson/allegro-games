#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include "init.h"

#define TILES_I 13
#define TILES_J 19

#define MAP_X0 0
#define MAP_Y0 100

#define TILESIZE 50

enum TILE_ID { GRASS = 0, BRICK = 1, BLOCK = 2, WALL = 3, INVISIBLE_BLOCK = 4 };

class Tilemap
{
    private:
        int matriz[TILES_I][TILES_J];
        bool matbombas[TILES_I][TILES_J];
        bool matenemies[TILES_I][TILES_J];
        int portalI, portalJ;

    public:
        Tilemap() { }
        void Initialize(FILE* f, int portalI, int portalJ);
        int GetTileID(int i, int j) { return matriz[i][j]; }
        int GetBombPos(int i, int j) { return matbombas[i][j]; }
        void SetBombPos(int i, int j, bool value) { matbombas[i][j] = value; }
        int GetEnemyPos(int i, int j) { return matenemies[i][j]; }
        void SetEnemyPos(int i, int j, bool value) { matenemies[i][j] = value; }
        int GetPortalI() { return portalI; }
        int GetPortalJ() { return portalJ; }
        void SetTileID(int i, int j, int ID) { matriz[i][j] = ID; }
        void Draw();
        bool IsPathBlocked(int i, int j) { return ( (GetTileID(i, j) != GRASS) || (GetBombPos(i,j) == 1) || (GetEnemyPos(i,j) == 1) ); }
        //bool IsPathBlocked(int i, int j) { return ( (GetTileID(i, j) != GRASS) || (GetBombPos(i,j) == 1) ); }
};

#endif // TILEMAP_H_INCLUDED
