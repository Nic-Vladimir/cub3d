/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:01:09 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/22 15:33:46 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	valid_move(float x, float y, t_game_data *game_data)
{
	int		grid_x;
	int		grid_y;
	int		i;
	float	check_points[5][2];

	check_points[0][0] = x;
	check_points[0][1] = y;
	check_points[1][0] = x + game_data->player->size;
	check_points[1][1] = y;
	check_points[2][0] = x - game_data->player->size;
	check_points[2][1] = y;
	check_points[3][0] = x;
	check_points[3][1] = y + game_data->player->size;
	check_points[4][0] = x;
	check_points[4][1] = y - game_data->player->size;
	i = 0;
	while (i < 5)
	{
		grid_x = (int)check_points[i][0];
		grid_y = (int)check_points[i][1];
		if (grid_x < 0 || grid_y < 0 || grid_x >= game_data->map->width
			|| grid_y >= game_data->map->height)
			return (false);
		if (game_data->map->grid[grid_y][grid_x] == '1')
			return (false);
		i++;
	}
	return (true);
}

static void	rotate_player(t_game_data *game_data, float rot_speed)
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
	if (valid_move(new_x, new_y, game_data))
	{
		player->pos.x = new_x;
		player->pos.y = new_y;
	}
	else
	{
		if (valid_move(new_x, player->pos.y, game_data))
			player->pos.x = new_x;
		if (valid_move(player->pos.x, new_y, game_data))
			player->pos.y = new_y;
	}
}
