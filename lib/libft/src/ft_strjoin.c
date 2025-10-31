/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:45:18 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 21:36:17 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	*ft_strjoin_alloc(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (NULL);
	return (ft_strjoin_alloc(s1, s2));
}
