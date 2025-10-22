/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:20:32 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/22 15:33:05 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

float	fov_to_plane_factor(float fov_deg)
{
	return (tan((fov_deg * PI / 180.0) / 2.0));
}

t_ErrorCode	protected_malloc(t_game_data *game_data)
{
	if (!game_data)
		return (ERR_ALLOC);
	game_data->map = malloc(sizeof(t_map));
	if (game_data->map == NULL)
		return (ERR_ALLOC);
	ft_memset(game_data->map, 0, sizeof(t_map));
	game_data->player = malloc(sizeof(t_player));
	if (game_data->player == NULL)
		return (ERR_ALLOC);
	ft_memset(game_data->player, 0, sizeof(t_player));
	return (ERR_OK);
}
