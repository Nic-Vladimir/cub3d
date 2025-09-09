/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:00:04 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/09 16:00:37 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_ErrorCode	assign_color(t_game_data *game_data, int r, int g, int b,
		char c)
{
	if (c == 'F')
	{
		game_data->floor_color[0] = r;
		game_data->floor_color[1] = g;
		game_data->floor_color[2] = b;
		game_data->floor_color_assigned = true;
	}
	else if (c == 'C')
	{
		game_data->floor_color[0] = r;
		game_data->floor_color[1] = g;
		game_data->floor_color[2] = b;
		game_data->ceiling_color_assigned = true;
	}
	else
		return (ERR_INVALID_COLORS);
	return (ERR_OK);
}

t_ErrorCode	parse_color_line(t_game_data *game_data, const char *line,
		int id_index, int data_index)
{
	char	*values;
	char	**parts;

	int r, g, b;
	values = (char *)(line + data_index);
	parts = ft_split(values, ',');
	if (!parts)
		return (ERR_ALLOC);
	// ft_printf("parts[0]=%s, parts[1]=%s, parts[2]=%s, parts[3]=%s\n",
	// parts[0],
	// parts[1], parts[2], parts[3]);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3] || !is_number(parts[0])
		|| !is_number(parts[1]) || !is_number(parts[2]))
		return (ERR_INVALID_COLORS);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	ft_free_split(parts);
	// ft_printf("r = %d, g = %d, b = %d\n", r, g, b);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ERR_INVALID_COLORS);
	if (ft_strncmp(line + id_index, "F ", 2) == 0
		&& game_data->floor_color_assigned == false)
		return (assign_color(game_data, r, g, b, 'F'));
	else if (ft_strncmp(line + id_index, "C ", 2) == 0
		&& game_data->ceiling_color_assigned == false)
		return (assign_color(game_data, r, g, b, 'C'));
	return (ERR_DUP_COLOR);
}
