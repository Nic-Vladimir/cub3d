/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:20:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 17:36:40 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

float	calculate_shading(float dist)
{
	float	shade_length;
	float	shade_start;

	shade_start = 1.5f;
	shade_length = 3.0f;
	if (dist <= shade_start)
		return (1.0f);
	else if (dist >= shade_start + shade_length)
		return (0.0f);
	else
		return (1.0f - (dist - shade_start) / shade_length);
}

int	shade_color(int color, float shading_factor)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * shading_factor;
	g = ((color >> 8) & 0xFF) * shading_factor;
	b = (color & 0xFF) * shading_factor;
	color = (r << 16) | (g << 8) | b;
	return (color);
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

void	first_computation(t_ray *ray, t_game_data *game_data)
{
	game_data->values->line_height = (int)(HEIGHT / ray->perp_dist);
	game_data->values->draw_start = fmax(0, -game_data->values->line_height / 2
			+ HEIGHT / 2);
	game_data->values->draw_end = fmin(HEIGHT - 1,
			game_data->values->line_height / 2 + HEIGHT / 2);
	game_data->values->shading_factor = calculate_shading(ray->perp_dist);
	game_data->values->screen_y = 0;
	game_data->values->color = shade_color(0xFF0000,
			game_data->values->shading_factor);
	game_data->values->tex_id = get_wall_texture(ray);
	game_data->values->tex_x = get_texture_x(ray, game_data,
			game_data->values->tex_id);
	game_data->values->tex_step = 1.0f
		* game_data->textures[game_data->values->tex_id].height
		/ game_data->values->line_height;
	game_data->values->tex_pos = (game_data->values->draw_start - HEIGHT / 2
			+ game_data->values->line_height / 2) * game_data->values->tex_step;
}

void	draw_start(t_game_data *game_data, int screen_x, float posZ)
{
	game_data->values->p = game_data->values->screen_y - HEIGHT / 2.0f;
	if (game_data->values->p == 0)
		game_data->values->p = 0.0001f;
	game_data->values->dist = fabsf(posZ / game_data->values->p);
	game_data->values->floor_ceiling_shading_factor = \
calculate_shading(game_data->values->dist);
	game_data->values->ceiling_color = shade_color(game_data->ceiling_color,
			game_data->values->floor_ceiling_shading_factor);
	put_pixel(screen_x, game_data->values->screen_y,
		game_data->values->ceiling_color, game_data);
	game_data->values->screen_y++;
}

void	draw_end(t_game_data *game_data, int screen_x)
{
	game_data->values->tex_y = (int)game_data->values->tex_pos
		% game_data->textures[game_data->values->tex_id].height;
	if (game_data->values->tex_y < 0)
		game_data->values->tex_y
			+= game_data->textures[game_data->values->tex_id].height;
	game_data->values->tex_pos += game_data->values->tex_step;
	game_data->values->color = \
game_data->textures[game_data->values->tex_id].pixels[game_data->values->tex_y
		* game_data->textures[game_data->values->tex_id].width
		+ game_data->values->tex_x];
	game_data->values->color = shade_color(game_data->values->color,
			game_data->values->shading_factor);
	put_pixel(screen_x, game_data->values->screen_y, game_data->values->color,
		game_data);
	game_data->values->screen_y++;
}

void	draw_shade(t_game_data *game_data, int screen_x, float posZ)
{
	game_data->values->p = game_data->values->screen_y - HEIGHT / 2.0f;
	if (game_data->values->p == 0)
		game_data->values->p = 0.0001f;
	game_data->values->dist = fabsf(posZ / game_data->values->p);
	game_data->values->floor_ceiling_shading_factor = \
calculate_shading(game_data->values->dist);
	game_data->values->floor_color = shade_color(game_data->floor_color,
			game_data->values->floor_ceiling_shading_factor);
	put_pixel(screen_x, game_data->values->screen_y,
		game_data->values->floor_color, game_data);
	game_data->values->screen_y++;
}

void	draw_column(t_ray *ray, t_game_data *game_data, int screen_x)
{
	float	posZ;

	posZ = 0.5f * HEIGHT;
	first_computation(ray, game_data);
	while (game_data->values->screen_y < game_data->values->draw_start)
	{
		draw_start(game_data, screen_x, posZ);
	}
	while (game_data->values->screen_y <= game_data->values->draw_end)
	{
		draw_end(game_data, screen_x);
	}
	while (game_data->values->screen_y < HEIGHT - 1)
	{
		draw_shade(game_data, screen_x, posZ);
	}
}
