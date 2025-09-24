/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:09:08 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/24 11:15:33 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_ErrorCode	parse_texture_line(t_game_data *game_data, const char *line,
		int id_index, int data_index)
{
	int					j;
	t_texture_path_info	map[5];

	map[0] = (t_texture_path_info){"NO ", &game_data->no_texture_path};
	map[1] = (t_texture_path_info){"SO ", &game_data->so_texture_path};
	map[2] = (t_texture_path_info){"WE ", &game_data->we_texture_path};
	map[3] = (t_texture_path_info){"EA ", &game_data->ea_texture_path};
	map[4] = (t_texture_path_info){NULL, NULL};
	j = 0;
	while (map[j].prefix)
	{
		if (ft_strncmp(line + id_index, map[j].prefix, 3) == 0)
		{
			if (*(map[j].target) != NULL)
				return (ERR_DUP_TEXTURE);
			*(map[j].target) = ft_strdup(line + data_index);
			if (*(map[j].target) == NULL)
				return (ERR_ALLOC);
			ft_remove_newline(*(map[j].target));
			return (ERR_OK);
		}
		j++;
	}
	return (ERR_UNKNOWN_TEXTURE_ID);
}
