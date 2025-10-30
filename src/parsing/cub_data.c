/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:53:52 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/09 18:10:39 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

t_ErrorCode	parse_data_line(t_game_data *game_data, const char *line,
		int id_index)
{
	int	data_index;

	if (game_data->in_map == true)
		return (ERR_INVALID_ORDER);
	data_index = id_index + 1;
	if (line[id_index] == 'N' || line[id_index] == 'S' || line[id_index] == 'W'
		|| line[id_index] == 'E')
		data_index++;
	while (ft_is_whitespace(line[data_index]))
		data_index++;
	if (line[data_index] == '\n' || line[data_index] == '\0')
		return (ERR_INVALID_DATA_FORMAT);
	if (ft_strncmp(line + id_index, "F ", 2) == 0 || ft_strncmp(line + id_index,
			"C ", 2) == 0)
		return (parse_color_line(game_data, line, id_index, data_index));
	else
		return (parse_texture_line(game_data, line, id_index, data_index));
}

static t_ErrorCode	parse_cub_line(t_game_data *game_data, char *line)
{
	t_ErrorCode	err;
	int			i;

	i = 0;
	while (ft_is_whitespace(line[i]))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (ERR_OK);
	if (is_data_identifier(line[i]))
	{
		err = parse_data_line(game_data, line, i);
		if (err != ERR_OK)
			return (err);
	}
	else if (all_textures_and_colors_assigned(game_data))
	{
		err = parse_map_line(game_data, line, i);
		if (err != ERR_OK)
			return (err);
	}
	else
		return (ERR_INVALID_ORDER);
	return (ERR_OK);
}

t_ErrorCode	parse_cub_data(t_game_data *game_data, char **argv)
{
	const char	*path;
	char		*line;
	t_ErrorCode	err;
	int			fd;

	path = argv[1];
	fd = open(path, O_RDONLY);
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		// ft_printf("row: %d\n", i++);
		err = parse_cub_line(game_data, line);
		free(line);
		if (err != ERR_OK)
		{
			while ((line = ft_get_next_line(fd)) != NULL)
				free(line);
			close(fd);
			return (err);
		}
	}
	close(fd);
	return (ERR_OK);
}
