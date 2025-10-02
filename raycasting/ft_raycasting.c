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

void	draw_view_ray(int i, t_data *data, t_raycalculationdata *ray_data)
{
	int (color), (top_pixel);
	int (start_y), (end);
	ray_data->dist = ray_data->perp_wall * cos(ray_data->angle - data->player.angle);
	ray_data->hiegh = (int)((WIDTH ) / (ray_data->dist) - 28);
	start_y = (HEIGHT / 2) - (ray_data->hiegh / 2);
	end = (HEIGHT / 2) + (ray_data->hiegh / 2);
	if (start_y < 0)
		start_y = 0;
	if (end >= WIDTH)
		end = WIDTH - 1;
	if (ray_data->side == 0)
		ray_data->wall_x = data->player.y / BLOCK + ray_data->perp_wall * ray_data->ray_dir_y;
	else
		ray_data->wall_x = data->player.x / BLOCK + ray_data->perp_wall * ray_data->ray_dir_x;
	ray_data->wall_x -= floor(ray_data->wall_x);	
	ray_data->tex_x = (int)data->imgs[ray_data->directins].width * ray_data->wall_x;
	top_pixel = (HEIGHT - ray_data->hiegh) / 2;	
	draw_ciel_flor(start_y, end, data, i);
	while (start_y < end)
	{
		ray_data->tex_y = (start_y - top_pixel) * ((double)data->imgs[ray_data->directins].height / ray_data->hiegh);
		color = data->imgs[ray_data->directins].tex_data[(data->imgs[ray_data->directins].height * ray_data->tex_y) + ray_data->tex_x];
		put_pixel_into_frame(i,start_y,data,color);		
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
