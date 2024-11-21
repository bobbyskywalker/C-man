CC = gcc
CFLAGS = 
LDFLAGS += -lncurses

NAME = cmangame

SRCS = src/main.c src/game.c src/game_map.c src/utils.c src/menu.c src/levels.c src/ghosts.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re