/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:48:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 19:55:45 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"
#include "../inc/utils.h"
#include <stdlib.h>
#include <unistd.h>



t_ErrorCode	load_textures(t_game_data *game_data)
{
	t_texture	no_texture;
	t_texture	so_texture;
	t_texture	we_texture;
	t_texture	ea_texture;

	// Validate texture paths
	if (!game_data->no_texture_path || !game_data->so_texture_path
		|| !game_data->we_texture_path || !game_data->ea_texture_path)
		return (ERR_INVALID_PATH);
	// Initialize texture data
	ft_memset(&no_texture, 0, sizeof(t_texture));
	ft_memset(&so_texture, 0, sizeof(t_texture));
	ft_memset(&we_texture, 0, sizeof(t_texture));
	ft_memset(&ea_texture, 0, sizeof(t_texture));
	no_texture.img = mlx_xpm_file_to_image(game_data->mlx,
			game_data->no_texture_path, &no_texture.width, &no_texture.height);
	if (!no_texture.img)
		return (ERR_INVALID_PATH);
	fill_texture_pixels(&no_texture);
	game_data->textures[TEX_NORTH] = no_texture;
	so_texture.img = mlx_xpm_file_to_image(game_data->mlx,
			game_data->so_texture_path, &so_texture.width, &so_texture.height);
	if (!so_texture.img)
		return (ERR_INVALID_PATH);
	fill_texture_pixels(&so_texture);
	game_data->textures[TEX_SOUTH] = so_texture;
	we_texture.img = mlx_xpm_file_to_image(game_data->mlx,
			game_data->we_texture_path, &we_texture.width, &we_texture.height);
	if (!we_texture.img)
		return (ERR_INVALID_PATH);
	fill_texture_pixels(&we_texture);
	game_data->textures[TEX_WEST] = we_texture;
	ea_texture.img = mlx_xpm_file_to_image(game_data->mlx,
			game_data->ea_texture_path, &ea_texture.width, &ea_texture.height);
	if (!ea_texture.img)
		return (ERR_INVALID_PATH);
	fill_texture_pixels(&ea_texture);
	game_data->textures[TEX_EAST] = ea_texture;
	return (ERR_OK);
}

static t_ErrorCode	parse_cub_file(t_game_data *game_data, int argc,
		char **argv)
{
	t_ErrorCode	err;

	(void)game_data;
	err = check_args(argc, argv);
	if (err != ERR_OK)
		return (err);
	err = parse_cub_data(game_data, argv);
	if (err != ERR_OK)
		return (err);
	err = check_map(game_data);
	if (err != ERR_OK)
		return (err);
	err = store_map(game_data);
	if (err != ERR_OK)
		return (err);
	return (ERR_OK);
}

int	main(int argc, char **argv)
{
	t_game_data	*game_data;
	t_ErrorCode	err;

	game_data = malloc(sizeof(t_game_data));
	ft_memset(game_data, 0, sizeof(t_game_data));
	if (!game_data)
		error_exit(game_data, ERR_ALLOC);
	err = init_game_data(game_data);
	if (err != ERR_OK)
		error_exit(game_data, err);
	err = parse_cub_file(game_data, argc, argv);
	if (err != ERR_OK)
		error_exit(game_data, err);
	err = init_mlx(game_data);
	if (err != ERR_OK)
		error_exit(game_data, err);
	err = load_textures(game_data);
	if (err != ERR_OK)
		return (err);
	mlx_loop_hook(game_data->mlx, draw_loop, game_data);
	mlx_loop(game_data->mlx);
	return (0);
}
