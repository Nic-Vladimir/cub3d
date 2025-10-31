/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:28:03 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 21:51:07 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			total;

	if (size != 0 && count > UINT_MAX / size)
		return (NULL);
	total = count * size;
	tmp = malloc(total);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, total);
	return (tmp);
}
