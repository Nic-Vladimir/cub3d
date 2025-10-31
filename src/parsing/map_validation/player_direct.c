/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:06:20 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 21:03:11 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	set_player_dir_ns(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->camera_plane.x = player->fov_factor;
		player->camera_plane.y = 0;
	}
	else if (dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->camera_plane.x = -player->fov_factor;
		player->camera_plane.y = 0;
	}
	else
		return ;
}

void	set_player_dir_ew(t_player *player, char dir)
{
	if (dir == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->camera_plane.x = 0;
		player->camera_plane.y = player->fov_factor;
	}
	else if (dir == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->camera_plane.x = 0;
		player->camera_plane.y = -player->fov_factor;
	}
	else
		return ;
}
