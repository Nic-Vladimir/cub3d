/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:23:49 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/16 13:59:45 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"
#include <unistd.h>

static void	set_player_dir_NS(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->camera_plane.x = player->fov_factor;
		player->camera_plane.y = 0;
	}
	else if (dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->camera_plane.x = -player->fov_factor;
		player->camera_plane.y = 0;
	}
	else
		return ;
}

void	set_player_dir_EW(t_player *player, char dir)
{
	if (dir == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->camera_plane.x = 0;
		player->camera_plane.y = player->fov_factor;
	}
	else if (dir == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->camera_plane.x = 0;
		player->camera_plane.y = -player->fov_factor;
	}
	else
		return ;
}

static t_ErrorCode	is_player_position(t_game_data *game_data,
		t_temp_map_node *node, int map_x)
{
	if (ft_strchr("NSEW", node->line[map_x]))
	{
		if (game_data->player->pos_set == true)
			return (ERR_DUP_PLAYER_POS);
		// printf("DEBUG: node->map_y=%d, map_x=%d\n", node->map_y, map_x);
		game_data->player->pos.x = map_x + 0.5;
		game_data->player->pos.y = node->map_y + 0.5;
		// TODO: Add player orientation
		set_player_dir_NS(game_data->player, node->line[map_x]);
		set_player_dir_EW(game_data->player, node->line[map_x]);
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
