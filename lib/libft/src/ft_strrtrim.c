/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrtrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:33:38 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 21:38:19 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrtrim(const char *s, const char *set)
{
	size_t	end;

	if (!s)
		return (NULL);
	end = ft_strlen(s);
	while (end > 0 && ft_strchr(set, s[end - 1]))
		end--;
	return (ft_substr(s, 0, end));
}
