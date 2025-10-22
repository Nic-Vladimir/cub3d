/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:58:53 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/10 12:13:31 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

static void	init_ray_data(t_ray *ray, t_player *player, int screen_x)
{
	ft_memset(ray, 0, sizeof(t_ray));
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

static void	init_dda(t_ray *ray)
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

static void	check_collision(t_ray *ray, t_game_data *game_data)
{
	if (ray->map_check.x >= 0 && ray->map_check.x <= game_data->map->width
		&& ray->map_check.y >= 0 && ray->map_check.y <= game_data->map->height)
	{
		if (game_data->map->grid[ray->map_check.y][ray->map_check.x] == '1')
		{
			ray->hit = true;
			ray->intersection = vec2_add(ray->start, vec2_scale(ray->dir,
						ray->travel_dist));
			// draw_circle(ray->intersection.x, ray->intersection.y, 0.1,
			// 	0x00FF00, game_data);
		}
	}
}

static void	run_dda(t_ray *ray, t_game_data *game_data)
{
	while (!ray->hit && ray->travel_dist < DRAW_DISTANCE)
	{
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
		check_collision(ray, game_data);
	}
}

void	compute_perp_dist(t_ray *ray)
{
	if (!ray->hit)
	{
		ray->perp_dist = DRAW_DISTANCE;
		return ;
	}
	if (ray->side)
		ray->perp_dist = (ray->intersection.y - ray->start.y) / ray->dir.y;
	else
		ray->perp_dist = (ray->intersection.x - ray->start.x) / ray->dir.x;
	ray->perp_dist = fabsf(ray->perp_dist);
	// if (ray->perp_dist <= 1e-6f)
	// 	ray->perp_dist = 1e-6f;
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
		screen_x++;
	}
}
