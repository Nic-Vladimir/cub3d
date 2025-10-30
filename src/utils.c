/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:20:32 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/29 17:48:16 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"

int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

float	fov_to_plane_factor(float fov_deg)
{
	return (tan((fov_deg * PI / 180.0) / 2.0));
}
