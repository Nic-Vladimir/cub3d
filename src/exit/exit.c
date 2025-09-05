/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:19:01 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/05 16:49:14 by vnicoles         ###   ########.fr       */
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
	if (err >= ERR_OK && err < ERR_COUNT)
		return (errors[err]);
	return ("Unknown error\n");
}

static void	free_resources(t_game_data *game_data)
{
	if (!game_data)
		return ;
	if (game_data->mlx && game_data->img)
		mlx_destroy_image(game_data->mlx, game_data->img);
	if (game_data->mlx && game_data->win)
		mlx_destroy_window(game_data->mlx, game_data->win);
	if (game_data->mlx)
		mlx_destroy_display(game_data->mlx);
	if (game_data->map.grid)
		free(game_data->map.grid);
	if (game_data->mlx)
		free(game_data->mlx);
	game_data->img = NULL;
	game_data->win = NULL;
	game_data->mlx = NULL;
	game_data->map.grid = NULL;
}

void	clean_exit(t_game_data *game_data)
{
	free_resources(game_data);
	exit(EXIT_SUCCESS);
}

void	error_exit(t_game_data *game_data, t_ErrorCode err)
{
	ft_printf("[cub3d] " RED "Fatal error: %s" RESET "\n", get_err_msg(err));
	(void)game_data;
	free_resources(game_data);
	exit(err);
}
