/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:19:01 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/22 10:58:37 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <stdlib.h>

static const char	*get_err_msg(t_ErrorCode err)
{
	char	*errors[ERR_COUNT];

	errors[ERR_OK] = "";
	errors[ERR_USAGE] = "Usage: ./cub3d <path/to/map.cub>\n";
	errors[ERR_INVALID_FILENAME] = "Invalid file. The filename must have a '.cub' extension\n";
	errors[ERR_INVALID_PATH] = "Invalid path. No '.cub' file at given path\n";
	errors[ERR_INVALID_ORDER] = "Invalid order. Map must come last in '.cub' file\n";
	errors[ERR_DUP_TEXTURE] = "Duplicate texture assignment in '.cub' file\n";
	errors[ERR_UNKNOWN_TEXTURE_ID] = "Unknown texture id in '.cub' file\n";
	errors[ERR_INVALID_COLORS] = "Invalid colors in '.cub' file. Colors must be in range 0-255 and formatted as 'r,g,b'\n";
	errors[ERR_DUP_COLOR] = "Duplicate color assignment in '.cub' file\n";
	errors[ERR_ALLOC] = "Memory allocation failure\n";
	errors[ERR_INVALID_MAP_CHARACTER] = "Invalid character in map\n";
	errors[ERR_INVALID_MAP_FORMAT] = "Invalid map format\n";
	errors[ERR_DUP_PLAYER_POS] = "Duplicate player position in map\n";
	if (err >= ERR_OK && err < ERR_COUNT)
		return (errors[err]);
	return ("Unknown error\n");
}
static void	free_image_tex(t_game_data *game_data)
{
	if (game_data->mlx)
	{
		if (game_data->textures[TEX_NORTH].img)
			mlx_destroy_image(game_data->mlx,
				game_data->textures[TEX_NORTH].img);
		if (game_data->textures[TEX_SOUTH].img)
			mlx_destroy_image(game_data->mlx,
				game_data->textures[TEX_SOUTH].img);
		if (game_data->textures[TEX_WEST].img)
			mlx_destroy_image(game_data->mlx,
				game_data->textures[TEX_WEST].img);
		if (game_data->textures[TEX_EAST].img)
			mlx_destroy_image(game_data->mlx,
				game_data->textures[TEX_EAST].img);
	}
}

static void	free_mlx_data(t_game_data *game_data)
{
	if (game_data->mlx && game_data->img)
		mlx_destroy_image(game_data->mlx, game_data->img);
	if (game_data->mlx && game_data->win)
		mlx_destroy_window(game_data->mlx, game_data->win);
	if (game_data->mlx)
		mlx_destroy_display(game_data->mlx);
}
static void	free_map_data(t_game_data *game_data)
{
	int				i;
	t_temp_map_node	*curr;
	t_temp_map_node	*tmp;

	if (game_data->map && game_data->map->grid)
	{
		i = 0;
		while (game_data->map->grid[i])
		{
			free(game_data->map->grid[i]);
			i++;
		}
		free(game_data->map->grid);
		game_data->map->grid = NULL;
	}
	curr = game_data->tmp_map_lines;
	while (curr)
	{
		tmp = curr->next;
		free(curr->line);
		free(curr);
		curr = tmp;
	}
	game_data->tmp_map_lines = NULL;
}

static void	free_tex_compas(t_game_data *game_data)
{
	if (game_data->no_texture_path)
	{
		free(game_data->no_texture_path);
		game_data->no_texture_path = NULL;
	}
	if (game_data->so_texture_path)
	{
		free(game_data->so_texture_path);
		game_data->so_texture_path = NULL;
	}
	if (game_data->we_texture_path)
	{
		free(game_data->we_texture_path);
		game_data->we_texture_path = NULL;
	}
	if (game_data->ea_texture_path)
	{
		free(game_data->ea_texture_path);
		game_data->ea_texture_path = NULL;
	}
}

static void	free_other_structs(t_game_data *game_data)
{
	if (game_data->map)
	{
		free(game_data->map);
		game_data->map = NULL;
	}
	if (game_data->player)
	{
		free(game_data->player);
		game_data->player = NULL;
	}
	if (game_data->values)
	{
		free(game_data->values);
		game_data->values = NULL;
	}
	if (game_data->radar)
	{
		free(game_data->radar);
		game_data->radar = NULL;
	}
}

static void	free_resources(t_game_data *game_data)
{
	if (!game_data)
		return ;
	free_image_tex(game_data);
	free_mlx_data(game_data);
	free_map_data(game_data);
	free_other_structs(game_data);
	free_tex_compas(game_data);
	if (game_data->mlx)
		free(game_data->mlx);
	game_data->img = NULL;
	game_data->win = NULL;
	game_data->mlx = NULL;
}

int	clean_exit(t_game_data *game_data)
{
	free_resources(game_data);
	if (game_data)
		free(game_data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	error_exit(t_game_data *game_data, t_ErrorCode err)
{
	ft_printf("[cub3d] " RED "Fatal error: %s" RESET "\n", get_err_msg(err));
	free_resources(game_data);
	if (game_data)
		free(game_data);
	exit(err);
}
