/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:25:33 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 17:30:46 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

void	init_ray_tonull(t_ray *ray)
{
	ft_memset(ray, 0, sizeof(t_ray));
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
}
