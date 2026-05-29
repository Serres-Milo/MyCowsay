#ifndef __COLOR_H__
#define __COLOR_H__

#define LEN_COLORS 16

extern const char *listColors[LEN_COLORS];
extern const char *listColorCodes[LEN_COLORS];


#define RESET   "\033[0m"
#define DEFAULT_COLOR "\x1b[39m"

#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"


// Extended colors
#define EXTENDED_COLOR_TEXT(num) do { printf("\033[38;5;%dm", num); } while (0);
#define EXTENDED_COLOR_FONT(num) do { printf("\033[48;5;%dm", num); } while (0);



#endif
