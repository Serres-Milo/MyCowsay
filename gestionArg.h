#ifndef __GESTION_ARG_H__
#define __GESTION_ARG_H__

#include <stdbool.h>

bool rechOpt(int argc, char **argv, char* nameOptRed, char* nameOpt);
int rechOptDevMode(int argc, char **argv, char* nameOptReduct, char* nameOpt);
char* rechOptArg(int argc, char **argv, char* nameOptRed, char* nameOpt, char* defaultArg);
char* rechMessage(int argc, char **argv);

#endif
