/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:22:11 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 15:26:26 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "vectors.h"

typedef struct s_ray
{
	t_vec2					start;
	t_vec2					dir;
	t_vec2					step;
	t_vec2					len;
	t_vec2					intersection;
	t_int_vec2				map_check;
	t_int_vec2				v_step;
	float					screen_x;
	float					travel_dist;
	float					perp_dist;
	bool					side;
	bool					hit;
}							t_ray;

typedef struct s_game_data	t_game_data;

void						cast_ray(t_game_data *game_data);

#endif
