#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
// #include <fcntl.h>
// #include <sys/time.h>

#include "gameCow.h"
#include "color.h"
#include "wildcow.h"

#define WIDTH_MAP 102
#define HEIGHT_MAP 52

char** initMap(void) {
    char **map = NULL;
    map = malloc(HEIGHT_MAP*sizeof(char*));
    if (map == NULL) exit(1);
    for (int i=0; i<HEIGHT_MAP; i++) {
        map[i] = malloc(WIDTH_MAP*sizeof(char));
        if (map[i] == NULL) exit(1);
    }
    return map;
}

void freeMap(char **map) {
    for (int i=0; i<HEIGHT_MAP; i++) {
        free(map[i]);
    }
    free(map);
}

int nbWallAdj(char **map, int coordH, int coordW) {
    int res = 0;
    for (int y=coordH-1; y<=coordH+1; y++) {
        for (int x=coordW-1; x<=coordW+1; x++) {
            if (map[y][x] == '#')
                res++;
        }
    }


    // decrement the current cell if necessary
    if (map[coordH][coordW] == '#')
        res--;

    return res;
}


void generateMap(char **map) {
    // border creation
    map[0][0] = ' ';
    map[0][WIDTH_MAP-1] = ' ';
    map[HEIGHT_MAP-1][0] = '\\';
    map[HEIGHT_MAP-1][WIDTH_MAP-1] = '/';
    for (int x=1; x<WIDTH_MAP-1; x++) {
        map[0][x] = '_';
        map[HEIGHT_MAP-1][x] = '_';
    }
    for (int y=1; y<HEIGHT_MAP-1; y++) {
        map[y][0] = '|';
        map[y][WIDTH_MAP-1] = '|';
    }


    // rough map creation
    for (int coordH=1; coordH<HEIGHT_MAP-1; coordH++) {
        for (int coordW=1; coordW<WIDTH_MAP-1; coordW++) {
            if (rand()%5 == 0) {
                map[coordH][coordW] = '#';
            } else {
                map[coordH][coordW] = '.';
            }
        }
    }


    // wall blocks creation
    for (int i=0; i<4; i++) {
        char **mapTemp = initMap();
        for (int coordH=0; coordH<HEIGHT_MAP; coordH++) {
            for (int coordW=0; coordW<WIDTH_MAP; coordW++) {
                mapTemp[coordH][coordW] = map[coordH][coordW];
            }
        }

        for (int coordH=1; coordH<HEIGHT_MAP-1; coordH++) {
            for (int coordW=1; coordW<WIDTH_MAP-1; coordW++) {
                if (map[coordH][coordW] != '|'
                    && map[coordH][coordW] != '-'
                    && map[coordH][coordW] != '_'
                    && map[coordH][coordW] != '\\'
                    && map[coordH][coordW] != '/'
                    && map[coordH][coordW] != ' ')
                {
                        if (nbWallAdj(mapTemp, coordH, coordW) >= 3) {
                            map[coordH][coordW] = '#';
                        } else {
                            map[coordH][coordW] = '.';
                        }
                }
            }
        }

        freeMap(mapTemp);
    }

    // final smoothing
    for (int i=0; i<10; i++) {
        char **mapTemp = initMap();
        for (int coordH=0; coordH<HEIGHT_MAP; coordH++) {
            for (int coordW=0; coordW<WIDTH_MAP; coordW++) {
                mapTemp[coordH][coordW] = map[coordH][coordW];
            }
        }

        for (int coordH=1; coordH<HEIGHT_MAP-1; coordH++) {
            for (int coordW=1; coordW<WIDTH_MAP-1; coordW++) {
                if (map[coordH][coordW] != '|'
                    && map[coordH][coordW] != '-'
                    && map[coordH][coordW] != '_'
                    && map[coordH][coordW] != '\\'
                    && map[coordH][coordW] != '/'
                    && map[coordH][coordW] != ' ')
                {
                        if (map[coordH][coordW] == '.' && (nbWallAdj(mapTemp, coordH, coordW) >= 6)) {
                            map[coordH][coordW] = '#';
                        }
                }
            }
        }

        freeMap(mapTemp);
    }
}

int bRand(int bInf, int bSup) {
    return bInf + rand() % (bSup - bInf +1);
}

