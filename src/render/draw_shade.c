/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:03:34 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 21:04:15 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
