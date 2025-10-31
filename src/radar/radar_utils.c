/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:29:05 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 21:03:56 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	convrad(float ang)
{
	return (ang * PI / 180.0f);
}

void	collision_wrapper(t_radar *radar, t_game_data *game_data)
{
	right_cell_col(radar, game_data);
	left_cell_col(radar, game_data);
	bottom_cell_col(radar, game_data);
	top_cell_col(radar, game_data);
	diag_cell_col(radar, game_data);
}

void	calc_radar_point(t_radar *radar, t_game_data *game_data)
{
	radar->theta = convrad(radar->angle);
	radar->point_x = game_data->player->pos.x + radar->radius
		* cos(radar->theta);
	radar->point_y = game_data->player->pos.y + radar->radius
		* sin(radar->theta);
	radar->x = radar->point_x;
	radar->y = radar->point_y;
}

bool	validate_radar_data(t_game_data *game_data)
{
	if (!game_data || !game_data->radar || !game_data->player)
		return (false);
	if (!game_data->map || !game_data->map->grid || game_data->map->height < 0)
		return (false);
	return (true);
}
