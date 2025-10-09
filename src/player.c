/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:01:09 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/09 14:36:28 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
/*
static bool	is_valid_pos(float x, float y, t_game_data *game_data)
{
	// printf("Checking position x: %f (int: %d), y: %f (int: %d)\n", x / 64,
	//	(int)x / 64, y / 64, (int)y / 64);
	// if ((int)y < 0 || (int)y >= game_data->map->height || (int)x < 0
	//	|| (int)x >= game_data->map->width)
	// return (false);
	if (game_data->map->grid[(int)(y / 64)][(int)(x / 64)] == '0')
		return (true);
	return (false);
}

static bool	is_valid_move(float new_x, float new_y, t_game_data *game_data)
{
	bool	move;

	move = false;
	if (is_valid_pos(new_x, game_data->player->y, game_data))
	{
		game_data->player->x = new_x;
		move = true;
	}
	if (is_valid_pos(game_data->player->x, new_y, game_data))
	{
		game_data->player->y = new_y;
		move = true;
	}
	return (move);
}
*/
static bool	valid_move(float x, float y, t_game_data *game_data)
{
	t_player	*player;
	float		radius;

	int grid_x, grid_y;
	player = game_data->player;
	radius = player->size / 2.0;
	// Check center and radius points
	float check_points[5][2] = {
		{x, y},          // Center
		{x + radius, y}, // Right
		{x - radius, y}, // Left
		{x, y + radius}, // Down
		{x, y - radius}  // Up
	};
	for (int i = 0; i < 5; i++)
	{
		grid_x = check_points[i][0] / BLOCK_SIZE;
		grid_y = check_points[i][1] / BLOCK_SIZE;
		// Bounds check
		if (grid_x < 0 || grid_y < 0 || grid_x >= game_data->map->width
			|| grid_y >= game_data->map->height)
			return (false);
		// Wall check
		if (game_data->map->grid[grid_y][grid_x] == '1')
			return (false);
	}
	return (true);
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
	// rotate camera plane (needed for rays)
	tmp_x = player->camera_plane.x;
	player->camera_plane.x = player->camera_plane.x * cosf(rot_speed)
		- player->camera_plane.y * sinf(rot_speed);
	player->camera_plane.y = tmp_x * sinf(rot_speed) + player->camera_plane.y
		* cosf(rot_speed);
}

void	move_player(t_game_data *game_data)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = game_data->player;
	if (player->turn_left)
		rotate_player(game_data, player->turn_speed * -1);
	else if (player->turn_right)
		rotate_player(game_data, player->turn_speed);
	new_x = player->pos.x;
	new_y = player->pos.y;
	// cos_angle = cos(player->angle);
	// sin_angle = sin(player->angle);
	// if (player->turn_left)
	// 	player->angle -= player->turn_speed;
	// if (player->turn_right)
	// {
	// 	player->angle += player->turn_speed;
	// 	printf("Direction angle: %f\n", player->angle);
	// }
	// if (player->angle > 2 * PI)
	// 	player->angle = 0;
	// if (player->angle < 0)
	// 	player->angle = 2 * PI;
	if (player->key_up)
	{
		new_x += player->dir.x * player->move_speed;
		new_y += player->dir.y * player->move_speed;
	}
	if (player->key_down)
	{
		new_x -= player->dir.x * player->move_speed;
		new_y -= player->dir.y * player->move_speed;
	}
	if (player->key_left)
	{
		new_x += player->dir.y * player->move_speed;
		new_y += -player->dir.x * player->move_speed;
	}
	if (player->key_right)
	{
		new_x += -player->dir.y * player->move_speed;
		new_y += player->dir.x * player->move_speed;
	}
	// printf("Checking position x: %f (int: %d), y: %f (int: %d)\n", player->pos.x,
	// 	(int)player->pos.x, player->pos.y, (int)player->pos.y);
	player->pos.x = new_x;
	player->pos.y = new_y;
	if (valid_move(new_x, new_y, game_data))
	{
		player->pos.x = new_x;
		player->pos.y = new_y;
		// printf("Checking position x: %f (int: %d), y: %f (int: %d)\n", player->pos.x,
		// (int)player->pos.x, player->pos.y, (int)player->pos.y);
	}
}
