/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:07:01 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/27 18:25:25 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../inc/cub3d.h"

static t_ErrorCode	check_map_border(t_temp_map_node *node)
{
	int	map_x;

	map_x = 0;
	while (node->line[map_x])
	{
		ft_printf("%c", node->line[map_x]);
		if (ft_strchr("1 ", node->line[map_x]) == NULL)
			return (ERR_INVALID_MAP_CHARACTER);
		map_x++;
	}
	ft_printf("\n");
	return (ERR_OK);
}

t_ErrorCode	check_map(t_game_data *game_data)
{
	t_temp_map_node	*curr_node;
	t_ErrorCode		err;

	curr_node = game_data->tmp_map_lines;
	while (curr_node)
	{
		// ft_printf("line: %d\nmap->height: %d\n", curr_node->map_y,
		// 	game_data->map->height);
		if (curr_node->map_y == 0 || curr_node->map_y == game_data->map->height)
		{
			err = check_map_border(curr_node);
			if (err != ERR_OK)
				return (err);
		}
		else
		{
			err = check_map_line(game_data, curr_node);
			if (err != ERR_OK)
				return (err);
		}
		curr_node = curr_node->next;
	}
	return (ERR_OK);
}
