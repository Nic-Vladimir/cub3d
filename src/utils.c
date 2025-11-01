/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:20:32 by vnicoles          #+#    #+#             */
/*   Updated: 2025/11/01 20:53:27 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

float	fov_to_plane_factor(float fov_deg)
{
	return (tan((fov_deg * PI / 180.0) / 2.0));
}

void	remove_whitespace(char *chars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chars[i])
	{
		if (!ft_is_whitespace(chars[i]))
			chars[j++] = chars[i];
		i++;
	}
	chars[j] = '\0';
}

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

void	fill_texture_pixels(t_texture *tex)
{
	tex->pixels = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
}
