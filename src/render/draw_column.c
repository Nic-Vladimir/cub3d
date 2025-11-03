/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:20:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/11/03 11:23:12 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float	calculate_shading(float dist)
{
	if (dist <= SHADE_START)
		return (1.0f);
	else if (dist >= SHADE_START + SHADE_LENGTH)
		return (0.0f);
	else
		return (1.0f - (dist - SHADE_START) / SHADE_LENGTH);
}

t_texture_id	get_wall_texture(t_ray *ray)
{
	if (ray->side)
	{
		if (ray->dir.y > 0)
			return (TEX_NORTH);
		else
			return (TEX_SOUTH);
	}
	else
	{
		if (ray->dir.x > 0)
			return (TEX_WEST);
		else
			return (TEX_EAST);
	}
}

int	get_texture_x(t_ray *ray, t_game_data *game_data, int tex_id)
{
	float	wall_x;
	int		tex_x;

	if (ray->side)
		wall_x = ray->intersection.x;
	else
		wall_x = ray->intersection.y;
	wall_x -= floorf(wall_x);
	tex_x = (int)(wall_x * game_data->textures[tex_id].width);
	if ((!ray->side && ray->dir.x > 0) || (ray->side && ray->dir.y < 0))
		tex_x = game_data->textures[tex_id].width - tex_x - 1;
	return (tex_x);
}

t_values	*init_values(t_values *values)
{
	(void)values;
	values = ft_calloc(1, sizeof(t_values));
	if (!values)
		return (NULL);
	return (values);
}

void	draw_column(t_ray *ray, t_game_data *game_data, int screen_x)
{
	float	posz;

	posz = 0.5f * HEIGHT;
	first_computation(ray, game_data);
	while (game_data->values->screen_y < game_data->values->draw_start)
	{
		draw_start(game_data, screen_x, posz);
	}
	while (game_data->values->screen_y <= game_data->values->draw_end)
	{
		draw_end(game_data, screen_x);
	}
	while (game_data->values->screen_y < HEIGHT - 1)
	{
		draw_shade(game_data, screen_x, posz);
	}
}
