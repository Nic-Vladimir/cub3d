/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:41:19 by vnicoles          #+#    #+#             */
/*   Updated: 2025/08/22 15:01:53 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <sys/time.h>

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	get_fps(void)
{
	static long	last_time = 0;
	static int	frames = 0;
	static int	fps = 0;
	long		now;

	now = get_time_ms();
	frames++;
	if (now - last_time >= 1000)
	{
		fps = frames;
		frames = 0;
		last_time = now;
		return (fps);
	}
	return (-1);
}

void	print_fps(void)
{
	int	fps;

	fps = get_fps();
	if (fps >= 0)
		ft_printf("FPS: %d\n", fps);
}
