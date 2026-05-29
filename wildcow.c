#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "wildcow.h"
#include "color.h"

#define NB_FRAMES 4
#define NB_LINES_PER_FRAME  5

#define WIDTH_DOOR  10
#define WIDTH_DOOR_JAMB 2

#define COLOR_TEXT(arg) if (arg%6 == 0) { \
                            printf(RED); \
                        } else if (arg%5 == 1) { \
                            printf(GREEN); \
                        } else if (arg%5 == 2) { \
                            printf(YELLOW); \
                        } else if (arg%5 == 3) { \
                            printf(BLUE); \
                        } else if (arg%5 == 4) { \
                            printf(MAGENTA); \
                        } else { \
                            printf(CYAN); \
                        }

char *framesRunningCow[NB_FRAMES][NB_LINES_PER_FRAME] = {
    {"^__^",
    "(oo)\\_______",
    "(__)\\       )\\/\\",
    "   //----w /",
    "   \\\\     \\\\"},

    {"^__^",
    "(oo)\\_______",
    "(__)\\       )\\/\\",
    "   \\\\----w \\",
    "    \\\\     \\\\"},

    {"^__^\n",
    "(oo)\\_______",
    "(__)\\       )\\/\\",
    "   //----w /",
    "   \\\\     \\\\"},

    {"^__^",
    "(oo)\\_______",
    "(__)\\       )\\/\\",
    "   //----w /",
    "  //     //"}
};

char *door = {
    "\n  ______  \n"
    " //    \\\\ \n"
    "//      \\\\\n"
    "||      ||\n"
    "||      ||\n"
    "||      ||\n"
    "||      ||\n"
};



void updateScreen(void) {
    printf("\033[H\033[J");
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH",y,x);
}


void loopRunningCow(int xAct, int yAct, char* cowMessage) {

    for (int numFrame=0; numFrame<4; numFrame++) {
        updateScreen();
        COLOR_TEXT(rand())
        printf("%s" RESET,door);
        // text on door
        gotoxy(1,1);
        COLOR_TEXT(rand())
        printf("%s" RESET, cowMessage);

        for (int nLineFrame=0; nLineFrame<5; nLineFrame++) {
            gotoxy(xAct-(2*numFrame),yAct+nLineFrame);
            printf("%s",framesRunningCow[numFrame][nLineFrame]);
        }
        fflush(stdout);
        usleep(200000);
    }

}

void loopReducRunningCow(int xAct, int yAct, int indent, char* cowMessage) {
    for (int numFrame=0; numFrame<4; numFrame++) {
        updateScreen();
        COLOR_TEXT(rand())
        printf("%s" RESET,door);
        // text on door
        gotoxy(1,1);
        COLOR_TEXT(rand())
        printf("%s" RESET, cowMessage);

        for (int nLineFrame=0; nLineFrame<5; nLineFrame++) {
            if ((xAct-(2*(numFrame+1))) > 0) {
                gotoxy((xAct-(2*(numFrame+1))),yAct+nLineFrame);
            } else {
                gotoxy(WIDTH_DOOR_JAMB+1,yAct+nLineFrame);
            }

            int lenLine = strlen(framesRunningCow[numFrame][nLineFrame]);
            if (indent <= lenLine) {
                int nChar = indent;
                while (framesRunningCow[numFrame][nLineFrame][nChar] != '\0') {
                    printf("%c",framesRunningCow[numFrame][nLineFrame][nChar]);
                    nChar++;
                }
            }
        }
        fflush(stdout);
        usleep(200000);
    }
}

void runningCow(char* cowMessage) {
    int xDep = 50;
    int yDep = 4;
    srand(time(NULL));


    // max len of lines
    int maxLen = 0;
    for (int i=0; i<NB_FRAMES; i++) {
        for (int j=0; j<NB_LINES_PER_FRAME; j++) {
            int lenAct = strlen(framesRunningCow[i][j]);
            if (lenAct > maxLen)
                maxLen = lenAct;
        }
    }


    for (int i=0; i<xDep-WIDTH_DOOR_JAMB; i+=8) {
        loopRunningCow(xDep-i, yDep, cowMessage);
    }

    for (int i=0; i<=maxLen; i+=2) {         // replace i+=2 with i++ to remove one character at a time
        loopReducRunningCow(0, yDep, i, cowMessage);
    }


    printf("\n");

}



