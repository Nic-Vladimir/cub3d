/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:47:48 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 15:27:38 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef VALUES_H
# define VALUES_H

# include "../inc/cub3d.h"

typedef struct s_values
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		screen_y;
	int		color;
	int		ceiling_color;
	int		floor_color;
	int		tex_id;
	int		tex_x;
	int		tex_y;
	float	shading_factor;
	float	floor_ceiling_shading_factor;
	float	dist;
	float	p;
	float	tex_step;
	float	tex_pos;
}			t_values;

t_values	*init_values(t_values *values);

#endif
