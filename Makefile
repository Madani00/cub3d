NAME = cub3D
CC = cc
CFLAGS =  
RM = rm -f
MK = make
MLXDIR = minilibx-linux
LIBFT = ./Libft/libft.a
PARSER = parsing


SRCS = main.c ./raycasting/ft_dda_raycasting.c ./raycasting/ft_free.c ./raycasting/ft_init.c ./raycasting/ft_movement.c \
	./raycasting/ft_raycasting.c \
	 $(PARSER)/get_next_line.c $(PARSER)/free_error.c $(PARSER)/read_file.c \
		$(PARSER)/utils1.c $(PARSER)/parse_config.c $(PARSER)/parse_config1.c $(PARSER)/parse_map.c

OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS)
		@$(MK) -C ./Libft
		@$(CC) $(CFLAGS) $(OBJS) -L./minilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm  $(LIBFT) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -I./includes -I./minilibx-linux -I/usr/include -c $< -o $@

clean:
		@$(MK) clean -C ./Libft
		@${RM} ${OBJS}

fclean: clean
		@$(MK) fclean -C ./Libft
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean

.SECONDARY: