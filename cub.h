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
# define D_2 0
# define BLOCK_MAP 8
# define WIETH (BLOCK * 24)
# define HIGTH (BLOCK * 19)
# define WIETH_MAP (24 * BLOCK_MAP)
# define HIGTH_MAP (19 * BLOCK_MAP)
# define ANGLE_SPEED 0.01
# define SPEED 1

# define LEFT 65361
# define RIGHT 65363
# define W 119
# define D 97
# define S 115
# define A 100

#define PI 3.14159265359
typedef struct s_player
{
    float x;
    float y;
    float map_x;
    float map_y;
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
    void* img_map;
    char *data;
    char *data_map;
    char **map;
    bool  iside_win_map;
    bool  inside_win;
    int bpp;
    int len_line;
    int endiane;
    int bpp_map;
    int len_line_map;
    int endiane_map;
    t_player player;
} t_data;

#endif // CCUB_H