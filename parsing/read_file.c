/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:00:00 by eamchart          #+#    #+#             */
/*   Updated: 2025/07/18 14:30:06 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_map_extension(char *map_file)
{
	char	*start;
	char	*sec;

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

	// if (data->f_newline)
	// {
	// 	free(all_lines);
	// 	free_error(data, "❌ Error\nNewline encountered in MAP");
	// }
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

void	reach_map(char *line, t_data *data, bool reach)
{
	if (line[0] == ' ' || line[0] == '1')
		reach = true;
	else if (reach && strcmp(line, "\n") == 0)
		data->f_newline = true;
}

char	*get_first_line(int fd, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		free_error(data, "❌ Error\nfile is empty");
	return (line);
}

void	read_file(char **av, t_data *data)
{
	char	*line;
	int		fd;
	char	*all_lines;
	bool	reach;

	reach = false;
	fd = open(av[1], O_RDONLY);
	all_lines = NULL;
	line = get_first_line(fd, data);
	while (line != NULL)
	{
		if (line[0] == ' ' || line[0] == '1')
			reach = true;
		if (reach && strcmp(line, "\n") == 0)
			data->f_newline = true;
		else if (strcmp(line, "\n") != 0)
		{
			all_lines = join(all_lines, line);
			data->column++;
		}
		free(line);
		line = get_next_line(fd);
	}
	allocate_map(all_lines, data);
}
