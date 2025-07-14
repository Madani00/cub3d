/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:00:00 by eamchart          #+#    #+#             */
/*   Updated: 2025/07/14 13:14:10 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_map_extension(char *map_file)
{
	char	*start;
	char *sec;

	start = &map_file[ft_strlen(map_file) - 4];
	if ((ft_strncmp(start, ".cub", 4) != 0) || \
		(ft_strncmp(map_file, ".cub", 4) == 0))
	{
		printf("❌ Error\nmap extension not valid\n");
		exit(EXIT_FAILURE);
	}
	sec = ft_strrchr(map_file, '/');
	if (sec && ft_strncmp(sec, "/.cub", 5) == 0)
	{
		printf("❌ Error\nmap extension not valid\n");
		exit(EXIT_FAILURE);
	}
}

void	allocate_map(char *all_lines, t_data *data)
{
	char	**lines;
	int		index;

	printf("true ?? : %d\n", data->f_newline);
	if (data->f_newline)
	{
		printf("found new line in the map\n");
		exit(EXIT_FAILURE);
	}
	lines = ft_split(all_lines, '\n');
	free(all_lines);
	data->map_all = malloc(sizeof(char *) * (data->column + 1));
	if (!data->map_all)
		exit(EXIT_FAILURE);
	index = 0;
	while (index < data->column)
	{
		data->map_all[index] = ft_strdup(lines[index]);
		index++;
	}
	data->map_all[index] = NULL;
	free_args(lines);
}
void  reach_map(char *line, t_data *data, bool reach)
{
	if (line[0] == ' ' || line[0] == '1')
		reach = true;
	else if (reach && strcmp(line, "\n") == 0)
		data->f_newline = true;
}

void	read_file(char **av, t_data *data)
{
	char	*line;
	int		fd;
	char	*all_lines;
	bool reach;

	reach = false;
	fd = open(av[1], O_RDONLY);
	all_lines = NULL;
	line = get_next_line(fd);
	if (!line)
		free_error(data, "❌ Error\nfile is empty");
	while (line != NULL)
	{
		if (line[0] == ' ' || line[0] == '1')
			reach = true;
		if (reach && strcmp(line, "\n") == 0)
			data->f_newline = true;
		
		// reach_map(line, data, reach);
		else if (strcmp(line, "\n") != 0)
		{
			all_lines = join(all_lines, line);
			data->column++;
		}
		free(line);
		line = get_next_line(fd);
	}
	//printf("%s\n", all_lines);
	allocate_map(all_lines, data);
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
