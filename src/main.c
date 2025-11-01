/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:48:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/11/01 11:36:25 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>
#include <unistd.h>

static t_ErrorCode	load_texture(t_game_data *game_data, const char *path,
		t_texture *texture)
{
	ft_memset(texture, 0, sizeof(t_texture));
	texture->img = mlx_xpm_file_to_image(game_data->mlx, (char *)path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (ERR_INVALID_PATH);
	fill_texture_pixels(texture);
	return (ERR_OK);
}

t_ErrorCode	load_textures(t_game_data *game_data)
{
	if (!game_data->no_texture_path || !game_data->so_texture_path
		|| !game_data->we_texture_path || !game_data->ea_texture_path)
		return (ERR_INVALID_PATH);
	if (load_texture(game_data, game_data->no_texture_path,
			&game_data->textures[TEX_NORTH]) != ERR_OK)
		return (ERR_INVALID_PATH);
	if (load_texture(game_data, game_data->so_texture_path,
			&game_data->textures[TEX_SOUTH]) != ERR_OK)
		return (ERR_INVALID_PATH);
	if (load_texture(game_data, game_data->we_texture_path,
			&game_data->textures[TEX_WEST]) != ERR_OK)
		return (ERR_INVALID_PATH);
	if (load_texture(game_data, game_data->ea_texture_path,
			&game_data->textures[TEX_EAST]) != ERR_OK)
		return (ERR_INVALID_PATH);
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
