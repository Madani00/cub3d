#include "../include/cub.h"   

void init_player(t_player*  player,char** map)
{
    int (i) ,(j);

    i = -1;   
    player->angle = PI / 2; 
    player->turn_left = false;
    player->turn_right = false;
    player->down = false;
    player->left = false;
    player->right = false;
    player->up = false;
    while (map && map[++i] != NULL)
    {
        j = -1;
        while (map[i][++j] != '\0')
            if (map[i][j] == 'N')
            {
                player->x = j * BLOCK;
                player->y = i * BLOCK; 
                player->map_x = j * BLOCK_MAP;
                player->map_y = i * BLOCK_MAP;
                map[i][j] = '0';
                return;
            }
    }
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
void	free_images(t_data *data)
{
	if (data->texture1)
		mlx_destroy_image(data->mlx, data->texture1);
	if (data->texture2)
		mlx_destroy_image(data->mlx, data->texture2);
    if (data->texture3)
		mlx_destroy_image(data->mlx, data->texture3);
	if (data->texture4)
		mlx_destroy_image(data->mlx, data->texture4);
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
}
void	free_minilbx(t_data *data)
{
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
void	free_all_mlx(t_data *data)
{
    //free(data->data);
    free_args(data->map);
	free_images(data);
	free_minilbx(data);
}

void init_game(t_data* data,t_pars* input)
{
    data->map = input->map;
    data->data_pars = input;
    init_player(&data->player,data->map);
    data->height = 800;
    data->width = 1024;
    data->hei_map = (input->column - 6) * BLOCK_MAP;
    data->wid_map = input->long_line * BLOCK_MAP;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->width, data->height, "CUB3D");
    data->img = mlx_new_image(data->mlx,data->width, data->height);
    // data->img_map =  mlx_new_image(data->mlx, data->wid_map, data->hei_map);
    data->data = mlx_get_data_addr(data->img, &data->bpp, &data->len_line, &data->endiane);
    // data->data_map = mlx_get_data_addr(data->img_map, &data->bpp, &data->len_line_map, &data->endiane);
    
    data->img_height = 32;
    data->img_width = 32;
    // get_right_texture(input, "NO");
    // data->texture1 = mlx_xpm_file_to_image(data->mlx, "texture/eagle.xpm", &data->img_width, &data->img_height);
    data->texture1 = mlx_xpm_file_to_image(data->mlx, get_right_texture(input, "NO"), &data->img_width, &data->img_height);
    data->texture2 = mlx_xpm_file_to_image(data->mlx, get_right_texture(input, "SO"), &data->img_width, &data->img_height);
    data->texture3 = mlx_xpm_file_to_image(data->mlx, get_right_texture(input, "EA"), &data->img_width, &data->img_height);
    data->texture4 = mlx_xpm_file_to_image(data->mlx, get_right_texture(input, "WE"), &data->img_width, &data->img_height);
    if (!data->texture1 || !data->texture2 || !data->texture3 || !data->texture4)
    {
        free_all_mlx(data);
        free_all(input, NULL, NULL, "❌ Error\none of images failed"); // i left it here
    }
    data->tex_data[NORTH] =  (int *)mlx_get_data_addr(data->texture1, &data->bpp, &data->size_line1, &data->endiane);
    data->tex_data[SOUTH] =  (int *)mlx_get_data_addr(data->texture2, &data->bpp, &data->size_line2, &data->endiane);
    data->tex_data[EAST] =  (int *)mlx_get_data_addr(data->texture3, &data->bpp, &data->size_line3, &data->endiane);
    data->tex_data[WEST] =  (int *)mlx_get_data_addr(data->texture4, &data->bpp, &data->size_line4, &data->endiane);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void put_pixel_into_frame(int x, int y, t_data* data, int color)
{
    int index;

    if (data->inside_win)
    {
        if (x >=  data->width|| y >= data->height || x < 0 || y < 0)
            return;
        index = y * data->len_line + x * 4;
        data->data[index] = color & 0xFF;
        data->data[index + 1] = (color >> 8) & 0xFF;
        data->data[index + 2] = (color >> 16) & 0xFF;
    }
    if (data->iside_win_map)
    {
        if (x >= data->wid_map || y >= data->hei_map || x < 0 || y < 0)
            return;
        index = y * data->len_line_map + x * data->bpp/8;
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

int get_nbr_color(t_color* color)
{
    int c;

    c = 0;
    c = c | color->arr[0] << 16;
    c = c | color->arr[1] << 8;
    c = c | color->arr[2];
    return (c);
}

void clear_screen(t_data* data)
{
    int i, j;
    data->inside_win = true;
    data->iside_win_map = true;
    int color_ciel = get_nbr_color(get_right_color(data->data_pars,"C"));
    int color_floor = get_nbr_color(get_right_color(data->data_pars,"F"));
    for (i = 0; i < (data->height)/2; i++)
    {
        for (j = 1; j < data->width; j++)
        {
            put_pixel_into_frame(j, i, data, color_ciel);
        }
    }
    for (i = (data->height)/2; i < data->height; i++)
    {
        for (j = 0; j < data->width; j++)
            put_pixel_into_frame(j, i, data,color_floor);
    }
    data->inside_win = false;
    for (i = 0; i < data->hei_map; i++)
    {
        for (j = 0; j < data->wid_map; j++)
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

bool is_correct_move(t_data* game,float sin_angle,float cos_angle)
{
    t_player* player;

    player = &game->player;
    if (player->up)
    {
        if (is_touch_wall(player->x  + cos_angle * SPEED  ,player->y  +  sin_angle * SPEED ,game,BLOCK))
            return (true);
    }
    if (player->down)
    {
        if (is_touch_wall(player->x  - cos_angle * SPEED ,player->y  - sin_angle * SPEED,game,BLOCK))
            return(true);
    }
    if (player->left)
    {
        if (is_touch_wall(player->x  + sin_angle * SPEED,player->y  - sin_angle * SPEED,game,BLOCK))
            return(true);
    }
    if (player->right)
    {
         if (is_touch_wall(player->x  - sin_angle * SPEED, player->y   + cos_angle * SPEED,game,BLOCK))
            return(true);
    }
    return (false);
}

bool is_correct_move_map(t_data* game,float sin_angle,float cos_angle)
{
    t_player* player;

    player = &game->player;
    if (player->up)
    {
        if (is_touch_wall(player->map_x   + cos_angle * SPEED,player->map_y   +  sin_angle * SPEED,game,BLOCK_MAP))
            return (true);
    }
    if (player->down)
    {
        if (is_touch_wall(player->map_x   - cos_angle * SPEED,player->map_y   - sin_angle * SPEED,game,BLOCK_MAP))
            return(true);
    }
    if (player->left)
    {
        if (is_touch_wall(player->map_x   + cos_angle * SPEED,player->map_y   - sin_angle * SPEED,game,BLOCK_MAP))
            return(true);
    }
    if (player->right)
    {
         if (is_touch_wall(player->map_x  - cos_angle * SPEED, player->map_y   + sin_angle * SPEED,game,BLOCK_MAP))
            return(true);
    }
    return (false);
}

t_dirs get_directions(RayCalculationData* ray_data)
{
    if (ray_data->side == 0)
    {
        if (ray_data->rayDirX > 0)
            return (EAST);
        else
            return (WEST);
    }
    else
    {
        if (ray_data->rayDirY > 0)
            return (SOUTH);
        else
            return (NORTH);
    }
}

void move_angle(t_player* player)
{
    if (player->turn_left)
        player->angle -= ANGLE_SPEED;
    if (player->turn_right)
        player->angle += ANGLE_SPEED;
    
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
}

void move_player(t_data* game,float cos_angle,float sin_angle)
{
    move_player_map(game,cos_angle,sin_angle);
    if (is_correct_move(game,sin_angle,cos_angle))
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

float sqr_two_point(float x, float y)
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
    fix_dist = sqr_two_point(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

int get_volum_color_base_dist(double dis,t_dirs direction)
{
    int color;
    unsigned int r,g,b;
    
    dis /= 50;
    
    if (dis < 1)
        dis = 1;
    r = 255/dis;
    g = 255/dis;
    b = 255/dis;
    return (r << 16 | g << 8 | b);

}

// void draw_view_ray(RayCalculationData ray_data,int i,t_data* data)
// {
//     double dist;
//     float hiegh;
//     bool hit_hor = false;
//     bool hit_ver = false;
//     int ray_x = (int )ray_data.sideDistX;
//     int ray_y = (int )ray_data.sideDistY;
//     int start_y;
//     int end;

//     dist = fixed_dist(data->player.x,data->player.y,ray_x,ray_y,data);
//      if (dist < 20)
//         dist = 20;
//     hiegh = (BLOCK / dist) * (data->width) ;
//     start_y = ((data->height + 90)- hiegh) / 2;
//     end = start_y + hiegh;
   
//     // double wall_x;
//     // if (ray_data.side == 1)
//     //     wall_x = fmod(ray_x, BLOCK) / BLOCK;
//     // else
//     //     wall_x = fmod(ray_x, BLOCK) / BLOCK;        
//     // int texX = (int)(wall_x * TEXTURE_WID);
//     // int top_pixel = (data->height - hiegh) / 2;
//     // int color;
//     //printf("this is len eall %f\n\n",dist);
//     while (start_y < end)
//     {
//         // int texY = (start_y - top_pixel) * ((double)TEXTURE_HEI / hiegh);
//         //color = data->tex_data[0][(TEXTURE_WID * texY) + texX];
//         //put_pixel_into_frame(i,start_y,data, color);
//         put_pixel_into_frame(i,start_y,data,get_volum_color_base_dist(dist,data->player.direction));
//         //put_pixel_into_frame(i,start_y,data, data->tex_data[0][0]);
//         start_y++;
//     }
// }

void draw_view_ray(float ray_x,float ray_y,int i,t_data* data, RayCalculationData* ray_data)
{
    double dist;
    float hiegh;
    bool hit_hor = false;
    bool hit_ver = false;
    int start_y;
    int end;


    dist = fixed_dist(data->player.x,data->player.y,ray_x,ray_y,data);
     if (dist < 0)
        dist = 1;
    hiegh = (BLOCK / dist) * (data->width) ;
    start_y = ((data->height)- hiegh) / 2;
    end = start_y + hiegh;
   
    // hi
    double wall_x;
    if (ray_data->side == 1)
        wall_x = fmod(ray_x, BLOCK) / BLOCK;
   else
        wall_x = fmod(ray_y, BLOCK) / BLOCK;        
    int texX = (int)(wall_x * TEXTURE_WID);
    int top_pixel = (data->height - hiegh) / 2;
    int color;
   
    while (start_y < end)
    {
        int texY = (start_y - top_pixel) * ((double)TEXTURE_HEI / hiegh);
        color = data->tex_data[ray_data->directins][(TEXTURE_WID * texY) + texX];
        put_pixel_into_frame(i,start_y,data, color);
        //put_pixel_into_frame(i,start_y,data,get_volum_color_base_dist(dist,data->player.direction));
        texY += 1;
    
        start_y++;
    }
}

void init_ray_position_and_direction(RayCalculationData* ray_data, t_data* game, float angle)
{
    ray_data->angle = angle;
    ray_data->posX = game->player.x / BLOCK;
    ray_data->posY = game->player.y / BLOCK;
    ray_data->rayDirX = cos(ray_data->angle);
    ray_data->rayDirY = sin(ray_data->angle);
    ray_data->mapX = (int)ray_data->posX;
    ray_data->mapY = (int)ray_data->posY;
}

void calculate_delta_distances(RayCalculationData* ray_data)
{
    ray_data->deltaDistX = (ray_data->rayDirX == 0) ? 1e30 : fabs(1.0 / ray_data->rayDirX);
    ray_data->deltaDistY = (ray_data->rayDirY == 0) ? 1e30 : fabs(1.0 / ray_data->rayDirY);
}

void calculate_initial_side_distances(RayCalculationData* ray_data)
{
    if (ray_data->rayDirX < 0)
    {
        ray_data->stepX = -1;
        ray_data->sideDistX = (ray_data->posX - ray_data->mapX) * ray_data->deltaDistX;

    }
    else
    {
        ray_data->stepX = 1;
        ray_data->sideDistX = (ray_data->mapX + 1.0 - ray_data->posX) * ray_data->deltaDistX;
    }

    if (ray_data->rayDirY < 0)
    {
        ray_data->stepY = -1;
        ray_data->sideDistY = (ray_data->posY - ray_data->mapY) * ray_data->deltaDistY;
    }
    else
    {
        ray_data->stepY = 1;
        ray_data->sideDistY = (ray_data->mapY + 1.0 - ray_data->posY) * ray_data->deltaDistY;
    }
}

void perform_dda_hit_detection(RayCalculationData* ray_data, t_data* game)
{
    ray_data->hit = false;
    ray_data->side = 0;
    while (!ray_data->hit)
    {
        if (ray_data->sideDistX < ray_data->sideDistY)
        {
            ray_data->sideDistX += ray_data->deltaDistX;
            ray_data->mapX += ray_data->stepX;
            ray_data->side = 0; // horizontal
        }
        else
        {
            ray_data->sideDistY += ray_data->deltaDistY;
            ray_data->mapY += ray_data->stepY;
            ray_data->side = 1; // vertical
        }
        if (ray_data->mapX < 0 || ray_data->mapX >= game->data_pars->long_line ||
            ray_data->mapY < 0 || ray_data->mapY >= game->data_pars->column - 6)
        {
            ray_data->hit = true;
            break;
        }
        if (game->map[ray_data->mapY][ray_data->mapX] == '1')
            ray_data->hit = true;
    }
    ray_data->directins = get_directions(ray_data);
}

void calculate_perpendicular_wall_distance(RayCalculationData* ray_data)
{
    if (ray_data->side == 0)
    {
        ray_data->perpWall = (ray_data->sideDistX - ray_data->deltaDistX);
    }
    else
    {
        ray_data->perpWall = (ray_data->sideDistY - ray_data->deltaDistY);
    }
    ray_data->perpWall *= BLOCK;
}

void calculate_drawing_coordinates(RayCalculationData* ray_data, t_data* game)
{
    ray_data->i = (int)ray_data->perpWall; // Use integer distance for drawing

    ray_data->draw_x = (game->player.x + cos(ray_data->angle) * ray_data->i);
    ray_data->draw_y = (game->player.y + sin(ray_data->angle) * ray_data->i);
}

void draw_ray_on_wind(RayCalculationData* ray_data, int j, t_data* game)
{
    game->iside_win_map = false; // Set flag before drawing

    draw_view_ray((int)ray_data->draw_x, (int)ray_data->draw_y, j, game, ray_data);
    game->iside_win_map = true;  // Reset flag after drawing
}

void ray_line(t_data *game, float angle, int j)
{
    RayCalculationData ray_data;

    init_ray_position_and_direction(&ray_data, game, angle);
    calculate_delta_distances(&ray_data);
    calculate_initial_side_distances(&ray_data);
    perform_dda_hit_detection(&ray_data, game);
    calculate_perpendicular_wall_distance(&ray_data);
    calculate_drawing_coordinates(&ray_data, game);
    draw_ray_on_wind(&ray_data, j, game);
}

void move_player_map(t_data* game,float cos_angle,float sin_angle)
{

    if (is_correct_move_map(game,sin_angle ,cos_angle ))
        return;
    move_angle(&game->player);
    game->player.map_x = (game->player.x / BLOCK);
    game->player.map_x *= BLOCK_MAP;
    game->player.map_y = (game->player.y / BLOCK);
    game->player.map_y *= BLOCK_MAP;
}

void draw_ray_map(t_data* data,float start_x)
{
    float cos_angle;
    float sin_angle;
    float ray_x;
    float ray_y;

    ray_x = data->player.map_x;
    ray_y = data->player.map_y;
    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
    data->iside_win_map = true;
    data->inside_win = false;
    while(!is_touch_wall(ray_x, ray_y, data,BLOCK_MAP))
    {
        put_pixel_into_frame(ray_x, ray_y, data, 0xFF0000);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    data->inside_win = true;
    data->iside_win_map = false;
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
    fraction = (PI / 3) / data->width;
    fraction_map = (PI / 3) / data->wid_map;
    start_x = player->angle - ((60 * PI/180)/2);
    start_x_map = start_x;
    clear_screen(data);
    move_player(data,cos(player->angle),sin(player->angle));
    draw_map(data);
    while (++i < data->width)
    {
        ray_line(data, start_x,i);
        if (i < data->wid_map)
        {
            draw_ray_map(data,start_x_map);
            start_x_map += fraction_map;
        }
        start_x += fraction;
    }
    
    mlx_put_image_to_window(data->mlx,data->win,data->img,0,0);
    mlx_put_image_to_window(data->mlx,data->win,data->img_map,0,(data->height - data->hei_map));
    return (0);
}

int main(int ac, char **av)
{
    t_data data;
    t_pars *input;

    input = check_inputs(ac, av, input);
    if (!input)
        return (1);
    init_game(&data,input);
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

