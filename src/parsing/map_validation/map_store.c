/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:28:11 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/09 16:13:17 by vnicoles         ###   ########.fr       */
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

	map_y = 0;
	game_data->map->grid = malloc(sizeof(char *) * game_data->map->height);
	if (!game_data->map->grid)
		return (ERR_ALLOC);
	node = game_data->tmp_map_lines;
	while (node)
	{
		game_data->map->grid[map_y] = ft_strdup(node->line);
		if (!game_data->map->grid[map_y])
			return (ERR_ALLOC);
		node = node->next;
		map_y++;
	}
	free_temp_map(game_data);
	return (ERR_OK);
}
