/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_col_diag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:31:18 by vnicoles          #+#    #+#             */
/*   Updated: 2025/11/02 19:31:24 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	diag_cell_col(t_radar *radar, t_game_data *game_data)
{
	diag_cell_col_br(radar, game_data);
	diag_cell_col_bl(radar, game_data);
	diag_cell_col_tr(radar, game_data);
	diag_cell_col_tl(radar, game_data);
}

void	diag_cell_col_br(t_radar *radar, t_game_data *game_data)
{
	char	cell;

	if ((radar->fraction_x > (1.0 - radar->collision_dist)
			&& radar->fraction_y > (1.0 - radar->collision_dist))
		&& (radar->grid_x + 1 < game_data->map->width && radar->grid_y
			+ 1 < game_data->map->height))
	{
		if (game_data->map->grid[radar->grid_y + 1])
		{
			cell = game_data->map->grid[radar->grid_y + 1][radar->grid_x + 1];
			if (cell == '1')
			{
				radar->boundry = true;
			}
		}
	}
}

void	diag_cell_col_bl(t_radar *radar, t_game_data *game_data)
{
	char	cell;

	if ((radar->fraction_x < radar->collision_dist && radar->fraction_y > (1.0
				- radar->collision_dist)) && (radar->grid_x > 0 && radar->grid_y
			+ 1 < game_data->map->height))
	{
		if (game_data->map->grid[radar->grid_y + 1])
		{
			cell = game_data->map->grid[radar->grid_y + 1][radar->grid_x - 1];
			if (cell == '1')
			{
				radar->boundry = true;
			}
		}
	}
}

void	diag_cell_col_tr(t_radar *radar, t_game_data *game_data)
{
	char	cell;

	if ((radar->fraction_x > (1.0 - radar->collision_dist)
			&& radar->fraction_y < radar->collision_dist) && (radar->grid_x
			+ 1 < game_data->map->width && radar->grid_y > 0))
	{
		cell = game_data->map->grid[radar->grid_y - 1][radar->grid_x + 1];
		if (cell == '1')
		{
			radar->boundry = true;
		}
	}
}

void	diag_cell_col_tl(t_radar *radar, t_game_data *game_data)
{
	char	cell;

	if ((radar->fraction_x < radar->collision_dist
			&& radar->fraction_y < radar->collision_dist) && (radar->grid_x > 0
			&& radar->grid_y > 0))
	{
		cell = game_data->map->grid[radar->grid_y - 1][radar->grid_x - 1];
		if (cell == '1')
		{
			radar->boundry = true;
		}
	}
}
