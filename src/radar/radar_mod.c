/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:41:24 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 19:43:11 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"

void	dda_mod(float *radius, int *color, t_game_data *game_data)
{
	(void)game_data;
	*radius = 0.1f;
	*color = 0x00FF00;
}

void	radar_mod(float *radius, int *color, t_game_data *game_data)
{
	*radius = game_data->radar->dot_size;
	*color = game_data->radar->color;
}

void	player_mod(float *radius, int *color, t_game_data *game_data)
{
	(void)game_data;
	*radius = 0.25f;
	*color = 0xFF0000;
}
