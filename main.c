/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 07:33:56 by aybouatr          #+#    #+#             */
/*   Updated: 2025/08/04 07:33:58 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

bool	is_player_and_get_angle(t_player *player, int c)
{
	if (c == 'N')
	{
		player->angle = (PI * 3) / 2;
		return (true);
	}
	else if (c == 'S')
	{
		player->angle = PI / 2;
		return (true);
	}
	else if (c == 'W')
	{
		player->angle = PI;
		return (true);
	}
	else if (c == 'E')
	{
		player->angle = 0;
		return (true);
	}
	return (false);
}

t_dirs	get_directions(t_raycalculationdata *ray_data)
{
	if (ray_data->side == 0)
	{
		if (ray_data->ray_dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray_data->ray_dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

bool	touch_wall(float x_ray, float y_ray, t_data *data, int block)
{
	int	x;
	int	y;

	x = x_ray / block;
	y = y_ray / block;
	if (data->map[y][x] == '1')
		return (true);
	return (false);
}

bool	is_touch_wall(float x_ray, float y_ray, t_data *data, int block)
{
	// return (touch_wall(x_ray + 1,y_ray + 1 ,data,block) 
	// 		|| touch_wall(x_ray - 1,y_ray - 1 ,data,block)
	// 		|| touch_wall(x_ray + 1,y_ray - 1 ,data,block)
	// 		|| touch_wall(x_ray - 1,y_ray + 1 ,data,block)
	// 		);

	int	x;
	int	y;

	x = x_ray / block;
	y = y_ray / block;
	if (data->map[y][x] == '1')
		return (true);
	return (false);

}

float	sqr_two_point(float x, float y)
{
	return (sqrt(x * x + y * y));
}

int	main(int ac, char **av)
{
	t_data	data;
	t_pars	*input;

	input = NULL;
	input = check_inputs(ac, av, input);
	if (!input)
		return (1);
	init_game(&data, input);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, ft_performent, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