void initGame(char **map, CoordCouple* coordInit) {
    CoordCouple cowCoord, messCoord;
    do {
        cowCoord.coordH = bRand(1,HEIGHT_MAP-1);
        cowCoord.coordW = bRand(1,WIDTH_MAP-1);
        messCoord.coordH = bRand(1,HEIGHT_MAP-1);
        messCoord.coordW = bRand(1,WIDTH_MAP-1);
    } while ((cowCoord.coordH == messCoord.coordH && cowCoord.coordW == messCoord.coordW)   // different coordinates between the two
             || map[cowCoord.coordH][cowCoord.coordW] != '.'      // cow on an empty tile
             || map[messCoord.coordH][messCoord.coordW] != '.'    // message on an empty tile
             || (sqrt((cowCoord.coordH-messCoord.coordH)*(cowCoord.coordH-messCoord.coordH) +       // distance between the two is greater than the threshold
                      (cowCoord.coordW-messCoord.coordW)*(cowCoord.coordW-messCoord.coordW))
                 < (0.4 * sqrt(WIDTH_MAP*WIDTH_MAP + HEIGHT_MAP*HEIGHT_MAP)))
             || ! messageIsAccessible(map, cowCoord.coordH, cowCoord.coordW, messCoord.coordH, messCoord.coordW)      // message is accessible
    );

    map[cowCoord.coordH][cowCoord.coordW] = '@';
    map[messCoord.coordH][messCoord.coordW] = '$';

    coordInit[0] = cowCoord;
    coordInit[1] = messCoord;
}




void coordFloorAdj(char **map, CoordCouple *tabRes, int coordH, int coordW) {
    // bottom
    if (map[coordH+1][coordW] == '.') {
        tabRes[0].coordH = coordH+1;
        tabRes[0].coordW = coordW;
    } else {
        tabRes[0].coordH = -1;
    }
    // top
    if (map[coordH-1][coordW] == '.') {
        tabRes[1].coordH = coordH-1;
        tabRes[1].coordW = coordW;
    } else {
        tabRes[1].coordH = -1;
    }
    // right
    if (map[coordH][coordW+1] == '.') {
        tabRes[2].coordH = coordH;
        tabRes[2].coordW = coordW+1;
    } else {
        tabRes[2].coordH = -1;
    }
    // left
    if (map[coordH][coordW-1] == '.') {
        tabRes[3].coordH = coordH;
        tabRes[3].coordW = coordW-1;
    } else {
        tabRes[3].coordH = -1;
    }
}


int messageIsAccessible(char **map, int cow_coordH, int cow_coordW, int mess_coordH, int mess_coordW) {   // parcours en largeur (BFS)
    int lenTab = HEIGHT_MAP*WIDTH_MAP;
    CoordCouple *floorAdjViewed = NULL;     // FiFo tab (circular buffer)
    floorAdjViewed = malloc(lenTab*sizeof(CoordCouple));
    if (floorAdjViewed == NULL) exit(1);

    int **tilesAlreadyVisited = NULL;
    tilesAlreadyVisited = malloc(HEIGHT_MAP*sizeof(int*));
    if (tilesAlreadyVisited == NULL) exit(1);
    for (int h=0; h<HEIGHT_MAP; h++) {
        tilesAlreadyVisited[h] = malloc(WIDTH_MAP*sizeof(int));
        if (tilesAlreadyVisited[h] == NULL) exit(1);
        for (int w=0; w<WIDTH_MAP; w++) {
            tilesAlreadyVisited[h][w] = 0;
        }
    }

    floorAdjViewed[0].coordH = cow_coordH;  // init
    floorAdjViewed[0].coordW = cow_coordW;
    tilesAlreadyVisited[cow_coordH][cow_coordW] = 1;
    int head = 0;
    int tail = 1;
    CoordCouple actCoordFloorAdj[4];

    while (head != tail) {
        if (floorAdjViewed[head].coordH == mess_coordH && floorAdjViewed[head].coordW == mess_coordW) {
            free(floorAdjViewed);
            for (int i=0; i<HEIGHT_MAP; i++) {
                free(tilesAlreadyVisited[i]);
            }
            free(tilesAlreadyVisited);
            return 1;   // message found
        }
        coordFloorAdj(map, actCoordFloorAdj, floorAdjViewed[head].coordH, floorAdjViewed[head].coordW);
        for (int i=0; i<4; i++) {
            if (actCoordFloorAdj[i].coordH > -1
                && tilesAlreadyVisited[actCoordFloorAdj[i].coordH][actCoordFloorAdj[i].coordW] == 0) {
                floorAdjViewed[tail] = actCoordFloorAdj[i];
                tail = (tail+1)%lenTab;
                tilesAlreadyVisited[actCoordFloorAdj[i].coordH][actCoordFloorAdj[i].coordW] = 1;
            }
        }
        head = (head+1)%lenTab;


    }

    free(floorAdjViewed);
    for (int i=0; i<HEIGHT_MAP; i++) {
        free(tilesAlreadyVisited[i]);
    }
    free(tilesAlreadyVisited);
    return 0;   // message not accessible

}



