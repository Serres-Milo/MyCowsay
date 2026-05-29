#include "color.h"

const char *listColors[LEN_COLORS] = {
    "BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA",
    "CYAN", "WHITE", "BRIGHT_BLACK", "BRIGHT_RED",
    "BRIGHT_GREEN", "BRIGHT_YELLOW", "BRIGHT_BLUE",
    "BRIGHT_MAGENTA", "BRIGHT_CYAN", "BRIGHT_WHITE"
};


const char *listColorCodes[LEN_COLORS] = {
    "\033[30m", // BLACK
    "\033[31m", // RED
    "\033[32m", // GREEN
    "\033[33m", // YELLOW
    "\033[34m", // BLUE
    "\033[35m", // MAGENTA
    "\033[36m", // CYAN
    "\033[37m", // WHITE
    "\033[90m", // BRIGHT_BLACK
    "\033[91m", // BRIGHT_RED
    "\033[92m", // BRIGHT_GREEN
    "\033[93m", // BRIGHT_YELLOW
    "\033[94m", // BRIGHT_BLUE
    "\033[95m", // BRIGHT_MAGENTA
    "\033[96m", // BRIGHT_CYAN
    "\033[97m"  // BRIGHT_WHITE
};
