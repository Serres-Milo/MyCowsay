#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "tamagocow.h"


#define LIFEROCKS 0
#define LIFESUCKS 1
#define BYEBYELIFE 2

void displayStateCow (int health) {
    switch (health) {
        case LIFEROCKS:
            printf(
                "\n          ░     ░          ░     ░\n"
                "     ░     ░     ░░░    ░░░     ░     ░\n"
                "      ░     ░░░░░░░░░░░░░░░░░░░░     ░\n"
                "░      ░░░░░░░░░░░░      ░░░░░░░░░░░░      ░\n"
                " ░    ░░░░░░                    ░░░░░░    ░\n"
                "  ░░░░░░░░     ^__^               ░░░░░░░░\n"
                "     ░░░░░░    (**)\\_______      ░░░░░░ \n"
                " ░    ░░░░     (__)\\       )\\/\\   ░░░░    ░\n"
                "  ░░░░░░░          ||----w |       ░░░░░░░\n"
                "░░░░░░░░░          ||     ||       ░░░░░░░░░\n\n"
            );
            break;
        case LIFESUCKS:
            printf(
                "\n     ^__^\n"
                "     (~~)\\_______\n"
                "     (__)\\       )\\/\\\n"
                "         ||----w |\n"
                "       ░░░░░░░░░░░░ ░░░\n"
                "      ░░░     ░░░  ░  ░░\n"
                "    ░░░░  ░░░    ░  ░   ░░\n"
                "  ░░░░░  ░░   ░ ░░  ░░ ░ ░░░\n"
                " ░░░░  ░░░   ░  ░ ░░  ░  ░\n"
                "  ░░░░░░░░░░░░░░░░░░░░░░░\n\n"
            );
            break;
        case BYEBYELIFE:
            printf(
                "\n          ||     ||\n"
                "          ||----m |\n"
                "╦═════(¯¯)/       )/\\/═════╦\n"
                "║     (xx)/¯¯¯¯¯¯¯         ║\n"
                "║     v¯¯v     ░           ║\n"
                "║            ░░░░          ║\n"
                "║          ░░░ ░░░         ║\n"
                "║         ░░░   ░░░        ║\n"
                "║        ░░░   ░░░░        ║\n"
                "║       ════════════       ║\n\n"
            );
            break;
        default:
            fprintf(stderr, "Invalid \"health\" value: %d (must be between %d ; %d ; %d)", health, LIFEROCKS, LIFESUCKS, BYEBYELIFE);
            exit(1);
    }
}


int healthStatus (int fitness) {
    switch (fitness) {
        case 0:
        case 10:
            return BYEBYELIFE;
        case 1:
        case 2:
        case 3:
        case 7:
        case 8:
        case 9:
            return LIFESUCKS;
        case 4:
        case 5:
        case 6:
            return LIFEROCKS;
        default:
            fprintf(stderr, "Invalid \"fitness\" value: %d (must be between 0 and 10)", fitness);
            exit(1);
    }
}


void execAfterLunchFood (int* pFitness, int* pStock, int lunchfood) {
    int resTemp;
    resTemp = (*pFitness + lunchfood) - (rand()%4);   // digestion

    if (resTemp < 0) {
        *pFitness = 0;
    } else if (resTemp > 10) {
        *pFitness = 10;
    } else {
        *pFitness = resTemp;
    }


    resTemp = (*pStock - lunchfood) + (rand()%7 -3);   // crop

    if (resTemp < 0) {
        *pStock = 0;
    } else if (resTemp > 10) {
        *pStock = 10;
    } else {
        *pStock = resTemp;
    }
}





void tamagocowMain (bool isDevMode) {
    srand(time(NULL));

    int score = 0;
    int fitness = 5;
    int stock = 5;
    int health = LIFEROCKS;
    int lunchfood = -1;


    while (health != BYEBYELIFE) {
        displayStateCow(health);
        printf("Stock : %d\n", stock);
        if (isDevMode) printf("Fitness : %d\n", fitness);

        do {
            printf("How much food should you give at the cow ? ");
            if (scanf("%d", &lunchfood) != 1) {
                printf("Error: Invalid input\n");
                lunchfood = -1;
                while (getchar() != '\n');  // buffer clear
            } else if (lunchfood < 0 || lunchfood > stock) {
                printf("Error: This number is invalid for the \"stock\" value\n");
                lunchfood = -1;
            }
        } while (lunchfood < 0 || lunchfood > stock);


        execAfterLunchFood(&fitness, &stock, lunchfood);

        score++;

        health = healthStatus(fitness);
    }


    displayStateCow(health);

    printf(
            "╔══════════════════════╗\n"
            "╠════════DEFEAT════════╣\n"
            "╠══════════════════════╣\n"
            "╠══════SCORE: %-3d══════╣\n"
            "╚══════════════════════╝\n",
            score
           );

}




























