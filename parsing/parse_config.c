/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:07:20 by eamchart          #+#    #+#             */
/*   Updated: 2025/07/18 14:33:13 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_paths(t_data *data, int i)
{
	char	**configs;
	int		numb;
	char	*exten;

	numb = 0;
	configs = ft_split2(data->map_all[i], " \t");
	while (configs[numb] != NULL)
		numb++;
	if (numb != 2 || ft_strlen(configs[0]) != 2)
		free_all(data, configs, NULL, \
			"❌ Error\nPath identifier has no or more arguments");
	exten = &configs[1][ft_strlen(configs[1]) - 4];
	if ((ft_strncmp(exten, ".xpm", 4) != 0) || \
		(ft_strncmp(configs[1], ".xpm", 4) == 0))
		free_all(data, configs, NULL, "❌ Error\nfile extension is not valid");
	data->path[data->index_p].iden = ft_strdup(configs[0]);
	data->path[data->index_p++].pth = ft_strdup(configs[1]);
	free_args(configs);
}

void	parse_color_helper(t_data *data, char **configs, char **clr_range)
{
	int	numb;

	numb = 0;
	while (clr_range[numb] != NULL)
		numb++;
	if (numb != 3)
		free_all(data, configs, clr_range, \
			"❌ Error\nColor identifier has no or more arguments");
	numb = 0;
	while (clr_range[numb] != NULL)
	{
		if (!ft_isnum(clr_range[numb]))
		{
			data->color[data->index_c].arr[numb] = ft_atoi(clr_range[numb]);
		}
		else
			free_all(data, configs, clr_range, "❌ Error\nin the color range");
		numb++;
	}
	data->color[data->index_c].iden = ft_strdup(configs[0]);
}

void	parse_color(t_data *data, int i)
{
	char	**configs;
	int		numb;
	char	**clr_range;

	numb = 0;
	configs = ft_split2(data->map_all[i], " \t");
	while (configs[numb] != NULL)
		numb++;
	if (numb != 2 || ft_strlen(configs[0]) != 1 || configs[1][0] == ',' \
		|| configs[1][ft_strlen(configs[1]) - 1] == ',')
		free_all(data, configs, NULL, "❌ Error\nColor has no or more args");
	clr_range = ft_split(configs[1], ',');
	parse_color_helper(data, configs, clr_range);
	data->index_c++;
	free_args(clr_range);
	free_args(configs);
}

int	all_identifiers_found(t_data *data)
{
	if (data->find.floor == 1 && data->find.ceiling == 1 && \
		data->find.north == 1 && data->find.south == 1 && \
		data->find.west == 1 && data->find.east == 1)
	{
		return (0);
	}
	return (1);
}

void	check_configuration(t_data *data)
{
	int	i;

	i = 0;
	while (data->map_all[i] && i < 6)
	{
		if (config_path_found(data, i))
			parse_paths(data, i);
		else if (config_color_found(data, i))
			parse_color(data, i);
		else
			free_all(data, NULL, NULL, "❌ Error\nIs not a valid identifier");
		identifier_duplicate(data);
		i++;
	}
	if (data->f_newline)
		free_all(data, NULL, NULL, "❌ Error\nNewline encountered in MAP");
}
