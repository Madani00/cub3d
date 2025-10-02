/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 07:32:58 by aybouatr          #+#    #+#             */
/*   Updated: 2025/10/02 13:06:22 by eamchart         ###   ########.fr       */
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
				player->x = (j * BLOCK) + (BLOCK/2);
				player->y = (i * BLOCK) + (BLOCK/2);
				map[i][j] = '0';
				return ;
			}
		}
	}
}

void	init_game_help(t_data *data, t_pars *input)
{
	data->mlx = mlx_init();
	data->win = NULL;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->data = mlx_get_data_addr(data->img, &data->bpp, &data->len_line, &data->endiane);
	data->img_height = 32;
	data->img_width = 32;
	data->imgs[NORTH].data = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
				"NO"), &data->imgs[NORTH].width , &data->imgs[NORTH].height);
	data->imgs[SOUTH].data = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
				"SO"), &data->imgs[SOUTH].width, &data->imgs[SOUTH].height);
	data->imgs[EAST].data = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
				"EA"), &data->imgs[EAST].width, &data->imgs[EAST].height);
	data->imgs[WEST].data = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
				"WE"), &data->imgs[WEST].width, &data->imgs[WEST].height);

	if (!data->imgs[NORTH].data || !data->imgs[WEST].data || !data->imgs[SOUTH].data
		|| !data->imgs[EAST].data)
	{
		free_all_mlx(data);
		free_all(input, NULL, NULL, "❌ Error\none of images failed");
	}
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");

}

void	init_game(t_data *data, t_pars *input)
{
	data->map = input->map;
	data->data_pars = input;
	init_player(&data->player, data->map);
	init_game_help(data, input);
	data->imgs[NORTH].tex_data = (int *)mlx_get_data_addr(data->imgs[NORTH].data, &data->imgs[NORTH].bpp ,
			&data->imgs[NORTH].size_line, &data->endiane);
	data->imgs[SOUTH].tex_data = (int *)mlx_get_data_addr(data->imgs[SOUTH].data, &data->imgs[SOUTH].bpp,
			&data->imgs[NORTH].size_line, &data->endiane);
	data->imgs[EAST].tex_data = (int *)mlx_get_data_addr(data->imgs[EAST].data, &data->imgs[EAST].bpp,
			&data->imgs[EAST].size_line, &data->endiane);
	data->imgs[WEST].tex_data = (int *)mlx_get_data_addr(data->imgs[WEST].data,&data->imgs[WEST].bpp,
			&data->imgs[WEST].size_line, &data->endiane);
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




// void	init_player(t_player *player, char **map)
// {
// 	int (i), (j);
// 	i = -1;
// 	player->angle = PI / 2;
// 	player->turn_left = false;
// 	player->turn_right = false;
// 	player->down = false;
// 	player->left = false;
// 	player->right = false;
// 	player->up = false;
// 	while (map && map[++i] != NULL)
// 	{
// 		j = -1;
// 		while (map[i][++j] != '\0')
// 		{
// 			if (is_player_and_get_angle(player, map[i][j]))
// 			{
// 				player->x = (j * BLOCK) - 16;
// 				player->y = (i * BLOCK) - 16;
// 				map[i][j] = '0';
// 				return ;
// 			}
// 		}
// 	}
// }

// void	init_game_help(t_data *data, t_pars *input)
// {
// 	data->mlx = mlx_init();
// 	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
// 	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
// 	data->data = mlx_get_data_addr(data->img, &data->bpp, &data->len_line,
// 			&data->endiane);
// 	data->img_height = 32;
// 	data->img_width = 32;
// 	data->texture1 = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
// 				"NO"), &data->img_width, &data->img_height);
// 	data->texture2 = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
// 				"SO"), &data->img_width, &data->img_height);
// 	data->texture3 = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
// 				"EA"), &data->img_width, &data->img_height);
// 	data->texture4 = mlx_xpm_file_to_image(data->mlx, get_right_texture(input,
// 				"WE"), &data->img_width, &data->img_height);
// 	if (!data->texture1 || !data->texture2 || !data->texture3
// 		|| !data->texture4)
// 	{
// 		free_all_mlx(data);
// 		free_all(input, NULL, NULL, "❌ Error\none of images failed");
// 	}
// }

// void	init_game(t_data *data, t_pars *input)
// {
// 	data->map = input->map;
// 	data->data_pars = input;
// 	init_player(&data->player, data->map);
// 	init_game_help(data, input);
// 	data->tex_data[NORTH] = (int *)mlx_get_data_addr(data->texture1, &data->bpp,
// 			&data->size_line1, &data->endiane);
// 	data->tex_data[SOUTH] = (int *)mlx_get_data_addr(data->texture2, &data->bpp,
// 			&data->size_line2, &data->endiane);
// 	data->tex_data[EAST] = (int *)mlx_get_data_addr(data->texture3, &data->bpp,
// 			&data->size_line3, &data->endiane);
// 	data->tex_data[WEST] = (int *)mlx_get_data_addr(data->texture4, &data->bpp,
// 			&data->size_line4, &data->endiane);
// 	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
// }

// int	get_nbr_color(t_color *color)
// {
// 	int	c;

// 	c = 0;
// 	c = c | color->arr[0] << 16;
// 	c = c | color->arr[1] << 8;
// 	c = c | color->arr[2];
// 	return (c);
// }

// void	put_pixel_into_frame(int x, int y, t_data *data, int color)
// {
// 	int	index;

// 	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
// 		return ;
// 	index = y * data->len_line + x * 4;
// 	data->data[index] = color & 0xFF;
// 	data->data[index + 1] = (color >> 8) & 0xFF;
// 	data->data[index + 2] = (color >> 16) & 0xFF;
// }
