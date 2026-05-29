#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "gestionArg.h"
#include "newcow.h"
#include "color.h"
#include "wildcow.h"
#include "gameCow.h"
#include "help.h"
#include "tamagocow.h"


int main(int argc, char **argv) {
    char *argEyes = "";
    char *argTongue = "";
    const char *argColor = "";
    int colorIndex = 20;


    // checks that the argument for --wrap is indeed an int
    char *charLenLineMax = rechOptArg(argc,argv,"-W","--wrap","40");
    char *endCharLenLineMax;
    long longLenLineMax = strtol(charLenLineMax, &endCharLenLineMax, 10);
    if (*endCharLenLineMax != '\0') {
        fprintf(stderr, "Error: Invalid argument for --wrap\n");
        longLenLineMax = 40;
    }
    int intLenLineMax = (int)longLenLineMax;


    // help page
    if (rechOpt(argc,argv,"-h","--help")) {
        printf("%s",helpText);
        return 0;
    }

    // list color cow
    if (rechOpt(argc, argv,"-l","--listColors")) {
        for (int i=0; i<LEN_COLORS; i++) {
            printf("%s ", listColors[i]);
        }
        printf("\n");
        return 0;
    }

    // tamagocow
    int resRechC = rechOptDevMode(argc,argv,"-C","--tamagocow");
    if (resRechC == 1) {
        tamagocowMain(false);
        return 0;
    } else if (resRechC == 2) {
        tamagocowMain(true);
        return 0;
    }


    char *cowMessage = rechMessage(argc, argv);

    // explosive cow
    if (rechOpt(argc,argv,"-E","--explosive")) {
        explosiveCow(cowMessage, intLenLineMax);
        return 0;
    }

    // running cow
    if (rechOpt(argc,argv,"-r","--run")) {
        runningCow(cowMessage);
        return 0;
    }

    // game cow
    int resRechG = rechOptDevMode(argc,argv,"-G","--game");
    if (resRechG == 1) {
        gameCow(cowMessage, false);
        return 0;
    } else if (resRechG == 2) {
        gameCow(cowMessage, true);
        return 0;
    }

    // predefined states
    if (rechOpt(argc,argv,"-b","--borg")) {
        // borg (Star Trek)
        argEyes = "==";
    } else if (rechOpt(argc,argv,"-d","--dead")) {
        // dead
        argEyes = "xx";
        argTongue = "U ";
    } else if (rechOpt(argc,argv,"-g","--greedy")) {
        // greedy
        argEyes = "$$";
    } else if (rechOpt(argc,argv,"-p","--paranoid")) {
        // paranoid
        argEyes = "@@";
    } else if (rechOpt(argc,argv,"-s","--stoned")) {
        // stoned
        argEyes = "**";
        argTongue = "U ";
    } else if (rechOpt(argc,argv,"-t","--tired")) {
        // tired
        argEyes = "--";
    } else if (rechOpt(argc,argv,"-w","--wired")) {
        // wired
        argEyes = "OO";
    } else if (rechOpt(argc,argv,"-y","--youthful")) {
        // youthful
        argEyes = "..";
    } else {
        // general cases
        argEyes = rechOptArg(argc,argv,"-e","--eyes","oo");
        argTongue = rechOptArg(argc,argv,"-T","--tongue","");
        argColor = rechOptArg(argc, argv, "-c", "--color", DEFAULT_COLOR);
        // check if color is available
        for (int i=0; i<LEN_COLORS; i++) {
            if (strcmp(argColor,listColors[i]) == 0) {
                colorIndex = i;
                break;
            }
        }
        if (colorIndex < LEN_COLORS) {
            argColor = listColorCodes[colorIndex];
        } else {
            argColor = DEFAULT_COLOR;
        }

        // display cow
        displayCowMess(cowMessage, intLenLineMax, argColor);
        affiche_vache(argEyes, argTongue, argColor);

        return 0;
    }
}




