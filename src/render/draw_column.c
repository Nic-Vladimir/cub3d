/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:20:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/09 13:15:39 by mgavornik        ###   ########.fr       */
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
		return (1.0f); // no shading yet
	else if (dist >= shade_start + shade_length)
		return (0.0f); // fully black
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
	// DEBUG
	// ft_printf("DEBUG get_texture_x: side=%d dir=(%.3f,%.3f) wall_x=%.5f tex_id=%d tex_x=%d\n",
	// 	ray->side, ray->dir.x, ray->dir.y, wall_x, tex_id, tex_x);
	return (tex_x);
}
t_values *init_values(t_values *values) 
{
	(void)values;
	values = ft_calloc(1, sizeof(t_values));
	if(!values)
		return NULL;
	return values;
}

void	draw_column(t_ray *ray, t_game_data *game_data, int screen_x)
{
	// int		line_height;
	// int		draw_start;
	// int		draw_end;
	// int		screen_y;
	// float	shading_factor;
	// float	floor_ceiling_shading_factor;
	// int		color;
	// float	dist;
	// int		ceiling_color;
	// int		floor_color;
	// float	p;
	// int		tex_id;
	// int		tex_x;
	// int		tex_y;
	// float	tex_step;
	// float	tex_pos;

	

	float posZ = 0.5f * HEIGHT; // camera distance to projection plane
	game_data->values->line_height = (int)(HEIGHT / ray->perp_dist);
	game_data->values->draw_start = fmax(0, -game_data->values->line_height / 2 + HEIGHT / 2);
	game_data->values->draw_end = fmin(HEIGHT - 1, game_data->values->line_height / 2 + HEIGHT / 2);
	game_data->values->shading_factor = calculate_shading(ray->perp_dist);
	game_data->values->screen_y = 0;
	game_data->values->color = shade_color(0xFF0000, game_data->values->shading_factor);
	game_data->values->tex_id = get_wall_texture(ray);
	game_data->values->tex_x = get_texture_x(ray, game_data, game_data->values->tex_id);
	game_data->values->tex_step = 1.0f * game_data->textures[game_data->values->tex_id].height / game_data->values->line_height;
	game_data->values->tex_pos = (game_data->values->draw_start - HEIGHT / 2 + game_data->values->line_height / 2) * game_data->values->tex_step;
	while (game_data->values->screen_y < game_data->values->draw_start)
	{
		game_data->values->p = game_data->values->screen_y - HEIGHT / 2.0f; // row distance from horizon
		if (game_data->values->p == 0)
			game_data->values->p = 0.0001f;        // avoid div by zero
		game_data->values->dist = fabsf(posZ / game_data->values->p); // distance (in world units / blocks)
		game_data->values->floor_ceiling_shading_factor = calculate_shading(game_data->values->dist);
		game_data->values->ceiling_color = shade_color(game_data->ceiling_color,
				game_data->values->floor_ceiling_shading_factor);
		put_pixel(screen_x, game_data->values->screen_y, game_data->values->ceiling_color, game_data);
		game_data->values->screen_y++;
	}
	while (game_data->values->screen_y <= game_data->values->draw_end)
	{
		game_data->values->tex_y = (int)game_data->values->tex_pos % game_data->textures[game_data->values->tex_id].height;
		if (game_data->values->tex_y < 0)
			game_data->values->tex_y += game_data->textures[game_data->values->tex_id].height;
		game_data->values->tex_pos += game_data->values->tex_step;
		game_data->values->color = game_data->textures[game_data->values->tex_id].pixels[game_data->values->tex_y
			* game_data->textures[game_data->values->tex_id].width + game_data->values->tex_x];
		game_data->values->color = shade_color(game_data->values->color, game_data->values->shading_factor);
		put_pixel(screen_x, game_data->values->screen_y, game_data->values->color, game_data);
		game_data->values->screen_y++;
	}
	while (game_data->values->screen_y < HEIGHT - 1)
	{
		game_data->values->p = game_data->values->screen_y - HEIGHT / 2.0f; // row distance from horizon
		if (game_data->values->p == 0)
			game_data->values->p = 0.0001f;        // avoid div by zero
		game_data->values->dist = fabsf(posZ / game_data->values->p); // distance (in world units / blocks)
		game_data->values->floor_ceiling_shading_factor = calculate_shading(game_data->values->dist);
		game_data->values->floor_color = shade_color(game_data->floor_color,
				game_data->values->floor_ceiling_shading_factor);
		put_pixel(screen_x, game_data->values->screen_y, game_data->values->floor_color, game_data);
		game_data->values->screen_y++;
	}
}
