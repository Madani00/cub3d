#include "cub.h"   
#include <stdlib.h>

bool is_touch_wall(float x_ray,float y_ray,t_data* data,int block);
void move_player_map(t_data* game,float cos_angle,float sin_angle);

void init_player(t_player*  player)
{
    player->x = WIETH / 2;
    player->y = HIGTH / 2; 
    player->map_x = WIETH_MAP / 2;
    player->map_y = HIGTH_MAP / 2;
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
    data->win = mlx_new_window(data->mlx, WIETH, HIGTH, "CUB3D");
    data->img = mlx_new_image(data->mlx, WIETH, HIGTH);
    data->img_map =  mlx_new_image(data->mlx, WIETH_MAP, HIGTH_MAP);
    data->data = mlx_get_data_addr(data->img, &data->bpp, &data->len_line, &data->endiane);
    data->data_map = mlx_get_data_addr(data->img_map, &data->bpp_map, &data->len_line_map, &data->endiane_map);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void put_pixel_into_frame(int x, int y, t_data* data, int color)
{
    int index;

    if (data->inside_win)
    {
        if (x >= WIETH || y >= HIGTH || x < 0 || y < 0)
            return;
        index = y * data->len_line + x * data->bpp / 8;
        data->data[index] = color & 0xFF;
        data->data[index + 1] = (color >> 8) & 0xFF;
        data->data[index + 2] = (color >> 16) & 0xFF;
    }
    if (data->iside_win_map)
    {
        if (x >= WIETH_MAP || y >= HIGTH_MAP || x < 0 || y < 0)
            return;
        index = y * data->len_line_map + x * data->bpp_map / 8;
        data->data_map[index] = color & 0xFF;
        data->data_map[index + 1] = (color >> 8) & 0xFF;
        data->data_map[index + 2] = (color >> 16) & 0xFF;
    }
}

void draw_squrw(int y,int x,t_data *game,int size,int color)
{
    if (game->inside_win)
    {
        for (int i = 0;i < size;i++)
        {
            for (int  j = 0;j < size;j++)
            {
                put_pixel_into_frame(x + j,y + i,game,color);
            }
        }
    }
    if (game->iside_win_map)
    {
        size = BLOCK_MAP;
        y = y / BLOCK;
        y = y * BLOCK_MAP;
        x = x / BLOCK;
        x = x * BLOCK_MAP;
        for (int i = 0;i < size;i++)
        {
            for (int  j = 0;j < size;j++)
            {
                put_pixel_into_frame(x + j,y + i,game,color);
            }
        }
    }
}

void draw_map(t_data* data)
{
    int i;
    int j;

    data->inside_win = false;
    for (i = 0; data->map[i] != NULL; i++)
    {
        for (j = 0; data->map[i][j] != '\0'; j++)
        {
            if (data->map[i][j] == '1')
            draw_squrw(i * BLOCK, j * BLOCK, data,BLOCK, 400);
        }
    }
    data->inside_win = true;
}

void clear_screen(t_data* data)
{
    int i, j;
    data->inside_win = true;
    data->iside_win_map = true;
    for (i = 0; i < HIGTH/2; i++)
    {
        for (j = 0; j < WIETH; j++)
            put_pixel_into_frame(j, i, data, 255);
    }
    for (i = HIGTH/2; i < HIGTH; i++)
    {
        for (j = 0; j < WIETH; j++)
            put_pixel_into_frame(j, i, data,0x800080);
    }
    data->inside_win = false;
    for (i = 0; i < HIGTH_MAP; i++)
    {
        for (j = 0; j < WIETH_MAP; j++)
            put_pixel_into_frame(j, i, data, 0x00000000);
    }
    data->inside_win = true;
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

bool is_correct_move(t_data* game,float sin_angle,float cos_angle,int block)
{
    t_player* player;

    player = &game->player;
    if (player->up)
    {
        if (is_touch_wall(player->x  + cos_angle * SPEED,player->y  +  sin_angle * SPEED,game,block))
            return (true);
    }
    if (player->down)
    {
        if (is_touch_wall(player->x  - cos_angle * SPEED,player->y  - sin_angle * SPEED,game,block))
            return(true);
    }
    if (player->left)
    {
        if (is_touch_wall(player->x  + sin_angle * SPEED,player->y  - sin_angle * SPEED,game,block))
            return(true);
    }
    if (player->right)
    {
         if (is_touch_wall(player->x  - sin_angle * SPEED, player->y  + cos_angle * SPEED,game,block))
            return(true);
    }
}

bool is_correct_move_map(t_data* game,float sin_angle,float cos_angle,int block)
{
    t_player* player;

    player = &game->player;
    if (player->up)
    {
        if (is_touch_wall(player->map_x  + cos_angle * SPEED,player->map_y  +  sin_angle * SPEED,game,block))
            return (true);
    }
    if (player->down)
    {
        if (is_touch_wall(player->map_x  - cos_angle * SPEED,player->map_y  - sin_angle * SPEED,game,block))
            return(true);
    }
    if (player->left)
    {
        if (is_touch_wall(player->map_x  + sin_angle * SPEED,player->map_y  - sin_angle * SPEED,game,block))
            return(true);
    }
    if (player->right)
    {
         if (is_touch_wall(player->map_x  - sin_angle * SPEED, player->map_y  + cos_angle * SPEED,game,block))
            return(true);
    }
}

void move_angle(t_player* player)
{
    if (player->turn_left)
        player->angle -= ANGLE_SPEED;
    if (player->turn_right)
        player->angle += ANGLE_SPEED;
}

void move_player(t_data* game,float cos_angle,float sin_angle)
{
    move_player_map(game,cos_angle,sin_angle);
    if (is_correct_move(game,sin_angle,cos_angle,BLOCK))
        return;
    move_angle(&game->player);
    if (game->player.up)
    {
        game->player.x += cos_angle * SPEED;
        game->player.y += sin_angle * SPEED;
    }
    if (game->player.down)
    {
        game->player.x -= cos_angle * SPEED;
        game->player.y -= sin_angle * SPEED;
    }
    if (game->player.left)
    {
        game->player.x += sin_angle * SPEED;
        game->player.y -= cos_angle * SPEED;
    }
    if (game->player.right)
    {
        game->player.x -= sin_angle * SPEED;
        game->player.y += cos_angle * SPEED;
    }
}

bool is_touch_wall(float x_ray,float y_ray,t_data* data,int block)
{
    int x = x_ray / block;
    int y = y_ray / block;
    if (data->map[y][x] == '1')
        return (true);
    return (false);
    
}

float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_data *game)
{
    float delta_x ;
    float delta_y ;
    float angle  ;
    float fix_dist;

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    angle = atan2(delta_y, delta_x) - game->player.angle;
    fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

void draw_view_ray(float ray_x,float ray_y,int i,t_data* data)
{
    float dist;
    float hiegh;
    int start_y;
    int end;

    dist = fixed_dist(data->player.x,data->player.y,ray_x,ray_y,data);
    hiegh = (BLOCK / dist) * (WIETH / 2);
    start_y = (HIGTH - hiegh) / 2;
    end = start_y + hiegh;
    while (start_y < end)
    {
       put_pixel_into_frame(i,start_y,data,0xFFA590);
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
    data->iside_win_map = false;
    data->inside_win = true;
    while(!is_touch_wall(ray_x, ray_y, data,BLOCK))
    {
        //put_pixel_into_frame(ray_x, ray_y, data, 0xFF0000);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    draw_view_ray(ray_x,ray_y,i,data);
}

void move_player_map(t_data* game,float cos_angle,float sin_angle)
{

    if (is_correct_move_map(game,sin_angle,cos_angle,BLOCK_MAP))
        return;
    move_angle(&game->player);
    game->player.map_x = (game->player.x / BLOCK);
    game->player.map_x *= BLOCK_MAP;
    game->player.map_y = (game->player.y / BLOCK);
    game->player.map_y *= BLOCK_MAP;
}

void draw_ray_map(t_data* data,float start_x,int i)
{
    float cos_angle;
    float sin_angle;
    float ray_x;
    float ray_y;

    
    ray_x = data->player.map_x;
    ray_y = data->player.map_y;
    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
    cos_angle /= (BLOCK/BLOCK_MAP);
    sin_angle /= (BLOCK/BLOCK_MAP);
    data->iside_win_map = true;
    data->inside_win = false;
    while(!is_touch_wall(ray_x, ray_y, data,BLOCK_MAP))
    {
        put_pixel_into_frame(ray_x, ray_y, data, 0xFF0000);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    data->inside_win = true;
}

int ft_performent(t_data *data)
{
    int (i) ,(j);
    float (start_x_map) , (start_x);
    double (fraction) ,(fraction_map);
    t_player* player;

    player = &data->player;
    i = -1;
    j = -1;
    fraction = (PI / 3) / WIETH;
    fraction_map = (PI / 3) / WIETH_MAP;
    start_x = player->angle - (PI / 6);
    start_x_map = start_x;
    clear_screen(data);
    move_player(data,cos(player->angle),sin(player->angle));
    draw_map(data);
    while (++i < WIETH)
    {
        draw_ray(data, start_x,i);
        if (i < WIETH_MAP)
        {
            draw_ray_map(data,start_x_map,++j);
            start_x_map += fraction_map;
        }
        start_x += fraction;
    }
    mlx_put_image_to_window(data->mlx,data->win,data->img,0,0);
    mlx_put_image_to_window(data->mlx,data->win,data->img_map,0,(HIGTH - HIGTH_MAP));
    return (0);
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













