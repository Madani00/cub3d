/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 07:33:32 by aybouatr          #+#    #+#             */
/*   Updated: 2025/08/04 07:33:36 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

float	fixed_dist(float x2, float y2, t_data *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - game->player.x;
	delta_y = y2 - game->player.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = sqr_two_point(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

int	get_texture_color(img_info *texture, int tex_x, int tex_y)
{
	int	color;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width )
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height )
		tex_y = texture->height - 1;
	color = *(unsigned int *)(texture->tex_data + tex_y * texture->size_line + tex_x * (texture->bpp / 8));
	return (color);
}


// void	fish_eye_and_texture_x_position(t_rerenderinit_utils_variables *v,
// 	t_globaldata *t, double *ray_angle)
// {
// 	(*v).corrected_dist = (*v).perp_wall_dist * cos(*ray_angle - t->player.angler);
// 	(*v).perp_wall_on_screen = (int)(WIN_HEIGHT / (*v).corrected_dist);

// 	(*v).start_draw = (WIN_HEIGHT / 2) - ((*v).perp_wall_on_screen / 2);
// 	(*v).end_draw = (WIN_HEIGHT / 2) + ((*v).perp_wall_on_screen / 2);

// 	if ((*v).start_draw < 0)
// 		(*v).start_draw = 0;
// 	if ((*v).end_draw >= WIN_HEIGHT)
// 		(*v).end_draw = WIN_HEIGHT - 1;

// 	if ((*v).side == 0)
// 		(*v).wall_hit_x_in_texture = t->player.py / TILE_SIZE + (*v).perp_wall_dist * (*v).ray_dir_y;
// 	else
// 		(*v).wall_hit_x_in_texture = t->player.px / TILE_SIZE + (*v).perp_wall_dist * (*v).ray_dir_x;
// 	(*v).wall_hit_x_in_texture -= floor((*v).wall_hit_x_in_texture);
// }

// /*
//                  _rerenderinit util;
// */

// void	fetch_walls(t_rerenderinit_utils_variables *v,
// 	t_globaldata *t, int line_index)
// {
// 	(*v).tex_x = (int)((*v).wall_hit_x_in_texture * t->wrapper[(*v).texture_index].width);


// 	(*v).texture_step = (double)t->wrapper[(*v).texture_index].height / (double)(*v).perp_wall_on_screen;

// 	(*v).tex_y = ((*v).start_draw - WIN_HEIGHT / 2.0 + (*v).perp_wall_on_screen / 2.0) * (*v).texture_step;

// 	(*v).tindex = (*v).start_draw - 1;
// 	//
// 	while (++((*v).tindex) < (*v).end_draw)
// 	{
// 		my_mlx_pixel_put(&t->img, line_index, (*v).tindex, get_texture_color(&t->wrapper[(*v).texture_index], (*v).tex_x, (int)(*v).tex_y));
// 		(*v).tex_y += (*v).texture_step;
// 	}
// }



void	draw_view_ray(int i, t_data *data, t_raycalculationdata *ray_data)
{
	int (color), (top_pixel);
	double step;
	int (start_y), (end);

	ray_data->dist = ray_data->perp_wall * cos(ray_data->angle - data->player.angle);
	ray_data->hiegh = (int)((WIDTH ) / (ray_data->dist ));

	start_y = (HEIGHT / 2) - (ray_data->hiegh / 2);
	end = (HEIGHT / 2) + (ray_data->hiegh / 2);

	if (start_y < 0)
		start_y = 0;
	if (end >= WIDTH)
		end = WIDTH - 1;

	draw_ciel_flor(start_y, end, data, i);

	//	if ((*v).side == 0)
// 		(*v).wall_hit_x_in_texture = t->player.py / TILE_SIZE + (*v).perp_wall_dist * (*v).ray_dir_y;
// 	else
// 		(*v).wall_hit_x_in_texture = t->player.px / TILE_SIZE + (*v).perp_wall_dist * (*v).ray_dir_x;
// 	(*v).wall_hit_x_in_texture -= floor((*v).wall_hit_x_in_texture);


	if (ray_data->side == 0)
		 ray_data->wall_x = data->player.y / BLOCK + ray_data->perp_wall * ray_data->ray_dir_y;
	else
		 ray_data->wall_x = data->player.x / BLOCK + ray_data->perp_wall * ray_data->ray_dir_x;
	ray_data->wall_x -= floor(ray_data->wall_x);
	
	ray_data->tex_x = (int)data->imgs[ray_data->directins].width * ray_data->wall_x;
	
	step =  ((double)data->imgs[ray_data->directins].height / (double)ray_data->dist);
		
	top_pixel = (HEIGHT - ray_data->hiegh) / 2;
	
	while (start_y < end)
	{
		ray_data->tex_y = (start_y - top_pixel) * ((double)data->imgs[ray_data->directins].height / ray_data->hiegh);
		
		color = data->imgs[ray_data->directins].tex_data[(data->imgs[ray_data->directins].height * ray_data->tex_y) + ray_data->tex_x];

		put_pixel_into_frame(i,start_y,data,color);

		ray_data->tex_y += step;
		
		start_y += 1;

	}
}

void	init_ray_position_and_direction(t_raycalculationdata *ray_data,
		t_data *game, float angle)
{
	ray_data->angle = angle;
	ray_data->pos_x = game->player.x / BLOCK;
	ray_data->pos_y = game->player.y / BLOCK;
	ray_data->ray_dir_x = cos(ray_data->angle);
	ray_data->ray_dir_y = sin(ray_data->angle);
	ray_data->map_x = (int)ray_data->pos_x;
	ray_data->map_y = (int)ray_data->pos_y;
}

void	calculate_delta_distances(t_raycalculationdata *ray_data)
{
	if (ray_data->ray_dir_x == 0)
		ray_data->delta_dist_x = 1e30;
	else
		ray_data->delta_dist_x = fabs(1.0 / ray_data->ray_dir_x);
	if (ray_data->ray_dir_y == 0)
		ray_data->delta_dist_y = 1e30;
	else
		ray_data->delta_dist_y = fabs(1.0 / ray_data->ray_dir_y);
}

int	ft_performent(t_data *data)
{
	t_player	*player;
	int			i;
	float		start_x;
	double		fraction;

	player = &data->player;
	i = -1;
	fraction = POV / WIDTH;
	start_x = player->angle - (POV / 2);
	move_player(data, cos(player->angle), sin(player->angle));
	while (++i < WIDTH)
	{
		ray_line(data, start_x, i);
		start_x += fraction;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
