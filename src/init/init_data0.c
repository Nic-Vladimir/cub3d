/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:26:30 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 21:02:50 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_line(t_line *line)
{
	if (line == NULL)
		return ;
	line->cos_angle = 0;
	line->sin_angle = 0;
	line->ray_x = 0;
	line->ray_y = 0;
	line->dist = 0;
	line->height = 0;
	line->start_y = 0;
	line->end = 0;
}

void	init_tex_data(t_game_data *game_data)
{
	int	i;

	i = 0;
	if (!game_data)
		return ;
	while (i < 4)
	{
		game_data->textures[i].img = NULL;
		game_data->textures[i].pixels = NULL;
		game_data->textures[i].width = 0;
		game_data->textures[i].height = 0;
		game_data->textures[i].line_len = 0;
		game_data->textures[i].bpp = 0;
		game_data->textures[i].endian = 0;
		i++;
	}
}

void	init_zero_data(t_game_data *game_data)
{
	if (!game_data)
		return ;
	game_data->bpp = 0;
	game_data->line_len = 0;
	game_data->endian = 0;
	game_data->screen_width = 0;
	game_data->screen_height = 0;
	game_data->map->width = 0;
}

void	init_null_data(t_game_data *game_data)
{
	if (!game_data)
		return ;
	game_data->tmp_map_lines = NULL;
	game_data->mlx = NULL;
	game_data->win = NULL;
	game_data->img = NULL;
	game_data->addr = NULL;
	game_data->ray = NULL;
	game_data->map->grid = NULL;
	game_data->no_texture_path = NULL;
	game_data->so_texture_path = NULL;
	game_data->we_texture_path = NULL;
	game_data->ea_texture_path = NULL;
}

void	init_unasigned_data(t_game_data *game_data)
{
	if (!game_data)
		return ;
	game_data->map->height = UNASSIGNED;
	game_data->ceiling_color = UNASSIGNED;
	game_data->floor_color = UNASSIGNED;
}
