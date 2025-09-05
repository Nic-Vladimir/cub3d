/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:55:37 by vnicoles          #+#    #+#             */
/*   Updated: 2025/08/22 17:59:52 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	exit_err(char *err, int exit_code)
{
	ft_printf("cub3d ERROR: %s\n", err);
	exit(exit_code);
}
