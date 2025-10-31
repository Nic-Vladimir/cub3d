/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:19:04 by mgavornik         #+#    #+#             */
/*   Updated: 2025/10/31 13:18:30 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"

float convrad(float ang)
{
    return (ang * PI / 180.0f);
}

void	right_cell_col(t_radar *radar, t_game_data *game_data)
{
    char	cell;

    if (radar->fraction_x > (1.0 - radar->collision_dist) && radar->grid_x
        + 1 <= game_data->map->width)
    {
        cell = game_data->map->grid[radar->grid_y][radar->grid_x + 1];
        if (cell == '1')
        {
            radar->boundry = true;
        }
    }
}

void	left_cell_col(t_radar *radar, t_game_data *game_data)
{
    char	cell;

    if (radar->fraction_x < radar->collision_dist && radar->grid_x > 0)
    {
        cell = game_data->map->grid[radar->grid_y][radar->grid_x - 1];
        if (cell == '1')
        {
            radar->boundry = true;
        }
    }
}

void	bottom_cell_col(t_radar *radar, t_game_data *game_data)
{
    char	cell;

    if (radar->fraction_y > (1.0 - radar->collision_dist) && radar->grid_y
        + 1 <= (game_data->map->height + 1))
    {
        if (game_data->map->grid[radar->grid_y + 1])
        {
            cell = game_data->map->grid[radar->grid_y + 1][radar->grid_x];
            if (cell == '1')
            {
                radar->boundry = true;
            }
        }
    }
}

void	top_cell_col(t_radar *radar, t_game_data *game_data)
{
    char	cell;

    if (radar->fraction_y < radar->collision_dist && radar->grid_y > 0)
    {
        cell = game_data->map->grid[radar->grid_y - 1][radar->grid_x];
        if (cell == '1')
        {
            radar->boundry = true;
        }
    }
}
void diag_cell_col(t_radar *radar, t_game_data *game_data)
{
    diag_cell_col_br(radar, game_data);
    diag_cell_col_bl(radar, game_data);
    diag_cell_col_tr(radar, game_data);
    diag_cell_col_tl(radar, game_data);
}

void	diag_cell_col_br(t_radar *radar, t_game_data *game_data)
{
    char	cell;

    // Bottom-right diagonal
    if ((radar->fraction_x > (1.0 - radar->collision_dist)
            && radar->fraction_y > (1.0 - radar->collision_dist))
        && (radar->grid_x + 1 < game_data->map->width && radar->grid_y
            + 1 < game_data->map->height))
    {
        if (game_data->map->grid[radar->grid_y + 1])
        {
            cell = game_data->map->grid[radar->grid_y + 1][radar->grid_x + 1];
            if (cell == '1')
            {
                radar->boundry = true;
            }
        }
    }
}
void	diag_cell_col_bl(t_radar *radar, t_game_data *game_data)
{
    char	cell;

    // Bottom-left diagonal
    if ((radar->fraction_x < radar->collision_dist
            && radar->fraction_y > (1.0 - radar->collision_dist))
        && (radar->grid_x > 0 && radar->grid_y + 1 < game_data->map->height))
    {
        if (game_data->map->grid[radar->grid_y + 1])
        {
            cell = game_data->map->grid[radar->grid_y + 1][radar->grid_x - 1];
            if (cell == '1')
            {
                radar->boundry = true;
            }
        }
    }
}

void	diag_cell_col_tr(t_radar *radar, t_game_data *game_data)
{
    char	cell;
    // Top-right diagonal
    if ((radar->fraction_x > (1.0 - radar->collision_dist)
            && radar->fraction_y < radar->collision_dist)
        && (radar->grid_x + 1 < game_data->map->width && radar->grid_y > 0))
    {
        cell = game_data->map->grid[radar->grid_y - 1][radar->grid_x + 1];
        if (cell == '1')
        {
            radar->boundry = true;
        }
    }
}

void	diag_cell_col_tl(t_radar *radar, t_game_data *game_data)
{
    char	cell;

    // Top-left diagonal
    if ((radar->fraction_x < radar->collision_dist
            && radar->fraction_y < radar->collision_dist)
        && (radar->grid_x > 0 && radar->grid_y > 0))
    {
        cell = game_data->map->grid[radar->grid_y - 1][radar->grid_x - 1];
        if (cell == '1')
        {
            radar->boundry = true;
        }
    }
}

void	collision_wrapper(t_radar *radar, t_game_data *game_data)
{
    right_cell_col(radar, game_data);
    left_cell_col(radar, game_data);
    bottom_cell_col(radar, game_data);
    top_cell_col(radar, game_data);
    diag_cell_col(radar, game_data);
}

void calc_radar_point(t_radar *radar, t_game_data *game_data)
{
    radar->theta = convrad(radar->angle);
    radar->point_x = game_data->player->pos.x + radar->radius * cos(radar->theta);
    radar->point_y = game_data->player->pos.y + radar->radius * sin(radar->theta);
    radar->x = radar->point_x;
    radar->y = radar->point_y;
}

