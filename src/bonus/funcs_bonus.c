/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:14:42 by vnicoles          #+#    #+#             */
/*   Updated: 2025/11/02 01:01:54 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

void	draw_minimap_if_needed(t_game_data *game_data)
{
	draw_map(game_data);
	draw_vision_cone(game_data);
	draw_circle(game_data->player->pos.x, game_data->player->pos.y, player_mod,
		game_data);
}

bool	valid_move(float x, float y, t_game_data *game_data)
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
