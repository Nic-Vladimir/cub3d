/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:38:05 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 18:08:50 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

void	put_pixel(int x, int y, int color, t_game_data *game_data)
{
	int		offset;
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	offset = (game_data->line_len * y) + (x * (game_data->bpp / 8));
	dst = game_data->addr + offset;
	*(unsigned int *)dst = color;
}
