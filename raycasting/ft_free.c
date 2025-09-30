/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 07:32:35 by aybouatr          #+#    #+#             */
/*   Updated: 2025/08/04 07:32:39 by aybouatr         ###   ########.fr       */
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
