/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_radar_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:32:27 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 21:02:54 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_radar_zero(t_radar *radar)
{
	if (!radar)
		return ;
	ft_memset(radar, 0, sizeof(t_radar));
}

void	init_radar_data(t_game_data *game_data)
{
	if (!game_data)
		return ;
	init_radar_zero(game_data->radar);
	game_data->radar->color = 0xFF0000;
	game_data->radar->angle_step = 15;
	game_data->radar->radius = 0.15;
	game_data->radar->dot_size = 0.02;
	game_data->radar->collision_dist = 0.2;
}

t_circle	*init_circle(void)
{
	t_circle	*circle;

	circle = malloc(sizeof(t_circle));
	if (!circle)
		return (NULL);
	ft_memset(circle, 0, sizeof(t_circle));
	return (circle);
}
