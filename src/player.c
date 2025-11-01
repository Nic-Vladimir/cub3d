/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:01:09 by vnicoles          #+#    #+#             */
/*   Updated: 2025/11/01 20:35:33 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	handle_player_rotation(t_game_data *game_data, float dt)
{
	t_player	*player;

	player = game_data->player;
	if (player->turn_left)
		rotate_player(game_data, player->turn_speed * -1 * dt);
	else if (player->turn_right)
		rotate_player(game_data, player->turn_speed * dt);
}

static void	calculate_new_position(t_player *player, float *new_x, float *new_y,
		float dt)
{
	*new_x = player->pos.x;
	*new_y = player->pos.y;
	if (player->key_up)
	{
		*new_x += player->dir.x * player->move_speed * dt;
		*new_y += player->dir.y * player->move_speed * dt;
	}
	if (player->key_down)
	{
		*new_x -= player->dir.x * player->move_speed * dt;
		*new_y -= player->dir.y * player->move_speed * dt;
	}
	if (player->key_left)
	{
		*new_x += player->dir.y * player->move_speed * dt;
		*new_y += -player->dir.x * player->move_speed * dt;
	}
	if (player->key_right)
	{
		*new_x += -player->dir.y * player->move_speed * dt;
		*new_y += player->dir.x * player->move_speed * dt;
	}
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

void	move_player(t_game_data *game_data, float dt)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = game_data->player;
	handle_player_rotation(game_data, dt);
	calculate_new_position(player, &new_x, &new_y, dt);
	if (player->pos.x != new_x || player->pos.y != new_y)
		radar_player(game_data, new_x, new_y);
	handle_position_update(game_data, new_x, new_y);
}
