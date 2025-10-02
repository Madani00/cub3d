/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 08:33:50 by aybouatr          #+#    #+#             */
/*   Updated: 2025/10/02 10:30:15 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.14159265359
# define BLOCK 64
# define ANGLE_SPEED 0.006
# define SPEED 0.8
# define HEIGHT 720
# define WIDTH 1280
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100
# define SPACE 32
# define TEXTURE_WID 64
# define TEXTURE_HEI 64
# define POV (PI/3)

typedef enum e_dirs
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}				t_dirs;

typedef struct s_player
{
	float		x;
	float		y;
	float		map_x;
	float		map_y;
	float		angle;
	t_dirs		direction;
	bool		up;
	bool		down;
	bool		left;
	bool		right;
	bool		turn_left;
	bool		turn_right;
	bool		door_open;

}				t_player;

typedef struct t_raycalculationdata
{
	double		angle;
	double		pos_x;
	double		pos_y;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	bool		hit;
	int			side;
	t_dirs		directins;
	double		perp_wall;
	double		draw_x;
	double		draw_y;
	double		dist;
	float		hiegh;
	int		tex_x;
	double		wall_x;
	int			tex_y;
	int			i;
}				t_raycalculationdata;

typedef struct img_info
{
	void *data; // texture
	int *tex_data;
	int height;
	int width;
	int bpp;
	int size_line;
}img_info;


typedef struct s_xy
{
   double x;
   double y;
}t_xy;


typedef struct s_ray
{
	t_xy			hit;
	t_dirs			direction;
}					t_ray;

typedef struct RayCalculationData 
{    
    double angle;
    double posX;
    double posY;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double deltaDistX;
    double deltaDistY;
    int stepX;
    int stepY;
    double sideDistX;
    double sideDistY;
    bool hit;
    int side;
    t_dirs directins;
    double perpWall;
    double draw_x;
    double draw_y;
    int i;
} RayCalculationData;

typedef struct s_data
{
	void		*texture1;
	void		*texture2;
	void		*texture3;
	void		*texture4;
	int			size_line1;
	int			size_line2;
	int			size_line3;
	int			size_line4;


	void		*win;
	void		*mlx;
	void		*img;
	char		*data;
	char		**map;
	t_pars		*data_pars;
	int			bpp;
	int			len_line;
	int			endiane;

	int			img_width; //
	int			img_height; //
	int			*tex_data[4];
	img_info	imgs[4];
	
	t_player	player;
	double		last_hit_wall_dist;
	int			last_hit_side;
}				t_data;


bool	touch_wall(float x_ray, float y_ray, t_data *data, int block);
bool			is_player_and_get_angle(t_player *player, int c);
void			init_player(t_player *player, char **map);
int				close_window(t_data *game);
void			free_images(t_data *data);
void			free_minilbx(t_data *data);
void			free_all_mlx(t_data *data);
void			init_game_help(t_data *data, t_pars *input);
void			init_game(t_data *data, t_pars *input);
void			put_pixel_into_frame(int x, int y, t_data *data, int color);
int				get_nbr_color(t_color *color);
void			draw_ciel_flor(int start_y, int end_y, t_data *data, int x);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
bool			is_correct_move(t_data *game, float sin_angle, float cos_angle);
t_dirs			get_directions(t_raycalculationdata *ray_data);
void			move_angle(t_player *player);
void			move_player(t_data *game, float cos_angle, float sin_angle);
bool			is_touch_wall(float x_ray, float y_ray, t_data *data,
					int block);
float			sqr_two_point(float x, float y);
float			fixed_dist(float x2, float y2,
					t_data *game);
void			draw_view_ray(int i, t_data *data,
					t_raycalculationdata *ray_data);
void			init_ray_position_and_direction(t_raycalculationdata *ray_data,
					t_data *game, float angle);
void			calculate_delta_distances(t_raycalculationdata *ray_data);
void			calculate_initial_side_distances(
					t_raycalculationdata *ray_data);
void			perform_dda_hit_detection(t_raycalculationdata *ray_data,
					t_data *game);
void			calculate_perpendicular_wall_distance(
					t_raycalculationdata *ray_data);
void			calculate_drawing_coordinates(t_raycalculationdata *ray_data,
					t_data *game);
void			ray_line(t_data *game, float angle, int j);
int				ft_performent(t_data *data);
char			*get_right_texture(t_pars *input, char *texture_name);
t_color			*get_right_color(t_pars *input, char *color_name);
void			free_args(char **args);
t_pars			*check_inputs(int ac, char **av, t_pars *input);

#endif
