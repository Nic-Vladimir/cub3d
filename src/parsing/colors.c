/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:00:04 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 16:59:23 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

static t_color	init_color(void)
{
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	return (color);
}

void	set_color(t_color *color, char **parts)
{
	if (!color || !parts)
		return ;
	color->r = ft_atoi(parts[0]);
	color->g = ft_atoi(parts[1]);
	color->b = ft_atoi(parts[2]);
}

static t_ErrorCode	assign_color(t_game_data *game_data, t_color color, char c)
{
	int	floor_color[3];
	int	ceiling_color[3];

	if (c == 'F')
	{
		floor_color[0] = color.r;
		floor_color[1] = color.g;
		floor_color[2] = color.b;
		game_data->floor_color = rgb_to_int(floor_color);
	}
	else if (c == 'C')
	{
		ceiling_color[0] = color.r;
		ceiling_color[1] = color.g;
		ceiling_color[2] = color.b;
		game_data->ceiling_color = rgb_to_int(ceiling_color);
	}
	else
		return (ERR_INVALID_COLORS);
	return (ERR_OK);
}

t_ErrorCode	pre_check(char **parts)
{
	if (!parts)
		return (ERR_ALLOC);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3] || !is_number(parts[0])
		|| !is_number(parts[1]) || !is_number(parts[2]))
	{
		ft_free_split(parts);
		return (ERR_INVALID_COLORS);
	}
	return (ERR_OK);
}

t_ErrorCode	parse_color_line(t_game_data *game_data, const char *line,
		int id_index, int data_index)
{
	char	*values;
	char	**parts;
	t_color	color;

	color = init_color();
	values = (char *)(line + data_index);
	parts = ft_split(values, ',');
	if (pre_check(parts) != ERR_OK)
		return (ERR_INVALID_COLORS);
	set_color(&color, parts);
	ft_free_split(parts);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
		return (ERR_INVALID_COLORS);
	if (ft_strncmp(line + id_index, "F ", 2) == 0
		&& game_data->floor_color == UNASSIGNED)
		return (assign_color(game_data, color, 'F'));
	else if (ft_strncmp(line + id_index, "C ", 2) == 0
		&& game_data->ceiling_color == UNASSIGNED)
		return (assign_color(game_data, color, 'C'));
	return (ERR_DUP_COLOR);
}
