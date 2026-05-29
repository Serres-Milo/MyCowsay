#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "newcow.h"
#include "color.h"


void displayCowMess(char* cowMessage, int lenLineMax, const char *color) {
    int lenMess = strlen(cowMessage);
    int lenLineMess = (lenMess < lenLineMax) ? lenMess : lenLineMax;
    int nbLineMess = (lenMess <= lenLineMax) ? 1 : ((lenMess%lenLineMax == 0) ? lenMess/lenLineMax : (lenMess/lenLineMax)+1);

    // color setup
    printf("%s", color);

    // first line
    printf(" ");
    for (int i=1; i<=lenLineMess+2; i++) { printf("_"); }
    printf("\n");

    if (nbLineMess == 1) {
        printf("< %s >\n", cowMessage);
    } else {
        // second line
        printf("/ ");
        for (int c=0; c<lenLineMess; c++) { printf("%c", cowMessage[c]); }
        printf(" \\\n");

        // message body
        int numLineAct = 1;
        for (int i=0; i<nbLineMess-2; i++) {
            printf("| ");
            for (int c=(lenLineMess*numLineAct); c<(lenLineMess*(numLineAct+1)); c++) {
                printf("%c", cowMessage[c]);
            }
            numLineAct++;
            printf(" |\n");
        }

        // penultimate line
        printf("\\ ");
        for (int c=(lenLineMess*numLineAct); c<lenMess; c++) { printf("%c", cowMessage[c]); }
        int remaining = lenLineMess-(lenMess%lenLineMess);
        if (remaining > 0) {
            for (int i=0; i<remaining; i++) { printf(" "); }
        }
        printf(" /\n");
    }


    // last line
    printf(" ");
    for (int i=1; i<=lenLineMess+2; i++) { printf("-"); }
    printf("\n");

    // color reset
    printf(RESET);
}





void affiche_vache(char *eyes, char *tongue, const char *color) {
	printf("%s"
		"        \\   ^__^\n"
        "         \\  (%2.2s)\\_______\n"
        "            (__)\\       )\\/\\\n"
        "             %2.2s ||----w |\n"
        "                ||     ||\n"
        RESET,
        color, eyes, tongue
    );

}


void explosiveCow(char* cowMessage, int lenLineMax) {
    const char *frames[] = {

        "        \\   ^__^\n"
        "         \\  (oo)\\_______\n"
        "            (__)\\       )\\/\\\n"
        "                ||----w |\n"
        "                ||     ||\n",

        "        \\   ^__^\n"
        "         \\  (oo)\\_______\n"
        "            (__)\\  *    )\\/\\\n"
        "                ||-*-w |\n"
        "                ||  *  ||\n",

        "        \\   ^__^\n"
        "         \\  (oo)\\__*____\n"
        "            (__)\\ * *  )\\/\\\n"
        "                |*-*-w |\n"
        "                ||  *  ||\n",

        "         \\   ^__^\n"
        "          \\ (oo)__*___\n"
        "           (__)\\ * * )\n"
        "             |*-*-* |\n"
        "             | | *  |\n"
        "              *\n",

        "            ^__^\n"
        "         * (oo)  *\n"
        "        *  (__) *  *\n"
        "          * | * |\n"
        "        *   |   |   *\n",

        "        *   ^  ^   *\n"
        "     *    (oo)      *\n"
        "        * (__)  * \n"
        "     *    |  |     *\n"
        "        * |  |   *\n",

        "    *        ^        *\n"
        "       *   (   )   *\n"
        "   *       (   )       *\n"
        "       *    | |    *\n"
        "    *        |        *\n",

        " *    *     * *     *    *\n"
        "     *   (       )   *\n"
        " *       (       )       *\n"
        "     *      | |      *\n"
        " *    *     | |     *    *\n",

        " *   _     *   *     _   *\n"
        "    (   )       *  (   )\n"
        " * (     )   *    (     ) *\n"
        "    \\   /         \\   /\n"
        " *    | |     *     | |   *\n",

        "    _ ._      *      _ ._\n"
        " *        *       *\n"
        "    (          *     )\n"
        " *    (             )   *\n"
        "        \\         /\n"
        " *        |   |      *\n",

        "       _ ._  _   *\n"
        "     (    *      __)\n"
        "   (   *        *   _)\n"
        "  (      *   *     ,__)\n"
        "      `~~`\\   /`~~`\n"
        "    *      ; ;      *\n"
        "           / \\\n",

        "       _ ._  _ , *\n"
        "     (_   (   )_  .__)\n"
        "   ( (  (  * )   `)  ) _)\n"
        "  (__ (_   * . _) _) ,__)\n"
        "      `~~`\\ * /`~~`\n"
        "           ;   ;\n"
        "           /   \\\n"
        "______*___/     \\___*______\n",

        "       _ ._  _ , _ ._\n"
        "     (_ ' ( `  )_  .__)\n"
        "   ( (  (  * )   `)  ) _)\n"
        "  (__ (_   (_ . _) _) ,__)\n"
        "      `~~`\\ ' . /`~~`\n"
        "           ;   ;\n"
        "           /   \\\n"
        "__________/     \\_________\n",

        "       _ ._  _ , _ ._\n"
        "     (_ ' ( `  )_  .__)\n"
        "   ( (  (    )   `)  ) _)\n"
        "  (__ (_   (_ . _) _) ,__)\n"
        "      `~~`\\ ' . /`~~`\n"
        "           ;   ;\n"
        "           /   \\\n"
        "__________/     \\_________\n"
    };

    printf("\033[H\033[J");
    displayCowMess(cowMessage, lenLineMax, DEFAULT_COLOR);
    printf("%s",frames[0]);
    usleep(2000000);

    for (int i=1; i<14; i++) {
        printf("\033[H\033[J");
        displayCowMess(cowMessage, lenLineMax, DEFAULT_COLOR);
        printf("%s",frames[i]);
        usleep(300000);
    }
}




