/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_col_side.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:19:04 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 18:34:18 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"

void	right_cell_col(t_radar *radar, t_game_data *game_data)
{
	char	cell;

	if (radar->fraction_x > (1.0 - radar->collision_dist) && radar->grid_x
		+ 1 <= game_data->map->width)
	{
		cell = game_data->map->grid[radar->grid_y][radar->grid_x + 1];
		if (cell == '1')
		{
			radar->boundry = true;
		}
	}
}

void	left_cell_col(t_radar *radar, t_game_data *game_data)
{
	char	cell;

	if (radar->fraction_x < radar->collision_dist && radar->grid_x > 0)
	{
		cell = game_data->map->grid[radar->grid_y][radar->grid_x - 1];
		if (cell == '1')
		{
			radar->boundry = true;
		}
	}
}

void	bottom_cell_col(t_radar *radar, t_game_data *game_data)
{
	char	cell;

	if (radar->fraction_y > (1.0 - radar->collision_dist) && radar->grid_y
		+ 1 <= (game_data->map->height + 1))
	{
		if (game_data->map->grid[radar->grid_y + 1])
		{
			cell = game_data->map->grid[radar->grid_y + 1][radar->grid_x];
			if (cell == '1')
			{
				radar->boundry = true;
			}
		}
	}
}

void	top_cell_col(t_radar *radar, t_game_data *game_data)
{
	char	cell;

	if (radar->fraction_y < radar->collision_dist && radar->grid_y > 0)
	{
		cell = game_data->map->grid[radar->grid_y - 1][radar->grid_x];
		if (cell == '1')
		{
			radar->boundry = true;
		}
	}
}
