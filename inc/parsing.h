/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:46:58 by vnicoles          #+#    #+#             */
/*   Updated: 2025/05/11 17:01:50 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		parse_cub_file(const char *filename, t_game *game);
void	error_exit(const char *msg, t_game *game);

