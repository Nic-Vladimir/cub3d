/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:52:07 by vnicoles          #+#    #+#             */
/*   Updated: 2025/11/01 11:22:00 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_line(t_vec2 start, t_vec2 end, t_game_data *game_data)
{
	t_vec2	delta;
	t_vec2	current;
	float	steps;
	int		i;

	start.x *= SCALE_FACTOR;
	start.y *= SCALE_FACTOR;
	end.x *= SCALE_FACTOR;
	end.y *= SCALE_FACTOR;
	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	steps = fabsf(delta.x);
	if (fabsf(delta.y) > steps)
		steps = fabsf(delta.y);
	delta.x /= steps;
	delta.y /= steps;
	current = start;
	i = 0;
	while (i <= steps)
	{
		put_pixel((int)current.x, (int)current.y, game_data->color, game_data);
		current.x += delta.x;
		current.y += delta.y;
		i++;
	}
}

void	draw_vision_cone(t_game_data *game_data)
{
	t_ray	ray;
	int		screen_x;

	game_data->color = 0x00FF00;
	screen_x = 0;
	while (screen_x < WIDTH)
	{
		if (screen_x % 5 == 0)
		{
			init_ray_data(&ray, game_data->player, screen_x);
			init_dda(&ray);
			run_dda(&ray, game_data);
			if (ray.hit)
				draw_line(ray.start, ray.intersection, game_data);
		}
		screen_x++;
	}
}

void	draw_rectangle(t_vec2 top_left, t_vec2 bottom_right,
		t_game_data *game_data)
{
	int	x;
	int	y;
	int	color;
	int	width;
	int	height;

	color = game_data->color;
	width = (int)(bottom_right.x - top_left.x);
	height = (int)(bottom_right.y - top_left.y);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			put_pixel((int)top_left.x + x, (int)top_left.y + y, color,
				game_data);
			x++;
		}
		y++;
	}
}

void	draw_map_background(t_game_data *game_data)
{
	int		padding;
	t_vec2	top_left;
	t_vec2	bottom_right;
	t_vec2	top_left_border;
	t_vec2	bottom_right_border;

	padding = 12;
	top_left.x = 0;
	top_left.y = 0;
	bottom_right.x = (game_data->map->width * SCALE_FACTOR) + padding;
	bottom_right.y = (game_data->map->height * SCALE_FACTOR) + padding * 2;
	top_left_border.x = 0;
	top_left_border.y = 0;
	bottom_right_border.x = bottom_right.x + padding;
	bottom_right_border.y = bottom_right.y + padding;
	game_data->color = 0x000000;
	draw_rectangle(top_left_border, bottom_right_border, game_data);
	game_data->color = game_data->floor_color;
	draw_rectangle(top_left, bottom_right, game_data);
}

void	draw_map(t_game_data *game_data)
{
	char	**grid;
	int		x;
	int		y;

	grid = game_data->map->grid;
	draw_map_background(game_data);
	game_data->color = 0x333333;
	x = 0;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == '1')
				draw_square(x * SCALE_FACTOR, y * SCALE_FACTOR, SCALE_FACTOR,
					game_data);
			x++;
		}
		y++;
	}
}
