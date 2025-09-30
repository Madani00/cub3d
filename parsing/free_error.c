/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:35:53 by eamchart          #+#    #+#             */
/*   Updated: 2025/07/31 10:34:20 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	free_lines(t_pars *data)
{
	int	i;

	i = 0;
	while (i < data->column)
	{
		free(data->map_all[i]);
		i++;
	}
	free(data->map_all);
}

void	free_error(t_pars *data, char *msg)
{
	free(data);
	if (msg)
		printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	free_identifiers(t_pars *data)
{
	int	index;

	index = 0;
	while (index < data->index_c)
	{
		free(data->color[index].iden);
		index++;
	}
	index = 0;
	while (index < data->index_p)
	{
		free(data->path[index].iden);
		free(data->path[index].pth);
		index++;
	}
}

void	free_all(t_pars *data, char **configs, char **range, char *msg)
{
	free_identifiers(data);
	if (configs != NULL)
		free_args(configs);
	if (range != NULL)
		free_args(range);
	free_lines(data);
	free_error(data, msg);
}
