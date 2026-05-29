#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "gestionArg.h"

bool rechOpt(int argc, char **argv, char* nameOptReduct, char* nameOpt) {
    for (int i=1; i<argc; i++) {
        if ((strcmp(argv[i], nameOpt) == 0) || (strcmp(argv[i], nameOptReduct) == 0)) {
            return true;
        }
    }
    return false;
}

int rechOptDevMode(int argc, char **argv, char* nameOptReduct, char* nameOpt) {
    for (int i=1; i<argc; i++) {
        if ((strcmp(argv[i], nameOpt) == 0) || (strcmp(argv[i], nameOptReduct) == 0)) {
            if (i+1<argc && strcmp(argv[i+1], "--dev") == 0) {
                return 2;
            } else {
                return 1;
            }
        }
    }
    return 0;
}

char* rechOptArg(int argc, char **argv, char* nameOptReduct, char* nameOpt, char* defaultArg) {
    for (int i=1; i<argc; i++) {
        if ((strcmp(argv[i], nameOpt) == 0) || (strcmp(argv[i], nameOptReduct) == 0)) {
            if (!(i+1 < argc)
                || argv[i+1][0] == '-'
                || i+1 == argc-1) {
                fprintf(stderr, "Error: Missing argument for %s (%s)\n", nameOpt, nameOptReduct);
                return defaultArg;
            } else {
                return argv[i+1];
            }
        }
    }
    // default case
    return defaultArg;
}
char* rechMessage(int argc, char **argv) {
    if (argc > 1) {
        if (argv[argc-1][0] == '-') {
            fprintf(stderr, "Error: Missing message argument (Note: The message must not begin with the character '-')\n");
            exit(1);
        } else {
            return argv[argc-1];
        }
    } else {
        fprintf(stderr, "Error: Missing message argument\n");
        exit(1);
    }
}
