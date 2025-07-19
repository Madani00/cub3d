#ifndef CUB3D_H
# define CUB3D_H


# include "../Libft/libft.h"
// # include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 1

typedef struct config
{
    int north;
    int south;
    int west;
    int east;
    int floor;
    int ceiling;
} t_config;

typedef struct path
{
    char *iden;
    char *pth;
} t_path;

typedef struct color
{
    char *iden;
    int arr[3];
} t_color;


typedef struct data
{
    char **map_all;
    int column;
    bool f_newline;
    t_config find;
    t_path path[4];
    int index_p;
    t_color color[2];
    int index_c;
    int orientation;
    int long_line;
    char *direction;
    char **map;
} t_pars;


char	*get_next_line(int fd);
char	*allocation(int fd);
char	*fetch_line(char *buffer);
void	free_error(t_pars *data, char *msg);
char	*join(char *s1, char *s2);
void	free_args(char **arg);
void	free_lines(t_pars *data);
void	free_identifiers(t_pars *data);
int		ft_isnum(char *str);
int		num_length(char *str);
void    read_file(char **av, t_pars *data);
void	allocate_map(char *all_lines, t_pars *data);
void	check_map_extension(char *map_file);
int		check_inputs(int ac, char *av[], t_pars *data);
void	initiaze_struct(t_pars **data);
void	free_all(t_pars *data, char **configs, char **range, char *msg);
void	parse_paths(t_pars *data, int i);
void	parse_color(t_pars *data, int i);
void	identifier_duplicate(t_pars *data);
void	check_configuration(t_pars *data);
int		config_path_found(t_pars *data, int i);
int		config_color_found(t_pars *data, int i);
void	parse_color_helper(t_pars *data, char **configs, char **clr_range);
void	check_map(t_pars *data);
void	valid_map_helper(t_pars *data, int i, int j);
void	adjust_map(t_pars *data);
void	valid_map(t_pars *data, int i);
int		invalid_character(char c);
void    free_identifiers(t_pars *data);
void	path_texture(t_pars *data, char c);
char	*get_right_texture(t_pars *data, char *iden);
t_color	*get_right_color(t_pars *data, char *iden);



#endif