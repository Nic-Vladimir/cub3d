/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:28:11 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 16:16:29 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../inc/cub3d.h"

static void	free_temp_map(t_game_data *game_data)
{
	t_temp_map_node	*curr;
	t_temp_map_node	*tmp;

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

static t_ErrorCode	allocate_map_grid(t_game_data *game_data)
{
	game_data->map->grid = malloc(sizeof(char *) * (game_data->map->height
				+ 2));
	if (!game_data->map->grid)
		return (ERR_ALLOC);
	ft_memset(game_data->map->grid, 0, sizeof(char *) * (game_data->map->height
			+ 2));
	return (ERR_OK);
}

static void	cleanup_map_grid(t_game_data *game_data, int allocated_rows)
{
	int	i;

	i = 0;
	while (i < allocated_rows)
	{
		free(game_data->map->grid[i]);
		i++;
	}
	free(game_data->map->grid);
	game_data->map->grid = NULL;
}

t_ErrorCode	store_map(t_game_data *game_data)
{
	t_temp_map_node	*node;
	t_ErrorCode		err;
	int				map_y;

	err = allocate_map_grid(game_data);
	if (err != ERR_OK)
		return (err);
	map_y = 0;
	node = game_data->tmp_map_lines;
	while (node)
	{
		game_data->map->grid[map_y] = ft_strdup(node->line);
		if (!game_data->map->grid[map_y])
		{
			cleanup_map_grid(game_data, map_y);
			return (ERR_ALLOC);
		}
		node = node->next;
		map_y++;
	}
	game_data->map->grid[map_y] = NULL;
	free_temp_map(game_data);
	return (ERR_OK);
}
