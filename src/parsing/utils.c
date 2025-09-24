/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:00:41 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/24 11:16:12 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_data_identifier(const char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F' || c == 'C')
		return (true);
	return (false);
}

bool	is_number(const char *s)
{
	int	i;

	if (!s || !*s)
		return (false);
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	all_textures_and_colors_assigned(t_game_data *game_data)
{
	if (game_data->no_texture_path != NULL && game_data->so_texture_path != NULL
		&& game_data->ea_texture_path != NULL
		&& game_data->we_texture_path != NULL
		&& game_data->floor_color != UNASSIGNED
		&& game_data->ceiling_color != UNASSIGNED)
		return (true);
	return (false);
}

t_ErrorCode	check_args(int argc, char **argv)
{
	const char	*cub_file_path;
	int			fd;
	int			len;

	if (argc != 2)
		return (ERR_USAGE);
	cub_file_path = argv[1];
	len = ft_strlen(cub_file_path);
	if (len <= 4 || ft_strcmp(cub_file_path + len - 4, ".cub") != 0)
		return (ERR_INVALID_FILENAME);
	fd = open(cub_file_path, O_RDONLY);
	if (fd == -1)
		return (ERR_INVALID_PATH);
	close(fd);
	return (ERR_OK);
}
