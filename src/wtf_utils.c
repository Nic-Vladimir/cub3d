/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wtf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:54:44 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 19:59:53 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"

void	clear_image(t_game_data *game_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game_data);
			x++;
		}
		y++;
	}
}

bool	touch_wall(float px, float py, t_game_data *game_data)
{
	int	x;
	int	y;

	x = px / BLOCK_SIZE;
	y = py / BLOCK_SIZE;
	if (game_data->map->grid[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2,
					t_game_data *game_data) // TOO MANY ARGS
{
	t_vec2 delta;
	t_player *p;

	delta.x = x2 - x1;
	delta.y = y2 - y1;
	p = game_data->player;
	return (vec2_dot(delta, (t_vec2){p->dir.x, p->dir.y}));
}

void	fill_texture_pixels(t_texture *tex)
{
	tex->pixels = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
}
