/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_col_proc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:23:40 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 18:38:19 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"

static bool	check_grid_bounds(t_radar *radar, t_game_data *game_data)
{
	if (radar->grid_x >= 0 && radar->grid_x < game_data->map->width
		&& radar->grid_y >= 0 && radar->grid_y <= (game_data->map->height + 1))
		return (true);
	return (false);
}

static void	check_axis_blocking(t_radar *radar, t_game_data *game_data,
		bool *x_blocked, bool *y_blocked)
{
	radar->boundry = false;
	right_cell_col(radar, game_data);
	if (radar->boundry)
		*x_blocked = true;
	radar->boundry = false;
	left_cell_col(radar, game_data);
	if (radar->boundry)
		*x_blocked = true;
	radar->boundry = false;
	top_cell_col(radar, game_data);
	if (radar->boundry)
		*y_blocked = true;
	radar->boundry = false;
	bottom_cell_col(radar, game_data);
	if (radar->boundry)
		*y_blocked = true;
}

static bool	process_collision_detection(t_radar *radar, t_game_data *game_data)
{
	char	cell;
	bool	x_blocked;
	bool	y_blocked;

	if (!game_data->map->grid[radar->grid_y])
		return (false);
	radar->fraction_x = radar->point_x - (float)radar->grid_x;
	radar->fraction_y = radar->point_y - (float)radar->grid_y;
	radar->boundry = false;
	cell = game_data->map->grid[radar->grid_y][radar->grid_x];
	if (cell == '1')
		radar->boundry = true;
	collision_wrapper(radar, game_data);
	if (radar->boundry || cell == '1')
	{
		x_blocked = false;
		y_blocked = false;
		check_axis_blocking(radar, game_data, &x_blocked, &y_blocked);
		return (false);
	}
	return (true);
}

bool	process_radar_point(t_radar *radar, t_game_data *game_data,
		bool player_move)
{
	if (!player_move)
		return (true);
	radar->grid_x = (int)radar->point_x;
	radar->grid_y = (int)radar->point_y;
	if (!validate_radar_data(game_data))
		return (false);
	if (!check_grid_bounds(radar, game_data))
		return (true);
	return (process_collision_detection(radar, game_data));
}

void	radar_loop(t_game_data *game_data)
{
	static float	last_x = 0;
	static float	last_y = 0;
	t_player		*player;
	t_radar			*radar;

	player = game_data->player;
	radar = game_data->radar;
	if (!validate_radar_data(game_data))
		return ;
	player->move = (last_x != player->pos.x || last_y != player->pos.y);
	if (radar->angle >= 360.0f)
		radar->angle = 0.0f;
	while (radar->angle < 360.0f)
	{
		calc_radar_point(radar, game_data);
		draw_circle(radar->point_x, radar->point_y, radar_mod, game_data);
		process_radar_point(radar, game_data, player->move);
		radar->angle += radar->angle_step;
	}
	last_x = player->pos.x;
	last_y = player->pos.y;
}
