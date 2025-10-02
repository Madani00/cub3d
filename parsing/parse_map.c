/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:20:32 by eamchart          #+#    #+#             */
/*   Updated: 2025/08/06 10:04:05 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	invalid_character(char c)
{
	if (c != ' ' && c != '1' && c != 'N' \
		&& c != 'S' && c != 'E' && c != 'W' && c != '0')
		return (1);
	return (0);
}

void	valid_map_helper(t_pars *data, int i, int j)
{
	if (data->map_all[i][j] != '0')
	{
		path_texture(data, data->map_all[i][j]);
		data->orientation++;
	}
	if (i == 6 || j == 0 || j == (ft_strlen(data->map_all[i]) - 1) || \
		i == data->column - 1)
		free_all(data, NULL, NULL, "❌ Error\nMap is not closed");
	if (j >= ft_strlen(data->map_all[i + 1]) || \
		j >= ft_strlen(data->map_all[i - 1]) || \
		data->map_all[i][j + 1] == ' ' || \
		data->map_all[i][j - 1] == ' ' || \
		data->map_all[i + 1][j] == ' ' || \
		data->map_all[i - 1][j] == ' ')
		free_all(data, NULL, NULL, "❌ Error\nMap is not closed");
}

void	valid_map(t_pars *data, int i)
{
	int	j;

	j = 0;
	while (data->map_all[i][j])
	{
		if (ft_strchr("ENSW0", data->map_all[i][j]))
		{
			valid_map_helper(data, i, j);
		}
		if (data->orientation > 1)
			free_all(data, NULL, NULL, "❌ Error\nMore than one orientation");
		if (invalid_character(data->map_all[i][j]))
			free_all(data, NULL, NULL, "❌ Error\nInvalid character found");
		j++;
		if (data->long_line < j)
			data->long_line = j;
	}
}

void	adjust_map(t_pars *data)
{
	int	i;
	int	j;
	int	k;

	i = 5;
	k = 0;
	data->map = malloc(sizeof(char *) * (data->column - 5));
	if (!data->map)
		exit(EXIT_FAILURE);
	while (data->map_all[++i])
	{
		j = -1;
		data->map[k] = malloc(sizeof(char) * data->long_line + 1);
		while (data->map_all[i][++j])
			data->map[k][j] = data->map_all[i][j];
		while (j < data->long_line)
		{
			data->map[k][j] = ' ';
			j++;
		}
		data->map[k++][j] = '\0';
	}
	data->map[k] = NULL;
}

void	check_map(t_pars *data)
{
	int	i;

	i = 6;
	while (data->map_all[i])
	{
		valid_map(data, i);
		i++;
	}
	if (data->orientation == 0)
		free_all(data, NULL, NULL, "❌ Error\nNo player orientation found");
}
