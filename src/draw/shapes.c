/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:02:08 by mgavornik         #+#    #+#             */
/*   Updated: 2025/11/01 21:32:04 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	int	j;
	int	color;

	color = game_data->color;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			put_pixel(x + i, y + j, color, game_data);
			i++;
		}
		j++;
	}
}

int	draw_loop(t_game_data *game_data)
{
	float	dt;

	dt = calculate_dt();
	print_fps();
	move_player(game_data, dt);
	clear_image(game_data);
	cast_ray(game_data);
	draw_minimap_if_needed(game_data);
	mlx_put_image_to_window(game_data->mlx, game_data->win, game_data->img, 0,
		0);
	return (0);
}
