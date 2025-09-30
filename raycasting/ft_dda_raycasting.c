/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 07:32:04 by aybouatr          #+#    #+#             */
/*   Updated: 2025/08/06 10:06:11 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	calculate_initial_side_distances(t_raycalculationdata *ray_data)
{
	if (ray_data->ray_dir_x < 0)
	{
		ray_data->step_x = -1;
		ray_data->side_dist_x = (ray_data->pos_x - ray_data->map_x)
			* ray_data->delta_dist_x;
	}
	else
	{
		ray_data->step_x = 1;
		ray_data->side_dist_x = (ray_data->map_x + 1.0 - ray_data->pos_x)
			* ray_data->delta_dist_x;
	}
	if (ray_data->ray_dir_y < 0)
	{
		ray_data->step_y = -1;
		ray_data->side_dist_y = (ray_data->pos_y - ray_data->map_y)
			* ray_data->delta_dist_y;
	}
	else
	{
		ray_data->step_y = 1;
		ray_data->side_dist_y = (ray_data->map_y + 1.0 - ray_data->pos_y)
			* ray_data->delta_dist_y;
	}
}

void	perform_dda_hit_detection(t_raycalculationdata *ray_data, t_data *game)
{
	while (!ray_data->hit)
	{
		if (ray_data->side_dist_x < ray_data->side_dist_y)
		{
			ray_data->side_dist_x += ray_data->delta_dist_x;
			ray_data->map_x += ray_data->step_x;
			ray_data->side = 0;
		}
		else
		{
			ray_data->side_dist_y += ray_data->delta_dist_y;
			ray_data->map_y += ray_data->step_y;
			ray_data->side = 1;
		}
		if (ray_data->map_x < 0 || ray_data->map_x >= game->data_pars->long_line
			|| ray_data->map_y < 0 || ray_data->map_y >= game->data_pars->column
			- 6)
		{
			ray_data->hit = true;
			break ;
		}
		if (game->map[ray_data->map_y][ray_data->map_x] == '1')
			ray_data->hit = true;
	}
	ray_data->directins = get_directions(ray_data);
}

void	calculate_perpendicular_wall_distance(t_raycalculationdata *ray_data)
{
	if (ray_data->side == 0)
	{
		ray_data->perp_wall = (ray_data->side_dist_x - ray_data->delta_dist_x);
	}
	else
	{
		ray_data->perp_wall = (ray_data->side_dist_y - ray_data->delta_dist_y);
	}
	ray_data->perp_wall *= BLOCK;
}

void	calculate_drawing_coordinates(t_raycalculationdata *ray_data,
		t_data *game)
{
	ray_data->i = (int)ray_data->perp_wall;
	ray_data->draw_x = (game->player.x + cos(ray_data->angle) * ray_data->i);
	ray_data->draw_y = (game->player.y + sin(ray_data->angle) * ray_data->i);
}

void	ray_line(t_data *game, float angle, int j)
{
	t_raycalculationdata	ray_data;

	init_ray_position_and_direction(&ray_data, game, angle);
	calculate_delta_distances(&ray_data);
	calculate_initial_side_distances(&ray_data);
	ray_data.hit = false;
	perform_dda_hit_detection(&ray_data, game);
	calculate_perpendicular_wall_distance(&ray_data);
	calculate_drawing_coordinates(&ray_data, game);
	draw_view_ray(j, game, &ray_data);
}
