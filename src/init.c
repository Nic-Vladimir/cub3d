/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:28:46 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/22 15:37:37 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->turn_left = false;
	player->turn_right = false;
	player->move_speed = MOVE_SPEED;
	player->turn_speed = TURN_SPEED;
	player->size = PLAYER_SIZE;
}

t_ErrorCode	init_mlx(t_game_data *game_data)
{
	game_data->mlx = mlx_init();
	game_data->win = mlx_new_window(game_data->mlx, WIDTH, HEIGHT, "Cub3D");
	game_data->img = mlx_new_image(game_data->mlx, WIDTH, HEIGHT);
	game_data->addr = mlx_get_data_addr(game_data->img, &game_data->bpp,
			&game_data->line_len, &game_data->endian);
	mlx_hook(game_data->win, KeyPress, KeyPressMask, key_press_handler,
		game_data);
	mlx_hook(game_data->win, KeyRelease, KeyReleaseMask, key_release_handler,
		game_data);
	return (ERR_OK);
}
