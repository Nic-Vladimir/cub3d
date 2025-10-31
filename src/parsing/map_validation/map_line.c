/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:23:49 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 21:02:59 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"
#include <unistd.h>

static t_ErrorCode	is_player_position(t_game_data *game_data,
		t_temp_map_node *node, int map_x)
{
	if (ft_strchr("NSEW", node->line[map_x]))
	{
		if (game_data->player->pos_set == true)
			return (ERR_DUP_PLAYER_POS);
		game_data->player->pos.x = map_x + 0.5;
		game_data->player->pos.y = node->map_y + 0.5;
		set_player_dir_ns(game_data->player, node->line[map_x]);
		set_player_dir_ew(game_data->player, node->line[map_x]);
		game_data->player->pos_set = true;
	}
	return (ERR_OK);
}

static t_ErrorCode	check_map_line_char(t_temp_map_node *node, int map_x)
{
	t_temp_map_node	*prev_node;
	t_temp_map_node	*next_node;

	prev_node = node->prev;
	next_node = node->next;
	if (ft_strchr("01NSEW ", node->line[map_x]) == NULL)
		return (ERR_INVALID_MAP_CHARACTER);
	if (node->line[map_x] == '0' && (node->line[map_x + 1] == ' '
			|| node->line[map_x + 1] == '\n' || map_x == 0 || node->line[map_x
				- 1] == ' '))
		return (ERR_INVALID_MAP_FORMAT);
	if (ft_strlen(node->line) > ft_strlen(prev_node->line)
		&& map_x > (int)ft_strlen(prev_node->line) - 1 && (ft_strchr("1 ",
				node->line[map_x]) == NULL))
		return (ERR_INVALID_MAP_FORMAT);
	if (ft_strlen(node->line) > ft_strlen(next_node->line)
		&& map_x > (int)ft_strlen(next_node->line) - 1 && (ft_strchr("1 ",
				node->line[map_x]) == NULL))
	{
		ft_printf("Failed here");
		return (ERR_INVALID_MAP_FORMAT);
	}
	return (ERR_OK);
}

static t_ErrorCode	check_first_and_last_char(t_temp_map_node *node)
{
	int	i;

	i = 0;
	while (ft_is_whitespace(node->line[i]))
		i++;
	if (node->line[i] != '1')
		return (ERR_INVALID_MAP_FORMAT);
	i = ft_strlen(node->line) - 1;
	while (ft_is_whitespace(node->line[i]))
		i--;
	if (node->line[i] != '1')
		return (ERR_INVALID_MAP_FORMAT);
	return (ERR_OK);
}

t_ErrorCode	check_map_line(t_game_data *game_data, t_temp_map_node *node)
{
	t_ErrorCode	err;
	int			map_x;

	err = check_first_and_last_char(node);
	if (err != ERR_OK)
		return (err);
	map_x = 0;
	while (node->line[map_x])
	{
		ft_printf("%c", node->line[map_x]);
		err = check_map_line_char(node, map_x);
		if (err != ERR_OK)
			return (err);
		err = is_player_position(game_data, node, map_x);
		if (err != ERR_OK)
			return (err);
		map_x++;
	}
	if ((int)ft_strlen(node->line) > game_data->map->width)
		game_data->map->width = ft_strlen(node->line);
	ft_printf("\n");
	return (ERR_OK);
}
