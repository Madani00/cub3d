NAME = cub
SRC = raycasting/main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

CFLAGS = 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L./minilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I./includes -I./minilibx-linux -I/usr/include -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
