#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "cub3d.h"
// #include "../minilibx-linux/mlx.h"

# define BLOCK 32
# define D_2 0
# define BLOCK_MAP 8
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
    int height;
    int width;
    int hei_map;
    int wid_map;
    t_player player;
} t_data;

bool is_touch_wall(float x_ray,float y_ray,t_data* data,int block);
void move_player_map(t_data* game,float cos_angle,float sin_angle);
void init_player(t_player*  player,char** map);
int close_window(t_data* game);
char **get_map(void);
void init_game(t_data* data,t_pars* input);
void put_pixel_into_frame(int x, int y, t_data* data, int color);
void draw_squrw(int y,int x,t_data *game,int size,int color);
void draw_map(t_data* data);
void clear_screen(t_data* data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);
bool is_correct_move(t_data* game,float sin_angle,float cos_angle);
bool is_correct_move_map(t_data* game,float sin_angle,float cos_angle);
void move_angle(t_player* player);
void move_player(t_data* game,float cos_angle,float sin_angle);
bool is_touch_wall(float x_ray,float y_ray,t_data* data,int block);
float distance(float x, float y);
float fixed_dist(float x1, float y1, float x2, float y2, t_data *game);
int get_volum_color_base_dist(double dis);
void draw_view_ray(float ray_x,float ray_y,int i,t_data* data);
void get_intersection(t_data* data,float* ray_x,float* ray_y);
void draw_ray(t_data* data,float start_x,int i);
void move_player_map(t_data* game,float cos_angle,float sin_angle);
void draw_ray_map(t_data* data,float start_x);
int ft_performent(t_data *data);


#endif // CCUB_H