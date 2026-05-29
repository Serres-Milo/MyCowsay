NAME = cowsay

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBS = -lm
SRC =  main.c newcow.c gestionArg.c color.c wildcow.c gameCow.c tamagocow.c

OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all
