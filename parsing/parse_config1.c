/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:21:56 by eamchart          #+#    #+#             */
/*   Updated: 2025/07/19 10:02:47 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	config_path_found(t_pars *data, int i)
{
	if (ft_strncmp(data->map_all[i], "NO", 2) == 0)
		return (data->find.north++, 1);
	else if (ft_strncmp(data->map_all[i], "SO", 2) == 0)
		return (data->find.south++, 1);
	else if (ft_strncmp(data->map_all[i], "WE", 2) == 0)
		return (data->find.west++, 1);
	else if (ft_strncmp(data->map_all[i], "EA", 2) == 0)
		return (data->find.east++, 1);
	else
		return (0);
}

int	config_color_found(t_pars *data, int i)
{
	if (ft_strncmp(data->map_all[i], "F", 1) == 0)
		return (data->find.floor++, 1);
	else if (ft_strncmp(data->map_all[i], "C", 1) == 0)
		return (data->find.ceiling++, 1);
	else
		return (0);
}

void	identifier_duplicate(t_pars *data)
{
	if (data->find.floor > 1 || data->find.ceiling > 1 || data->find.north > 1
		|| data->find.south > 1 || data->find.west > 1 || data->find.east > 1)
	{
		free_all(data, NULL, NULL, "❌ Error\nidentifier is duplicated");
	}
}
