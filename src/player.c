/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:01:09 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 21:21:54 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	handle_player_rotation(t_game_data *game_data)
{
	t_player	*player;

	player = game_data->player;
	if (player->turn_left)
		rotate_player(game_data, player->turn_speed * -1);
	else if (player->turn_right)
		rotate_player(game_data, player->turn_speed);
}

static void	calculate_new_position(t_player *player, float *new_x, float *new_y)
{
	*new_x = player->pos.x;
	*new_y = player->pos.y;
	if (player->key_up)
	{
		*new_x += player->dir.x * player->move_speed;
		*new_y += player->dir.y * player->move_speed;
	}
	if (player->key_down)
	{
		*new_x -= player->dir.x * player->move_speed;
		*new_y -= player->dir.y * player->move_speed;
	}
	if (player->key_left)
	{
		*new_x += player->dir.y * player->move_speed;
		*new_y += -player->dir.x * player->move_speed;
	}
	if (player->key_right)
	{
		*new_x += -player->dir.y * player->move_speed;
		*new_y += player->dir.x * player->move_speed;
	}
}

static bool	valid_move(float x, float y, t_game_data *game_data)
{
	t_radar	*radar;

	radar = game_data->radar;
	radar->point_x = x;
	radar->point_y = y;
	radar->grid_x = (int)x;
	radar->grid_y = (int)y;
	radar->fraction_x = x - (float)radar->grid_x;
	radar->fraction_y = y - (float)radar->grid_y;
	radar->boundry = false;
	if (radar->grid_x < 0 || radar->grid_y < 0
		|| radar->grid_x >= game_data->map->width
		|| radar->grid_y >= game_data->map->height)
		return (false);
	if (game_data->map->grid[radar->grid_y][radar->grid_x] == '1')
		return (false);
	collision_wrapper(radar, game_data);
	if (radar->boundry)
		return (false);
	return (true);
}

static void	handle_position_update(t_game_data *game_data, float new_x,
		float new_y)
{
	t_player	*player;

	player = game_data->player;
	if (valid_move(new_x, new_y, game_data))
	{
		radar_loop(game_data);
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

void	move_player(t_game_data *game_data)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = game_data->player;
	handle_player_rotation(game_data);
	calculate_new_position(player, &new_x, &new_y);
	if (player->pos.x != new_x || player->pos.y != new_y)
		radar_player(game_data, new_x, new_y);
	handle_position_update(game_data, new_x, new_y);
}
