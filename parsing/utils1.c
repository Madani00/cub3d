/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:04:47 by eamchart          #+#    #+#             */
/*   Updated: 2025/07/19 14:52:45 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	initiaze_struct(t_pars **data)
{
	(*data) = malloc(sizeof(t_pars));
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


void print_map(t_pars *data)
{
	int i = 0;
	while (data->map[i])
	{
		printf("%s||\n", data->map[i]);
		i++;
	}
	
}

int	num_length(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 3 && str[0] != '0')
		return (1);
	else if (len < 3)
		return (0);
	if (ft_strncmp(str, "255", 3) >= 0)
		return (1);
	return (0);
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (num_length(&str[i]))
		return (1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

t_color	*get_right_color(t_pars *data, char *iden)
{
	int	i;

	i = 0;
	while (i < data->index_c)
	{
		if (ft_strcmp(iden, data->color[i].iden) == 0)
			return (&data->color[i]);
		i++;
	}
	return (NULL);
}

int	check_inputs(int ac, char *av[], t_pars *data)
{
	if (ac != 2)
		return (printf("❌ Error\n in the number of arguments\n"));
	check_map_extension(av[1]);
	initiaze_struct(&data);
	read_file(av, data);
	check_configuration(data);
	check_map(data);
	adjust_map(data);
	//print_map(data);
	return (0);
}