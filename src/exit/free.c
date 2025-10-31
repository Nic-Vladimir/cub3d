/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:49:10 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 15:55:34 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

void	free_image_tex(t_game_data *game_data)
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

void	free_other_structs(t_game_data *game_data)
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

int	clean_exit(t_game_data *game_data)
{
	free_resources(game_data);
	if (game_data)
		free(game_data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	free_map_data(t_game_data *game_data)
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
