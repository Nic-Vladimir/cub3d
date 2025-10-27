/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:37:23 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/22 15:38:10 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_tex_data(t_game_data *game_data)
{
	int	i;

	i = 0;
	if (!game_data)
		return ;
	while (i < 4)
	{
		game_data->textures[i].img = NULL;
		game_data->textures[i].pixels = NULL;
		game_data->textures[i].width = 0;
		game_data->textures[i].height = 0;
		game_data->textures[i].line_len = 0;
		game_data->textures[i].bpp = 0;
		game_data->textures[i].endian = 0;
		i++;
	}
}
void	init_zero_data(t_game_data *game_data)
{
	if (!game_data)
		return ;
	game_data->bpp = 0;
	game_data->line_len = 0;
	game_data->endian = 0;
	game_data->screen_width = 0;
	game_data->screen_height = 0;
	game_data->map->width = 0;
}
void	init_null_data(t_game_data *game_data)
{
	if (!game_data)
		return ;
	game_data->tmp_map_lines = NULL;
	game_data->mlx = NULL;
	game_data->win = NULL;
	game_data->img = NULL;
	game_data->addr = NULL;
	game_data->map->grid = NULL;
	game_data->no_texture_path = NULL;
	game_data->so_texture_path = NULL;
	game_data->we_texture_path = NULL;
	game_data->ea_texture_path = NULL;
}
void	init_unasigned_data(t_game_data *game_data)
{
	if (!game_data)
		return ;
	game_data->map->height = UNASSIGNED;
	game_data->ceiling_color = UNASSIGNED;
	game_data->floor_color = UNASSIGNED;
}

t_ErrorCode	init_game_data(t_game_data *game_data)
{
	if (!game_data)
		return (ERR_ALLOC);
	protected_malloc(game_data);
	// game_data->values = init_values(game_data->values);
	init_tex_data(game_data);
	init_zero_data(game_data);
	init_null_data(game_data);
	init_unasigned_data(game_data);
	game_data->player->pos_set = false;
	game_data->in_map = false;
	game_data->player->fov_factor = fov_to_plane_factor(FOV);
	init_player(game_data->player);
	return (ERR_OK);
}
