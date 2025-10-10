/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:57:18 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/10 12:36:10 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

static void	assign_new_node(t_game_data *game_data, t_temp_map_node *new_node)
{
	t_temp_map_node	*prev_node;

	prev_node = game_data->tmp_map_lines;
	while (prev_node->next)
		prev_node = prev_node->next;
	prev_node->next = new_node;
	new_node->prev = prev_node;
}

static t_ErrorCode	store_tmp_line(t_game_data *game_data, const char *line)
{
	t_temp_map_node	*new_node;

	new_node = malloc(sizeof(t_temp_map_node));
	if (!new_node)
		return (ERR_ALLOC);
	ft_memset(new_node, 0, sizeof(t_temp_map_node));
	new_node->line = ft_strdup(line);
	if (!new_node->line)
		return (ERR_ALLOC);
	new_node->next = NULL;
	new_node->prev = NULL;
	game_data->map->height++;
	new_node->map_y = game_data->map->height;
	if (!game_data->tmp_map_lines)
		game_data->tmp_map_lines = new_node;
	else
		assign_new_node(game_data, new_node);
	return (ERR_OK);
}

t_ErrorCode	parse_map_line(t_game_data *game_data, char *line, int i)
{
	t_ErrorCode	err;

	(void)i;
	if (game_data->in_map == false)
		game_data->in_map = true;
	line = ft_strrtrim(line, "\t\n ");
	err = store_tmp_line(game_data, line);
	free(line);
	line = NULL;
	if (err != ERR_OK)
		return (err);
	return (ERR_OK);
}