int isEndGame(CoordCouple coordCowAct, CoordCouple coordMess, char keyAct) {
    if ((coordCowAct.coordH+1 == coordMess.coordH && coordCowAct.coordW == coordMess.coordW)
        || (coordCowAct.coordH-1 == coordMess.coordH && coordCowAct.coordW == coordMess.coordW)
        || (coordCowAct.coordH == coordMess.coordH && coordCowAct.coordW+1 == coordMess.coordW)
        || (coordCowAct.coordH == coordMess.coordH && coordCowAct.coordW-1 == coordMess.coordW)
        ) {
        return 1;
    } else if (keyAct == 'E' || keyAct == 'e') {
        return 2;
    } else {
        return 0;
    }
}

void initTerm(struct termios *oldTerm) {
    if (tcgetattr(STDIN_FILENO, oldTerm) == -1) exit(1);

    struct termios newTerm = *oldTerm;
    newTerm.c_lflag &= ~(ICANON | ECHO);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &newTerm) == -1) exit(1);

    /*
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    if (flags == -1) exit(1);
    flags |= O_NONBLOCK;

    if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1) exit(1);
    */
}

void restoreTerm(struct termios *oldTerm) {
    if (tcsetattr(STDIN_FILENO, TCSANOW, oldTerm) == -1) exit(1);

    /*
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    if (flags == -1) exit(1);
    flags &= ~O_NONBLOCK;
    if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1) exit(1);
    */
}


void displayMapAroundCow(char **map, int **crushedGrass, CoordCouple coordCow, int visibleRadiusHeight, int visibleRadiusWidth) {
    int start_coordH = coordCow.coordH - visibleRadiusHeight;
    int end_coordH = coordCow.coordH + visibleRadiusHeight;
    int start_coordW = coordCow.coordW - visibleRadiusWidth;
    int end_coordW = coordCow.coordW + visibleRadiusWidth;

    if (start_coordH < 0) start_coordH = 0;
    if (end_coordH >= HEIGHT_MAP) end_coordH = HEIGHT_MAP-1;
    if (start_coordW < 0) start_coordW = 0;
    if (end_coordW >= WIDTH_MAP) end_coordW = WIDTH_MAP-1;

    for (int coordH=start_coordH; coordH<=end_coordH; coordH++) {
        for (int coordW=start_coordW; coordW<=end_coordW; coordW++) {
            if (map[coordH][coordW] == '#') {           // walls
                EXTENDED_COLOR_TEXT(94)
                printf("#" RESET);
            } else if (map[coordH][coordW] == '.') {    // floor
                if (crushedGrass[coordH][coordW] == 1) {
                    EXTENDED_COLOR_TEXT(35)
                } else {
                    EXTENDED_COLOR_TEXT(22)
                }
                printf("." RESET);
            } else if (map[coordH][coordW] == '@') {    // cow
                EXTENDED_COLOR_TEXT(196)
                printf("@" RESET);
            } else if (map[coordH][coordW] == '$') {    // message
                EXTENDED_COLOR_TEXT(220)
                printf("$" RESET);
            } else {                                    // border
                EXTENDED_COLOR_TEXT(101)
                printf("%c" RESET, map[coordH][coordW]);
            }
        }
        printf("\n");
    }
}

// only for dev
void displayAllMap(char **map, int **crushedGrass) {
    for (int coordH=0; coordH<HEIGHT_MAP; coordH++) {
        for (int coordW=0; coordW<WIDTH_MAP; coordW++) {
            if (map[coordH][coordW] == '#') {           // walls
                EXTENDED_COLOR_TEXT(94)
                printf("#" RESET);
            } else if (map[coordH][coordW] == '.') {    // floor
                if (crushedGrass[coordH][coordW] == 1) {
                    EXTENDED_COLOR_TEXT(35)
                } else {
                    EXTENDED_COLOR_TEXT(22)
                }
                printf("." RESET);
            } else if (map[coordH][coordW] == '@') {    // cow
                EXTENDED_COLOR_TEXT(196)
                printf("@" RESET);
            } else if (map[coordH][coordW] == '$') {    // message
                EXTENDED_COLOR_TEXT(220)
                printf("$" RESET);
            } else {                                    // border
                EXTENDED_COLOR_TEXT(101)
                printf("%c" RESET, map[coordH][coordW]);
            }
        }
        printf("\n");
    }
}


