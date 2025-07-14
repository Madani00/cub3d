/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:04:47 by eamchart          #+#    #+#             */
/*   Updated: 2025/07/14 11:46:55 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initiaze_struct(t_data **data)
{
	(*data) = malloc(sizeof(t_data));
	(*data)->column = 0;
	(*data)->find.north = 0;
	(*data)->find.south = 0;
	(*data)->find.west = 0;
	(*data)->find.east = 0;
	(*data)->find.floor = 0;
	(*data)->find.ceiling = 0;
	(*data)->index_p = 0;
	(*data)->index_c = 0;
	(*data)->orientation = 0;
	(*data)->long_line = 0;
	(*data)->f_newline = false;
}


int invalid_character(char c)
{
	if (c != ' ' && c != '1' && c != 'N' \
		&& c != 'S' && c != 'E' && c != 'W' && c != '0')
			return (1);
	return (0);
}
void has_onlyspaces(t_data *data, int i)
{
	int j;
	
	j = 0;
	while (data->map_all[i][j])
	{
		if (data->map_all[i][j] != ' ' && data->map_all[i][j] != '\t')
			return ;
		j++;
	}
	free_all(data, NULL, NULL, "❌ Error\nline has only spaces");
}

void valid_map(t_data *data, int i)
{
	int j;
	
	j = 0;
	while (data->map_all[i][j])
	{
		if (ft_strchr("ENSW0", data->map_all[i][j]))
		{
			if (data->map_all[i][j] != '0')
				data->orientation++;
			if (i == 6 || j == 0 || j == (ft_strlen(data->map_all[i]) - 1) || i == data->column - 1)
				free_all(data, NULL, NULL, "❌ Error: l9nat fihom difo hhahah");
			if (data->map_all[i][j + 1] == ' ' || data->map_all[i][j - 1] == ' ' || data->map_all[i + 1][j] == ' ' || data->map_all[i - 1][j] == ' ' || j >= ft_strlen(data->map_all[i+1]) || j >= ft_strlen(data->map_all[i-1]))
				free_all(data, NULL, NULL, "❌ Error: one of the direction has a space");
		}		
		if (data->orientation > 1)	
			free_all(data, NULL, NULL, "❌ Error: more than one player’s orientation");
		if (invalid_character(data->map_all[i][j]))
			free_all(data, NULL, NULL, "❌ Error: something something something");
		j++;
		if (data->long_line < j)
			data->long_line = j;
	}
}

void check_map(t_data *data)
{
	int i;

	// printf("\n%d\n", data->column);
	i = 6;
	while (data->map_all[i])
	{
		//has_onlyspaces(data, i);
		valid_map(data, i);
		// 	free_all(data, NULL, NULL, "❌ Error: map is not valid");
		// else
		// 	printf("%c : valid\n", data->map_all[i][0]);
		i++;
	}
	if (data->orientation == 0)	
		free_all(data, NULL, NULL, "❌ Error: more NOT FOUND AT ALL");
}

void	adjust_map(t_data *data)
{
	int i;
	int j;
	int k;

	i = 5;
	k = 0;
	data->map = malloc(sizeof(char *) * (data->column - 5));
	if (!data->map)
		exit(EXIT_FAILURE);
	while (data->map_all[++i])
	{
		j = -1;
		data->map[k] = malloc(sizeof(char) * data->long_line);
		while (data->map_all[i][++j])
		{
			data->map[k][j] = data->map_all[i][j];
		}
		while (j < data->long_line)
		{
			data->map[k][j] = ' ';
			j++;
		}
		data->map[k++][j] = '\0';
	}
	data->map[k] = NULL;
}

void print_map(t_data *data)
{
	int i = 0;
	while (data->map[i])
	{
		
		printf("%s||\n", data->map[i]);
		i++;
	}
	
}

int	check_inputs(int ac, char *av[], t_data *data)
{
	if (ac != 2)
		return (printf("❌ Error\n in the number of arguments\n"));
	check_map_extension(av[1]);
	initiaze_struct(&data);
	read_file(av, data);
	check_configuration(data);
	check_map(data);
	printf("\n%d\n", data->long_line);
	adjust_map(data);
	print_map(data);
	return (0);
}