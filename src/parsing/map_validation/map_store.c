/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:28:11 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/24 17:37:40 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


t_ErrorCode	store_map(t_game_data *game_data)
{
	t_temp_map_node	*node;
	int				map_y;
	int				i;

	map_y = 0;
	game_data->map->grid = malloc(sizeof(char *) * (game_data->map->height + 2));
	if (!game_data->map->grid)
		return (ERR_ALLOC);
	ft_memset(game_data->map->grid, 0, sizeof(char *) * (game_data->map->height + 2));
	node = game_data->tmp_map_lines;
	while (node)
	{
		game_data->map->grid[map_y] = ft_strdup(node->line);
		if (!game_data->map->grid[map_y])
		{
			i = 0;
			while (i < map_y)
			{
				free(game_data->map->grid[i]);
				i++;
			}
			free(game_data->map->grid);
			game_data->map->grid = NULL;
			return (ERR_ALLOC);
		}
		node = node->next;
		map_y++;
	}
	game_data->map->grid[map_y] = NULL;
	free_temp_map(game_data);
	return (ERR_OK);
}
