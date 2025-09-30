/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 07:32:58 by aybouatr          #+#    #+#             */
/*   Updated: 2025/08/04 07:33:02 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	init_player(t_player *player, char **map)
{
	int (i), (j);
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
		{
			if (is_player_and_get_angle(player, map[i][j]))
			{
				player->x = (j * BLOCK) - 16;
				player->y = (i * BLOCK) - 16;
				map[i][j] = '0';
				return ;
			}
		}
	}
}

void	init_game_help(t_data *data, t_pars *input)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->data = mlx_get_data_addr(data->img, &data->bpp, &data->len_line,
			&data->endiane);
	data->img_height = 32;
	data->img_width = 32;
	data->img[NORTH].data = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
				"NO"), &data->imgs[NORTH].width , &data->imgs[NORTH].height);
	data->imgs[SOUTH].data = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
				"SO"), &data->imgs[SOUTH].width, &data->imgs[SOUTH].height);
	data->imgs[EAST].data = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
				"EA"), &data->imgs[EAST].width, &data->imgs[EAST].height);
	data->imgs[WEST].data = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
				"WE"), &data->imgs[WEST].width, &data->imgs[WEST].height);
	if (!data->imgs[NORTH] || !data->imgs[WEST] || !data->imgs[SOUTH]
		|| !data->imgs[EAST])
	{
		free_all_mlx(data);
		free_all(input, NULL, NULL, "❌ Error\none of images failed");
	}
}

void	init_game(t_data *data, t_pars *input)
{
	data->map = input->map;
	data->data_pars = input;
	init_player(&data->player, data->map);
	init_game_help(data, input);
	data->imgs[NORTH].tex_data = (int *)mlx_get_data_addr(data->img[NORTH].data, &data->bpp,
			data->imgs[NORTH].size_line, &data->endiane);
	data->imgs[SOUTH].tex_data = (int *)mlx_get_data_addr(data->img[SOUTH].data, &data->bpp,
			data->imgs[NORTH].size_line, &data->endiane);
	data->imgs[EAST].tex_data = (int *)mlx_get_data_addr(data->img[EAST].data, &data->bpp,
			data->imgs[EAST].size_line, &data->endiane);
	data->imgs[WEST].tex_data = (int *)mlx_get_data_addr(data->img[WEST].data, &data->bpp,
			data->imgs[WEST].size_line, &data->endiane);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	get_nbr_color(t_color *color)
{
	int	c;

	c = 0;
	c = c | color->arr[0] << 16;
	c = c | color->arr[1] << 8;
	c = c | color->arr[2];
	return (c);
}

void	put_pixel_into_frame(int x, int y, t_data *data, int color)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * data->len_line + x * 4;
	data->data[index] = color & 0xFF;
	data->data[index + 1] = (color >> 8) & 0xFF;
	data->data[index + 2] = (color >> 16) & 0xFF;
}
