NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MK = make
MLXDIR = minilibx-linux


SRCS = main.c 
OBJS = $(SRCS:.c=.o)

all: $(MLXDIR)/libmlx.a $(NAME)

$(MLXDIR)/libmlx.a:
	make -C $(MLXDIR)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -lX11 -lXext -lmlx -lm -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(MK) clean -C $(MLXDIR)
		${RM} ${OBJS} $(OBJS_B)

fclean: clean
		$(MK) fclean -C ./Libft

re: fclean all

.PHONY: all clean fclean re bonus

.SECONDARY: