/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:21:00 by mgavorni          #+#    #+#             */
/*   Updated: 2025/10/31 21:21:40 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->turn_left = false;
	player->turn_right = false;
	player->move_speed = MOVE_SPEED;
	player->turn_speed = TURN_SPEED;
	player->size = PLAYER_SIZE;
}

int	key_press_handler(int keycode, t_game_data *game_data)
{
	t_player	*player;

	player = game_data->player;
	if (keycode == XK_Escape)
	{
		printf("The %d key (ESC) was pressed\n\n", keycode);
		clean_exit(game_data);
	}
	else if (keycode == W)
		player->key_up = true;
	else if (keycode == S)
		player->key_down = true;
	else if (keycode == A)
		player->key_left = true;
	else if (keycode == D)
		player->key_right = true;
	else if (keycode == TURN_LEFT)
		player->turn_left = true;
	else if (keycode == TURN_RIGHT)
		player->turn_right = true;
	return (0);
}

int	key_release_handler(int keycode, t_game_data *game_data)
{
	t_player	*player;

	player = game_data->player;
	if (keycode == W)
		player->key_up = false;
	else if (keycode == S)
		player->key_down = false;
	else if (keycode == A)
		player->key_left = false;
	else if (keycode == D)
		player->key_right = false;
	else if (keycode == TURN_LEFT)
		player->turn_left = false;
	else if (keycode == TURN_RIGHT)
		player->turn_right = false;
	return (0);
}

void	rotate_player(t_game_data *game_data, float rot_speed)
{
	t_player	*player;
	float		tmp_x;

	player = game_data->player;
	tmp_x = player->dir.x;
	player->dir.x = player->dir.x * cosf(rot_speed) - player->dir.y
		* sinf(rot_speed);
	player->dir.y = tmp_x * sinf(rot_speed) + player->dir.y * cosf(rot_speed);
	tmp_x = player->camera_plane.x;
	player->camera_plane.x = player->camera_plane.x * cosf(rot_speed)
		- player->camera_plane.y * sinf(rot_speed);
	player->camera_plane.y = tmp_x * sinf(rot_speed) + player->camera_plane.y
		* cosf(rot_speed);
}

void	radar_player(t_game_data *game_data, float new_x, float new_y)
{
	t_player	*player;
	t_radar		*radar;
	double		theta;

	player = game_data->player;
	radar = game_data->radar;
	while (radar->angle < 360)
	{
		theta = convrad(radar->angle);
		radar->x = (player->pos.x + radar->radius * cos(theta));
		radar->y = (player->pos.y + radar->radius * sin(theta));
		radar->angle += radar->angle_step;
	}
	if (player->pos.x == new_x || player->pos.y == new_y)
		radar->angle = 0;
}
