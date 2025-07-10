#ifndef CCUB_H
#define CCUB_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"

# define BLOCK 32
# define WIETH (BLOCK * 24 + 2)
# define HIGTH (BLOCK * 19 + 3)

# define LEFT 65361
# define RIGHT 65363
# define W 119
# define D 97
# define S 115
# define A 100

#define PI 3.14159265358979323846264338328
typedef struct s_player
{
    int x;
    int y;
    float angle;

    bool up;
    bool down;
    bool left;
    bool right;
    bool turn_left;
    bool turn_right;

} t_player;

typedef struct s_data
{
    void *win;
    void *mlx;
    void *img;
    char *data;
    char **map;

    int bpp;
    int len_line;
    int endiane;
    t_player player;
} t_data;

#endif // CCUB_H