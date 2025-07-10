#include "cub.h"   
#include <stdlib.h>

void init_player(t_player* player)
{
    player->x = WIETH / 2;
    player->y = HIGTH / 2; 
    player->angle = PI / 3;

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
    map[1] =  "100000000000000000000001";
    map[2] =  "100000000000000000000001";
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
    map[13] = "100000000000000000000001";
    map[14] = "100000000000000000000001";
    map[15] = "100000000000000000000001";
    map[16] = "100000000000000000000001";
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
    for(int i = 0;i < size;i++)
        put_pixel_into_frame(x + i,y,game,color);
    for(int i = 0;i < size;i++)
        put_pixel_into_frame(x,y + i,game,color);
    for(int i = 0;i < size;i++)
        put_pixel_into_frame(x + i,y + size,game,color);
    for(int i = 0;i < size;i++)
        put_pixel_into_frame(x + size,y + i,game,color);
    // for (int i = 0;i < size;i++)
    // {
    //     for (int  j = 0;j < size;j++)
    //     {
    //         put_pixel_into_frame(x + j,y + i,game,color);
    //     }
    // }
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

void move_player(t_data* game)
{
    int speed = 3;
    float angle_speed = 0.03;
    t_player* player;
    player = &game->player;

    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

   
    if (player->turn_left)
        player->angle -= angle_speed;
    if (player->turn_right)
        player->angle += angle_speed;

    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->up)
    {
        player->x += cos_angle * speed;
        player->y += sin_angle * speed;
    }
    if (player->down)
    {
        player->x -= cos_angle * speed;
        player->y -= sin_angle * speed;
    }
    if (player->left)
    {
        player->x += sin_angle * speed;
        player->y -= cos_angle * speed;
    }
    if (player->right)
    {
        player->x -= sin_angle * speed;
        player->y += cos_angle * speed;
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

void draw_line(t_data* data,float start_x)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = data->player.x;
    float ray_y = data->player.y;

    while(!is_touch_wall(ray_x, ray_y, data))
    {
        put_pixel_into_frame(ray_x, ray_y, data, 0xFF0000);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
}

int ft_performent(t_data *data)
{
    int i = 0;
    float fraction = PI / 3 / WIETH;
    float start_x = data->player.angle - PI / 6;

    clear_screen(data);
    move_player(data);
    draw_squrw(data->player.y,data->player.x,data,1,0xFFC0CB);
    draw_map(data);

    while (i < WIETH)
    {
        draw_line(data, start_x);
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
// Silver: 0xC0C0C0 (same as Light Grey, often)
// Navy Blue: 0x000080
// Teal: 0x008080
// Maroon: 0x800000
// Olive: 0x808000
// Lime: 0x00FF00 (same as Green)
// Aqua: 0x00FFFF (same as Cyan)
// Coral: 0xFF7F50
// Indigo: 0x4B0082