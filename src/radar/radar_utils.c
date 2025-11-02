/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:29:05 by mgavornik         #+#    #+#             */
/*   Updated: 2025/11/02 01:37:13 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

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
