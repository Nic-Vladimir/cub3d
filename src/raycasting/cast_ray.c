/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:58:53 by vnicoles          #+#    #+#             */
/*   Updated: 2025/11/01 11:19:57 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_ray_data(t_ray *ray, t_player *player, int screen_x)
{
	init_ray_tonull(ray);
	ray->screen_x = 2 * screen_x / (float)WIDTH - 1;
	ray->start = player->pos;
	ray->dir.x = player->dir.x + player->camera_plane.x * ray->screen_x;
	ray->dir.y = player->dir.y + player->camera_plane.y * ray->screen_x;
	ray->step.x = fabsf(1 / ray->dir.x);
	ray->step.y = fabsf(1 / ray->dir.y);
	ray->map_check.x = (int)ray->start.x;
	ray->map_check.y = (int)ray->start.y;
	ray->travel_dist = 0;
	ray->hit = false;
}

void	init_dda(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->v_step.x = -1;
		ray->len.x = (ray->start.x - ray->map_check.x) * ray->step.x;
	}
	else
	{
		ray->v_step.x = 1;
		ray->len.x = ((ray->map_check.x + 1) - ray->start.x) * ray->step.x;
	}
	if (ray->dir.y < 0)
	{
		ray->v_step.y = -1;
		ray->len.y = (ray->start.y - ray->map_check.y) * ray->step.y;
	}
	else
	{
		ray->v_step.y = 1;
		ray->len.y = ((ray->map_check.y + 1) - ray->start.y) * ray->step.y;
	}
}

static void	dda_data_update(t_ray *ray)
{
	if (!ray)
		return ;
	if (ray->len.x < ray->len.y)
	{
		ray->map_check.x += ray->v_step.x;
		ray->travel_dist = ray->len.x;
		ray->len.x += ray->step.x;
		ray->side = false;
	}
	else
	{
		ray->map_check.y += ray->v_step.y;
		ray->travel_dist = ray->len.y;
		ray->len.y += ray->step.y;
		ray->side = true;
	}
}

void	run_dda(t_ray *ray, t_game_data *game_data)
{
	if (!ray || !game_data || !game_data->map || !game_data->map->grid)
		return ;
	while (!ray->hit && ray->travel_dist < DRAW_DISTANCE)
	{
		dda_data_update(ray);
		if (ray->map_check.x >= 0 && ray->map_check.x <= game_data->map->width
			&& ray->map_check.y >= 0
			&& ray->map_check.y <= game_data->map->height)
		{
			if (game_data->map->grid[ray->map_check.y][ray->map_check.x] == '1')
			{
				ray->hit = true;
				ray->intersection = vec2_add(ray->start, vec2_scale(ray->dir,
							ray->travel_dist));
			}
		}
	}
}

void	cast_ray(t_game_data *game_data)
{
	t_ray	ray;
	int		screen_x;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		init_ray_data(&ray, game_data->player, screen_x);
		init_dda(&ray);
		run_dda(&ray, game_data);
		compute_perp_dist(&ray);
		draw_column(&ray, game_data, screen_x);
		if (game_data->ray)
			ft_memcpy(game_data->ray, &ray, sizeof(t_ray));
		screen_x++;
	}
}
