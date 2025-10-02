/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 07:32:35 by aybouatr          #+#    #+#             */
/*   Updated: 2025/10/02 13:07:00 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	close_window(t_data *game)
{
	free_all_mlx(game);
	free_all(game->data_pars, NULL, NULL, NULL);
	return (0);
}

void	free_images(t_data *data)
{
	if (data->imgs[SOUTH].data)
		mlx_destroy_image(data->mlx, data->imgs[SOUTH].data);
	if (data->imgs[EAST].data)
		mlx_destroy_image(data->mlx, data->imgs[EAST].data);
	if (data->imgs[NORTH].data)
		mlx_destroy_image(data->mlx, data->imgs[NORTH].data);
	if (data->imgs[WEST].data)
		mlx_destroy_image(data->mlx, data->imgs[WEST].data);
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
	free_args(data->map);
	free_images(data);
	free_minilbx(data);
}

void	draw_ciel_flor(int start_y, int end_y, t_data *data, int x)
{
	int	i;
	int	color_ciel;
	int	color_floor;

	i = -1;
	color_ciel = get_nbr_color(get_right_color(data->data_pars, "C"));
	color_floor = get_nbr_color(get_right_color(data->data_pars, "F"));
	while (++i < start_y)
		put_pixel_into_frame(x, (start_y - i), data, color_ciel);
	i = 0;
	while ((++i + end_y) < HEIGHT)
		put_pixel_into_frame(x, (end_y + i), data, color_floor);
}
