/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:59:46 by vnicoles          #+#    #+#             */
/*   Updated: 2025/05/12 00:41:17 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_cub_file(const char *filename)
{
	int		fd;
	int		char_index;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = NULL;
	if (fd < 0)
		error_exit("Error\nFailed to open file", game);
	while ((line = get_next_line(fd)))
	{
		if (is_line_empty(line))
			free(line);
		char_index = 0;
		while (line[char_index])
		{
			if (is_whitespace(line[char_index]))
			{
				char_index++;
				continue ;
			}
			check_data_element(line, char_index, game);
		}
	}
	close(fd);
	if ()
}
