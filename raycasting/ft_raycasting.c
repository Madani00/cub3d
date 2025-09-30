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

void	draw_view_ray(int i, t_data *data, t_raycalculationdata *ray_data)
{
	int (color), (top_pixel);
	int (start_y), (end);
	ray_data->dist = fixed_dist(ray_data->draw_x, ray_data->draw_y, data);
	if (ray_data->dist < 0)
		ray_data->dist = 1;
	ray_data->hiegh = (BLOCK / ray_data->dist) * (WIDTH);
	start_y = ((HEIGHT) - ray_data->hiegh) / 2;
	end = start_y + ray_data->hiegh;
	if (ray_data->side == 1)
		ray_data->wall_x = fmod(ray_data->draw_x, BLOCK) / BLOCK;
	else
		ray_data->wall_x = fmod(ray_data->draw_y, BLOCK) / BLOCK;
	ray_data->tex_x = (int)(ray_data->wall_x * TEXTURE_WID);
	top_pixel = (HEIGHT - ray_data->hiegh) / 2;
	draw_ciel_flor(start_y, end, data, i);
	while (start_y < end)
	{
		ray_data->tex_y = (start_y - top_pixel) * ((double)TEXTURE_HEI
				/ ray_data->hiegh);
		color = data->tex_data[ray_data->directins][(TEXTURE_WID
				* ray_data->tex_y) + ray_data->tex_x];
		put_pixel_into_frame(i, start_y, data, color);
		start_y++;
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
