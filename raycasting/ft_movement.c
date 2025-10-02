/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 07:33:17 by aybouatr          #+#    #+#             */
/*   Updated: 2025/08/04 07:33:20 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	if (keycode == W)
		data->player.up = true;
	 if (keycode == S)
		data->player.down = true;
	 if (keycode == A)
		data->player.left = true;
	 if (keycode == D)
		data->player.right = true;
	 if (keycode == LEFT)
		data->player.turn_left = true;
	 if (keycode == RIGHT)
		data->player.turn_right = true;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player.up = false;
	 if (keycode == S)
		data->player.down = false;
	 if (keycode == A)
		data->player.left = false;
	 if (keycode == D)
		data->player.right = false;
	 if (keycode == LEFT)
		data->player.turn_left = false;
	 if (keycode == RIGHT)
		data->player.turn_right = false;
	return (0);
}

bool	is_correct_move(t_data *game, float sin_angle, float cos_angle)
{
	t_player	*player;

	player = &game->player;
	if (player->up)
		if (is_touch_wall(player->x + cos_angle * SPEED, player->y + sin_angle
				* SPEED, game, BLOCK))
			return (true);
	if (player->down)
		if (is_touch_wall(player->x - cos_angle * SPEED, player->y - sin_angle
				* SPEED, game, BLOCK))
			return (true);
	if (player->left)
		if (is_touch_wall(player->x + sin_angle * SPEED, player->y - cos_angle
				* SPEED, game, BLOCK))
			return (true);
	if (player->right)
		if (is_touch_wall(player->x - sin_angle * SPEED, player->y + cos_angle
				* SPEED, game, BLOCK))
			return (true);
	return (false);
}

void	move_angle(t_player *player)
{
	if (player->turn_left)
		player->angle -= ANGLE_SPEED;
	if (player->turn_right)
		player->angle += ANGLE_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	move_player(t_data *game, float cos_angle, float sin_angle)
{
	move_angle(&game->player);
	if (is_correct_move(game, sin_angle, cos_angle))
		return ;
	if (game->player.up)
	{
		game->player.x += cos_angle * SPEED;
		game->player.y += sin_angle * SPEED;
	}
	if (game->player.down)
	{
		game->player.x -= cos_angle * SPEED;
		game->player.y -= sin_angle * SPEED;
	}
	if (game->player.left)
	{
		game->player.x += sin_angle * SPEED;
		game->player.y -= cos_angle * SPEED;
	}
	if (game->player.right)
	{
		game->player.x -= sin_angle * SPEED;
		game->player.y += cos_angle * SPEED;
	}
}
