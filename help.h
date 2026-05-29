#ifndef __HELP_H__
#define __HELP_H__

#define RESET_ANSI "\033[0m"
#define UNDERLINE "\033[4m"
#define BOLD "\033[1m"
#define COLOR_OPT "\033[38;5;37m"

static const char *helpText =
    UNDERLINE "Usage:" RESET " " COLOR_OPT BOLD "cowsay [options] <message>" RESET "\n"
    "\n"
    UNDERLINE "Options:" RESET "\n"
    "\t" COLOR_OPT BOLD "-h" RESET ", " COLOR_OPT BOLD "--help" RESET "\tDisplay this help\n"
    "\n"
    "\t" UNDERLINE "Basic options (can be combined):" RESET "\n"
    "\t" COLOR_OPT BOLD "-e <XX>" RESET ", " COLOR_OPT BOLD "--eyes <XX>" RESET "\t\t\tChange the cow's eyes (using the two specified characters)\n"
    "\t" COLOR_OPT BOLD "-T <XX>" RESET ", " COLOR_OPT BOLD "--tongue <XX>" RESET "\t\t\tChange the cow's tongue (using the two specified characters)\n"
    "\t" COLOR_OPT BOLD "-c <color name>" RESET ", " COLOR_OPT BOLD "--color <color name>" RESET "\tChange the color of the cow\n"
    "\t\t" COLOR_OPT BOLD "-l" RESET ", " COLOR_OPT BOLD "--listColors" RESET "\t\tDisplays the available options for --colors\n"
    "\t" COLOR_OPT BOLD "-W <number>" RESET ", " COLOR_OPT BOLD "--wrap <number>" RESET "\t\tSpecifies the maximum width of a message line (without this option, the default is 40)\n"
    "\n"
    "\t" UNDERLINE "Predefined states:" RESET "\n"
    "\t" COLOR_OPT BOLD "-b" RESET ", " COLOR_OPT BOLD "--borg" RESET "\n"
    "\t" COLOR_OPT BOLD "-d" RESET ", " COLOR_OPT BOLD "--dead" RESET "\n"
    "\t" COLOR_OPT BOLD "-g" RESET ", " COLOR_OPT BOLD "--greedy" RESET "\n"
    "\t" COLOR_OPT BOLD "-p" RESET ", " COLOR_OPT BOLD "--paranoid" RESET "\n"
    "\t" COLOR_OPT BOLD "-s" RESET ", " COLOR_OPT BOLD "--stoned" RESET "\n"
    "\t" COLOR_OPT BOLD "-t" RESET ", " COLOR_OPT BOLD "--tired" RESET "\n"
    "\t" COLOR_OPT BOLD "-w" RESET ", " COLOR_OPT BOLD "--wired" RESET "\n"
    "\t" COLOR_OPT BOLD "-y" RESET ", " COLOR_OPT BOLD "--youthful" RESET "\n"
    "\n"
    "\t" UNDERLINE "Other options:" RESET "\n"
    "\t" COLOR_OPT BOLD "-E" RESET ", " COLOR_OPT BOLD "--explosive" RESET "\tThe cow explodes\n"
    "\t" COLOR_OPT BOLD "-r" RESET ", " COLOR_OPT BOLD "--run" RESET "\tThe cow runs to the door " "\033[38;5;196m" "(DOESN'T support messages longer than 40 characters !)\n"
    "\t" COLOR_OPT BOLD "-G" RESET ", " COLOR_OPT BOLD "--game" RESET "\tStart the cow game (Add " COLOR_OPT BOLD "--dev" RESET " right after that to display the entire map)\n"
    "\t\t" UNDERLINE "Game commands:" RESET "\n"
    "\t\t" COLOR_OPT BOLD "Z Q S D" RESET " -> cow's movement keys " "\033[38;5;196m" "(DON'T hold down these keys !)" RESET "\n"
    "\t\t" COLOR_OPT BOLD "E" RESET " -> game exit key\n"
    "\t\t" UNDERLINE "Game rules:" RESET "\n"
    "\t\t" "Explore the map with the cow (" RED "@" RESET ") until you find the message (" "\033[38;5;220m" "$" RESET ")\n"
    "\t\t" "(PS: The grass changes color where the cow has walked)\n"
    "\t" COLOR_OPT BOLD "-C" RESET ", " COLOR_OPT BOLD "--tamagocow" RESET "\t\tStart the tamagocow game (Add " COLOR_OPT BOLD "--dev" RESET " right after that to display the \"fitness\" variable)\n"

    "\n"
    UNDERLINE "Author:" RESET " SERRES Milo\n"

;


#endif
