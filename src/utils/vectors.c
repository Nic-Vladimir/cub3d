/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:14:31 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 21:04:34 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vectors.h"

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x + b.x, a.y + b.y});
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x - b.x, a.y - b.y});
}

t_vec2	vec2_scale(t_vec2 v, float scale)
{
	return ((t_vec2){v.x * scale, v.y * scale});
}

float	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}
