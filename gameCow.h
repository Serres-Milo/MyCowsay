#ifndef __GAME_COW_H__
#define __GAME_COW_H__

#include <termios.h>

typedef struct {
    int coordH;
    int coordW;
} CoordCouple;


char** initMap(void);
void freeMap(char **map);
int nbWallAdj(char **map, int coordH, int coordW);
void generateMap(char **map);
int bRand(int bInf, int bSup);
void initGame(char **map, CoordCouple* coordInit);
void coordFloorAdj(char **map, CoordCouple *tabRes, int coordH, int coordW);
int messageIsAccessible(char **map, int cow_coordH, int cow_coordW, int mess_coordH, int mess_coordW);
int isEndGame(CoordCouple coordMess, CoordCouple coordCowAct, char keyAct);
void initTerm(struct termios *oldTerm);
void restoreTerm(struct termios *oldTerm);
void displayMapAroundCow(char **map, int **crushedGrass, CoordCouple coordCowint, int visibleRadiusHeight, int visibleRadiusWidth);

void displayAllMap(char **map, int **crushedGrass);

void gameCow(char* cowMessage, bool isDevMode);


#endif

