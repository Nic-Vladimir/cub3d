/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:24:57 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 21:04:37 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	game_data->radar = malloc(sizeof(t_radar));
	if (game_data->radar == NULL)
		return (ERR_ALLOC);
	ft_memset(game_data->radar, 0, sizeof(t_radar));
	if (game_data->ray == NULL)
		return (ERR_ALLOC);
	ft_memset(game_data->ray, 0, sizeof(t_ray));
	return (ERR_OK);
}

t_ErrorCode	init_game_data(t_game_data *game_data)
{
	if (!game_data)
		return (ERR_ALLOC);
	protected_malloc(game_data);
	game_data->values = init_values(game_data->values);
	init_radar_data(game_data);
	init_tex_data(game_data);
	init_zero_data(game_data);
	init_null_data(game_data);
	init_unasigned_data(game_data);
	game_data->player->pos_set = false;
	game_data->in_map = false;
	game_data->player->fov_factor = fov_to_plane_factor(FOV);
	init_player(game_data->player);
	return (ERR_OK);
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
	mlx_hook(game_data->win, 17, 0, clean_exit, NULL);
	return (ERR_OK);
}
