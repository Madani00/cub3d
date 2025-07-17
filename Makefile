NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
MK = make
MLXDIR = minilibx-linux
LIBFT = ./Libft/libft.a
PARSER = parsing


SRCS = main.c  $(PARSER)/get_next_line.c $(PARSER)/free_error.c $(PARSER)/utils0.c \
		$(PARSER)/utils1.c $(PARSER)/parse_config.c $(PARSER)/parse_config1.c $(PARSER)/parse_map.c

OBJS = $(SRCS:.c=.o)

all: $(MLXDIR)/libmlx.a $(NAME)

$(MLXDIR)/libmlx.a:
	make -C $(MLXDIR)

$(NAME): $(OBJS)
		@$(MK) -C ./Libft
		$(CC) $(CFLAGS) $(OBJS) -lX11 -lXext -lmlx -lm $(LIBFT) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(MK) clean -C ./Libft
		@${RM} ${OBJS}

fclean: clean
		@$(MK) fclean -C ./Libft
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

.SECONDARY: