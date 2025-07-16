#include "cub.h"   
#include <stdlib.h>

bool is_touch_wall(float x_ray,float y_ray,t_data* data);

void init_player(t_player*  player)
{
    player->x = WIETH / 2;
    player->y = HIGTH / 2; 
    player->angle = PI / 2;

    player->turn_left = false;
    player->turn_right = false;
    player->down = false;
    player->left = false;
    player->right = false;
    player->up = false;
    
}

int close_window(t_data* game)
{
    mlx_destroy_image(game->mlx, game->img);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    exit(0);
    return (0);
}

char **get_map(void)
{
   char **map = malloc(sizeof(char *) * 25); // 24 rows + NULL

    map[0] =  "111111111111111111111111";
    map[1] =  "100100000000000000000001";
    map[2] =  "100000100100011111100001";
    map[3] =  "100000100000000100000001";
    map[4] =  "100000000000000000000001";
    map[5] =  "100000010000000010000001";
    map[6] =  "100001000000001000000001";
    map[7] =  "100000000000000000000001";
    map[8] =  "100000000000000000000001";
    map[9] =  "100000000000000000000001";
    map[10] = "100000000000000000000001";
    map[11] = "100000000000000000000001";
    map[12] = "100000000000000000000001";
    map[13] = "100100100111111000000001";
    map[14] = "100100100000000001111001";
    map[15] = "100000100000000000000001";
    map[16] = "100000111101110011111001";
    map[17] = "100000000000000000000001";
    map[18] = "111111111111111111111111";
    map[19] = NULL;
        return (map);
}

void init_game(t_data* data)
{
    init_player(&data->player);
    data->map = get_map();
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIETH, HIGTH, "first windows");
    data->img = mlx_new_image(data->mlx, WIETH, HIGTH);
    data->data = mlx_get_data_addr(data->img, &data->bpp, &data->len_line, &data->endiane);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void put_pixel_into_frame(int x, int y, t_data* data, int color)
{
    if (x >= WIETH || y >= HIGTH || x < 0 || y < 0)
        return;
    int index = y * data->len_line + x * data->bpp / 8;
    data->data[index] = color & 0xFF;
    data->data[index + 1] = (color >> 8) & 0xFF;
    data->data[index + 2] = (color >> 16) & 0xFF;
}

void draw_squrw(int y,int x,t_data *game,int size,int color)
{
    // for(int i = 0;i < size;i++)
    //     put_pixel_into_frame(x + i,y,game,color);
    // for(int i = 0;i < size;i++)
    //     put_pixel_into_frame(x,y + i,game,color);
    // for(int i = 0;i < size;i++)
    //     put_pixel_into_frame(x + i,y + size,game,color);
    // for(int i = 0;i < size;i++)
    //     put_pixel_into_frame(x + size,y + i,game,color);
    for (int i = 0;i < size;i++)
    {
        for (int  j = 0;j < size;j++)
        {
            put_pixel_into_frame(x + j,y + i,game,color);
        }
    }
}

void draw_map(t_data* data)
{
    int i, j;

   
    for (i = 0; data->map[i] != NULL; i++)
    {
        for (j = 0; data->map[i][j] != '\0'; j++)
        {
            if (data->map[i][j] == '1')
                draw_squrw(i * BLOCK, j * BLOCK, data,BLOCK, 0xFFA500);
        }
    }
}
void clear_screen(t_data* data)
{
    int i, j;

    for (i = 0; i < HIGTH; i++)
    {
        for (j = 0; j < WIETH; j++)
        {
            put_pixel_into_frame(j, i, data, 0x000000);
        }
    }
}

int key_press(int keycode, t_data *data)
{
    if (keycode == 65307)
        close_window(data);
    if (keycode == W)
        data->player.up = true;
    else if (keycode == S)
        data->player.down = true;
    else if (keycode == A)
        data->player.left = true;
    else if (keycode == D)
        data->player.right = true;
    else if (keycode == LEFT)
        data->player.turn_left = true;
    else if (keycode == RIGHT)
        data->player.turn_right = true;

    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == W)
        data->player.up = false;
    else if (keycode == S)
        data->player.down = false;
    else if (keycode == A)
        data->player.left = false;
    else if (keycode == D)
        data->player.right = false;
    else if (keycode == LEFT)
        data->player.turn_left = false;
    else if (keycode == RIGHT)
        data->player.turn_right = false;
    return (0);
}

