/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:12:10 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 21:02:03 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_vec2
{
	float	x;
	float	y;
}			t_vec2;

typedef struct s_int_vec2
{
	int		x;
	int		y;
}			t_int_vec2;

// --- Vec2 Utils ---
t_vec2		vec2_add(t_vec2 a, t_vec2 b);
t_vec2		vec2_sub(t_vec2 a, t_vec2 b);
t_vec2		vec2_scale(t_vec2 v, float scale);
float		vec2_dot(t_vec2 a, t_vec2 b);

#endif
