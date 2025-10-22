/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codebuff <codebuff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:00:00 by codebuff          #+#    #+#             */
/*   Updated: 2025/01/20 00:00:00 by codebuff         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

static void	put_pixel_clipped(int x, int y, int color, t_game_data *game_data,
		int min_x, int min_y, int max_x, int max_y)
{
	if (x < min_x || x >= max_x || y < min_y || y >= max_y)
		return;
	put_pixel(x, y, color, game_data);
}

void	draw_circle_minimap(float cx, float cy, float radius, int color,
		t_game_data *game_data, int offset_x, int offset_y, float scale)
{
	int	x;
	int	y;
	int	err;
	int	scaled_cx;
	int	scaled_cy;
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;

	min_x = offset_x;
	min_y = offset_y;
	max_x = offset_x + MINIMAP_SIZE;
	max_y = offset_y + MINIMAP_SIZE;
	x = radius * scale;
	y = 0;
	err = 0;
	scaled_cx = cx * scale + offset_x;
	scaled_cy = cy * scale + offset_y;
	while (x >= y)
	{
		put_pixel_clipped(scaled_cx + x, scaled_cy + y, color, game_data, min_x, min_y, max_x, max_y);
		put_pixel_clipped(scaled_cx + y, scaled_cy + x, color, game_data, min_x, min_y, max_x, max_y);
		put_pixel_clipped(scaled_cx - y, scaled_cy + x, color, game_data, min_x, min_y, max_x, max_y);
		put_pixel_clipped(scaled_cx - x, scaled_cy + y, color, game_data, min_x, min_y, max_x, max_y);
		put_pixel_clipped(scaled_cx - x, scaled_cy - y, color, game_data, min_x, min_y, max_x, max_y);
		put_pixel_clipped(scaled_cx - y, scaled_cy - x, color, game_data, min_x, min_y, max_x, max_y);
		put_pixel_clipped(scaled_cx + y, scaled_cy - x, color, game_data, min_x, min_y, max_x, max_y);
		put_pixel_clipped(scaled_cx + x, scaled_cy - y, color, game_data, min_x, min_y, max_x, max_y);
		y++;
		if (err <= 0)
			err += 2 * y + 1;
		if (err > 0)
		{
			x--;
			err -= 2 * x + 1;
		}
	}
}

static void	draw_square_minimap(int x, int y, int size, int color,
		t_game_data *game_data, int offset_x, int offset_y, int min_x, int min_y,
		int max_x, int max_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_clipped(x + i + offset_x, y + j + offset_y, color,
				game_data, min_x, min_y, max_x, max_y);
			j++;
		}
		i++;
	}
}

static void	draw_map_minimap(t_game_data *game_data, int center_x, int center_y,
		float scale, int minimap_x, int minimap_y)
{
	char	**grid;
	int		color;
	int		x;
	int		y;
	int		min_x;
	int		min_y;
	int		max_x;
	int		max_y;

	grid = game_data->map->grid;
	color = 0x404040;
	min_x = minimap_x;
	min_y = minimap_y;
	max_x = minimap_x + MINIMAP_SIZE;
	max_y = minimap_y + MINIMAP_SIZE;
	y = 0;
	while (y < game_data->map->height && grid[y])
	{
		x = 0;
		while (x < game_data->map->width && grid[y][x])
		{
			if (grid[y][x] == '1')
			{
				int draw_x = center_x + (x - game_data->player->pos.x) * scale;
				int draw_y = center_y + (y - game_data->player->pos.y) * scale;
				draw_square_minimap(draw_x, draw_y, scale, color, game_data, 0, 0,
					min_x, min_y, max_x, max_y);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game_data *game_data)
{
	int		offset_x;
	int		offset_y;
	float	scale;
	int		i;
	int		j;

	offset_x = 10;
	offset_y = 10;
	scale = MINIMAP_SCALE;
	// Draw black background for minimap
	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			put_pixel(offset_x + i, offset_y + j, 0x000000, game_data);
			j++;
		}
		i++;
	}
	// Draw map (centered on player)
	draw_map_minimap(game_data, offset_x + MINIMAP_SIZE / 2,
		offset_y + MINIMAP_SIZE / 2, scale, offset_x, offset_y);
	// Draw player position (always at center of minimap)
	draw_circle_minimap(0, 0, 0.3, 0x00FF00, game_data,
		offset_x + MINIMAP_SIZE / 2, offset_y + MINIMAP_SIZE / 2, scale);
	// Draw minimap border (drawn last to ensure it's on top)
	i = 0;
	while (i < MINIMAP_SIZE)
	{
		put_pixel(offset_x + i, offset_y, 0xFFFFFF, game_data);
		put_pixel(offset_x + i, offset_y + MINIMAP_SIZE - 1, 0xFFFFFF,
			game_data);
		put_pixel(offset_x, offset_y + i, 0xFFFFFF, game_data);
		put_pixel(offset_x + MINIMAP_SIZE - 1, offset_y + i, 0xFFFFFF,
			game_data);
		i++;
	}
}