void gameCow(char* cowMessage, bool isDevMode) {
    // init map
    char **map = initMap();
    srand(time(NULL));
    generateMap(map);


    // init tab for grass color
    int **crushedGrass = NULL;
    crushedGrass = malloc(HEIGHT_MAP*sizeof(int*));
    if (crushedGrass == NULL) exit(1);
    for (int h=0; h<HEIGHT_MAP; h++) {
        crushedGrass[h] = malloc(WIDTH_MAP*sizeof(int));
        if (crushedGrass[h] == NULL) exit(1);
        for (int w=0; w<WIDTH_MAP; w++) {
            crushedGrass[h][w] = 0;
        }
    }

    // init coord
    CoordCouple coordInit[2];
    initGame(map, coordInit);
    CoordCouple coordCowAct = coordInit[0];
    CoordCouple coordMess = coordInit[1];
    crushedGrass[coordCowAct.coordH][coordCowAct.coordW] = 1;
    /*struct timeval timeStart, timeEnd;
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    timeEnd.tv_sec++;
    double timeDiff = 0.1;*/

    // init term setup
    struct termios oldTerm;
    initTerm(&oldTerm);
    int cKeyAct;
    char keyAct = '\0';

    // entry display
    runningCow("GAME ENTRY");

    // first map display
    updateScreen();
    if (isDevMode) {
        displayAllMap(map, crushedGrass);
    } else {
        displayMapAroundCow(map, crushedGrass,  coordCowAct, 10, 20);
    }
    printf("\n");

    // game loop
    while (isEndGame(coordCowAct, coordMess, keyAct) == 0) {
        // keyboard input
        keyAct = '\0';
        cKeyAct = getchar();
        if (cKeyAct != EOF) {
            keyAct = cKeyAct;
            /* gettimeofday(&timeStart, NULL); */
        }
        /* timeDiff = (timeStart.tv_sec - timeEnd.tv_sec) + (timeStart.tv_usec - timeEnd.tv_usec)/1e6; */

        // move cow
        if ((keyAct == 'Z' || keyAct == 'z') && (map[coordCowAct.coordH-1][coordCowAct.coordW] == '.')) {
            map[coordCowAct.coordH][coordCowAct.coordW] = '.';
            coordCowAct.coordH--;
            map[coordCowAct.coordH][coordCowAct.coordW] = '@';
            crushedGrass[coordCowAct.coordH][coordCowAct.coordW] = 1;
        } else if ((keyAct == 'S' || keyAct == 's') && (map[coordCowAct.coordH+1][coordCowAct.coordW] == '.')) {
            map[coordCowAct.coordH][coordCowAct.coordW] = '.';
            coordCowAct.coordH++;
            map[coordCowAct.coordH][coordCowAct.coordW] = '@';
            crushedGrass[coordCowAct.coordH][coordCowAct.coordW] = 1;
        } else if ((keyAct == 'Q' || keyAct == 'q') && (map[coordCowAct.coordH][coordCowAct.coordW-1] == '.')) {
            map[coordCowAct.coordH][coordCowAct.coordW] = '.';
            coordCowAct.coordW--;
            map[coordCowAct.coordH][coordCowAct.coordW] = '@';
            crushedGrass[coordCowAct.coordH][coordCowAct.coordW] = 1;
        } else if ((keyAct == 'D' || keyAct == 'd') && (map[coordCowAct.coordH][coordCowAct.coordW+1] == '.')) {
            map[coordCowAct.coordH][coordCowAct.coordW] = '.';
            coordCowAct.coordW++;
            map[coordCowAct.coordH][coordCowAct.coordW] = '@';
            crushedGrass[coordCowAct.coordH][coordCowAct.coordW] = 1;
        }

        // display map
        if (cKeyAct != EOF) {
            updateScreen();
            if (isDevMode) {
                displayAllMap(map, crushedGrass);
            } else {
                displayMapAroundCow(map, crushedGrass, coordCowAct, 10, 20);
            }
            printf("\n");
            usleep(100000);
            /* gettimeofday(&timeEnd, NULL); */
        }
        usleep(60000);
    }

    restoreTerm(&oldTerm);

    if (isEndGame(coordCowAct, coordMess, keyAct) == 1) {
        updateScreen();
        printf("    .''.       .''.      .''.\n   :_\\/_:     :_\\/_:    :_\\/_:\n   : /\\ :     : /\\ :    : /\\ :\n    '..'       '..'      '..'\n\n");
        printf("%s\n",cowMessage);
        printf("\n    .''.       .''.      .''.\n   :_\\/_:     :_\\/_:    :_\\/_:\n   : /\\ :     : /\\ :    : /\\ :\n    '..'       '..'      '..'\n");
    } else {    // == 2
        updateScreen();
        printf("EXIT\n");
    }


    for (int i=0; i<HEIGHT_MAP; i++) {
        free(crushedGrass[i]);
    }
    free(crushedGrass);
    freeMap(map);

}





