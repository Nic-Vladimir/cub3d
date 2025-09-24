/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:20:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/24 19:38:12 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	draw_column(t_ray *ray, t_game_data *game_data, int screen_x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		screen_y;
	float	shading_factor;
	float	floor_ceiling_shading_factor;
	int		color;
	float	dist;
	int		ceiling_color;
	int		floor_color;
	float	p;
	int		tex_id;
	int		tex_x;
	int		tex_y;
	float	tex_step;
	float	tex_pos;

	float posZ = 0.5f * HEIGHT; // camera distance to projection plane
	line_height = (int)(HEIGHT / ray->perp_dist);
	draw_start = fmax(0, -line_height / 2 + HEIGHT / 2);
	draw_end = fmin(HEIGHT - 1, line_height / 2 + HEIGHT / 2);
	shading_factor = calculate_shading(ray->perp_dist);
	screen_y = 0;
	color = shade_color(0xFF0000, shading_factor);
	tex_id = get_wall_texture(ray);
	tex_x = get_texture_x(ray, game_data, tex_id);
	tex_step = 1.0f * game_data->textures[tex_id].height / line_height;
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * tex_step;
	while (screen_y < draw_start)
	{
		p = screen_y - HEIGHT / 2.0f; // row distance from horizon
		if (p == 0)
			p = 0.0001f;        // avoid div by zero
		dist = fabsf(posZ / p); // distance (in world units / blocks)
		floor_ceiling_shading_factor = calculate_shading(dist);
		ceiling_color = shade_color(game_data->ceiling_color,
				floor_ceiling_shading_factor);
		put_pixel(screen_x, screen_y, ceiling_color, game_data);
		screen_y++;
	}
	while (screen_y <= draw_end)
	{
		tex_y = (int)tex_pos % game_data->textures[tex_id].height;
		if (tex_y < 0)
			tex_y += game_data->textures[tex_id].height;
		tex_pos += tex_step;
		color = game_data->textures[tex_id].pixels[tex_y
			* game_data->textures[tex_id].width + tex_x];
		color = shade_color(color, shading_factor);
		put_pixel(screen_x, screen_y, color, game_data);
		screen_y++;
	}
	while (screen_y < HEIGHT - 1)
	{
		p = screen_y - HEIGHT / 2.0f; // row distance from horizon
		if (p == 0)
			p = 0.0001f;        // avoid div by zero
		dist = fabsf(posZ / p); // distance (in world units / blocks)
		floor_ceiling_shading_factor = calculate_shading(dist);
		floor_color = shade_color(game_data->floor_color,
				floor_ceiling_shading_factor);
		put_pixel(screen_x, screen_y, floor_color, game_data);
		screen_y++;
	}
}