void move_player(t_player* player,t_data* game)
{
    int SPEED = 1;
    float ANGLE_SPEED = 0.01;
  
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);
    
    if (player->turn_left)
        player->angle -= ANGLE_SPEED;
    if (player->turn_right)
        player->angle += ANGLE_SPEED;

    // if (player->angle > 2 * PI)
    //     player->angle = 0;
    // if (player->angle < 0)
    //     player->angle = 2 * PI;

    if (player->up)
    {
        if (is_touch_wall(player->x  + cos_angle * SPEED,player->y  +  sin_angle * SPEED,game))
            return;
        player->x += cos_angle * SPEED;
        player->y += sin_angle * SPEED;
    }
    if (player->down)
    {
        if (is_touch_wall(player->x  - cos_angle * SPEED,player->y  - sin_angle * SPEED,game))
            return;
        player->x -= cos_angle * SPEED;
        player->y -= sin_angle * SPEED;
    }
    if (player->left)
    {
        if (is_touch_wall(player->x  + sin_angle * SPEED,player->y  - sin_angle * SPEED,game))
            return;
        player->x += sin_angle * SPEED;
        player->y -= cos_angle * SPEED;
    }
    if (player->right)
    {
         if (is_touch_wall(player->x  - sin_angle * SPEED, player->y  + cos_angle * SPEED,game))
            return;
        player->x -= sin_angle * SPEED;
        player->y += cos_angle * SPEED;
    }
}

bool is_touch_wall(float x_ray,float y_ray,t_data* data)
{
    int x = x_ray / BLOCK;
    int y = y_ray / BLOCK;
    if (data->map[y][x] == '1')
        return (true);
    return (false);
    
}

float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_data *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

void draw_view_ray(float ray_x,float ray_y,int i,t_data* data)
{

    float dist;
    float hiegh;

    dist = fixed_dist(data->player.x,data->player.y,ray_x,ray_y,data);
    hiegh = (BLOCK / dist) * (WIETH / 2);
    int start_y = (HIGTH - hiegh) / 2;
    int end = start_y + hiegh;
    
    while (start_y < end)
    {
       put_pixel_into_frame(i,start_y,data,0xFFA500);
       start_y++;
    }
}

void draw_ray(t_data* data,float start_x,int i)
{
    float cos_angle;
    float sin_angle;
    float ray_x;
    float ray_y;

    
    ray_x = data->player.x;
    ray_y = data->player.y;
    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
        while(!is_touch_wall(ray_x, ray_y, data))
        {
            //put_pixel_into_frame(ray_x, ray_y, data, 0xFF0000);
            ray_x += cos_angle;
            ray_y += sin_angle;
        }
   
    draw_view_ray(ray_x,ray_y,i,data);
}

int ft_performent(t_data *data)
{
    float i = 0;
    t_player* player;

    player = &data->player;
    double fraction = (PI / 3) / WIETH;
    float start_x = player->angle - (PI / 6);

    clear_screen(data);
    //move_player(player,data);
    draw_squrw(player->y,player->x,data,0,0xFFC0CB);
    //draw_map(data);

    while (i < WIETH)
    {
        draw_ray(data, start_x,i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(data->mlx,data->win,data->img,0,0);
    return 0;
}


int main(void)
{
    t_data data;

    init_game(&data);
    mlx_hook(data.win, 2, 1L << 0, key_press, &data);
    mlx_hook(data.win, 3, 1L << 1, key_release, &data);
    mlx_loop_hook(data.mlx, ft_performent, &data);
    mlx_hook(data.win, 17, 0, close_window, &data); 
    mlx_loop(data.mlx);
    return (0);
}

// Orange: 0xFFA500
// Purple: 0x800080
// Pink: 0xFFC0CB
// Brown: 0xA52A2A
// Gold: 0xFFD700
