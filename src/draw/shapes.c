/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:02:08 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 19:20:39 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"

void	draw_circle(float cx, float cy, t_circ_mod mod, t_game_data *game_data)
{
	t_circle	*circle;

	circle = init_circle();
	if (mod)
		mod(&circle->radius, &circle->color, game_data);
	circle->angle_step = 10.0f;
	while (circle->angle < 360.0f)
	{
		circle->theta = convrad(circle->angle);
		circle->point_x = cx + circle->radius * cos(circle->theta);
		circle->point_y = cy + circle->radius * sin(circle->theta);
		put_pixel(circle->point_x * SCALE_FACTOR, circle->point_y
			* SCALE_FACTOR, circle->color, game_data);
		circle->angle += circle->angle_step;
	}
	free(circle);
}

void	draw_square(int x, int y, int size, t_game_data *game_data)
{
	int	i;
	int	color;

	color = game_data->color;
	i = 0;
	while (i < size)
		put_pixel(x + i++, y, color, game_data);
	i = 0;
	while (i < size)
		put_pixel(x, y + i++, color, game_data);
	i = 0;
	while (i < size)
		put_pixel(x + size, y + i++, color, game_data);
	i = 0;
	while (i < size)
		put_pixel(x + i++, y + size, color, game_data);
}

void	draw_map(t_game_data *game_data)
{
	char	**grid;
	int		x;
	int		y;

	game_data->color = 0x0000FF;
	grid = game_data->map->grid;
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

void	draw_line(t_player *player, t_game_data *game_data, float start_x,
		int i)
{
	t_line	line;

	init_line(&line);
	line.cos_angle = cos(start_x);
	line.sin_angle = sin(start_x);
	line.ray_x = player->pos.x;
	line.ray_y = player->pos.y;
	while (!touch_wall(line.ray_x + line.cos_angle * 5, line.ray_y
			+ line.sin_angle * 5, game_data))
	{
		if (DEBUG)
			put_pixel(line.ray_x, line.ray_y, 0xFF0000, game_data);
		line.ray_x += line.cos_angle;
		line.ray_y += line.sin_angle;
	}
	if (!DEBUG)
	{
		line.dist = fixed_dist(player->pos.x, player->pos.y, line.ray_x,
				line.ray_y, game_data);
		line.height = (BLOCK_SIZE / line.dist) * (WIDTH / 2);
		line.start_y = (HEIGHT - line.height) / 2;
		line.end = line.start_y + line.height;
		while (line.start_y < line.end)
			put_pixel(i, line.start_y++, 255, game_data);
	}
}

int	draw_loop(t_game_data *game_data)
{
	t_player	*player;

	player = game_data->player;
	move_player(game_data);
	clear_image(game_data);
	draw_circle(player->pos.x, player->pos.y, player_mod, game_data);
	draw_map(game_data);
	cast_ray(game_data);
	radar_loop(game_data);
	mlx_put_image_to_window(game_data->mlx, game_data->win, game_data->img, 0,
		0);
	return (0);
}
