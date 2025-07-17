/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:04:47 by eamchart          #+#    #+#             */
/*   Updated: 2025/07/15 19:05:34 by eamchart         ###   ########.fr       */
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
	adjust_map(data);
	print_map(data);
	return (0);
}