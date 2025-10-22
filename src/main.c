/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:48:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/10 12:52:25 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"
#include <stdlib.h>
#include <unistd.h>

void	draw_circle(float cx, float cy, float radius, int color,
		t_game_data *game_data)
{
	int	x;
	int	y;
	int	err;
	int	scaled_cx;
	int	scaled_cy;

	x = radius * SCALE_FACTOR;
	y = 0;
	err = 0;
	scaled_cx = cx * SCALE_FACTOR;
	scaled_cy = cy * SCALE_FACTOR;
	while (x >= y)
	{
		put_pixel(scaled_cx + x, scaled_cy + y, color, game_data);
		put_pixel(scaled_cx + y, scaled_cy + x, color, game_data);
		put_pixel(scaled_cx - y, scaled_cy + x, color, game_data);
		put_pixel(scaled_cx - x, scaled_cy + y, color, game_data);
		put_pixel(scaled_cx - x, scaled_cy - y, color, game_data);
		put_pixel(scaled_cx - y, scaled_cy - x, color, game_data);
		put_pixel(scaled_cx + y, scaled_cy - x, color, game_data);
		put_pixel(scaled_cx + x, scaled_cy - y, color, game_data);
		y++;
		if (err <= 0)
			err += 2 * y + 1;
		if (err > 0)
		{
			x--;
			err -= 2 * x + 1;
		}
	}
}

void	draw_square(int x, int y, int size, int color, t_game_data *game_data)
{
	int	i;

	i = 0;
	while (i < size)
		put_pixel(x + i++, y, color, game_data);
	i = 0;
	while (i < size)
		put_pixel(x, y + i++, color, game_data);
	i = 0;
	while (i < size)
		put_pixel(x + size, y + i++, color, game_data);
	i = 0;
	while (i < size)
		put_pixel(x + i++, y + size, color, game_data);
}

void	clear_image(t_game_data *game_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game_data);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game_data *game_data)
{
	char	**grid;
	int		color;
	int		x;
	int		y;

	grid = game_data->map->grid;
	color = 0x0000FF;
	x = 0;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == '1')
				draw_square(x * SCALE_FACTOR, y * SCALE_FACTOR, SCALE_FACTOR,
					color, game_data);
			x++;
		}
		y++;
	}
}

bool	touch_wall(float px, float py, t_game_data *game_data)
{
	int	x;
	int	y;

	x = px / BLOCK_SIZE;
	y = py / BLOCK_SIZE;
	if (game_data->map->grid[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2,
		t_game_data *game_data)
{
	t_vec2		delta;
	t_player	*p;

	delta.x = x2 - x1;
	delta.y = y2 - y1;
	p = game_data->player;
	// Project delta onto player direction using dot product
	return (vec2_dot(delta, (t_vec2){p->dir.x, p->dir.y}));
}

// float	fixed_dist(float x1, float y1, float x2, float y2,
// 		t_game_data *game_data)
// {
// 	float	delta_x;
// 	float	delta_y;
// 	float	angle;
// 	float	fixed_dist;
//
// 	delta_x = x2 - x1;
// 	delta_y = y2 - y1;
// 	angle = atan2(delta_y, delta_x) - game_data->player->angle;
// 	fixed_dist = distance(delta_x, delta_y) * cos(angle);
// 	return (fixed_dist);
// }

void	draw_line(t_player *player, t_game_data *game_data, float start_x,
		int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->pos.x;
	ray_y = player->pos.y;
	while (!touch_wall(ray_x + cos_angle * 5, ray_y + sin_angle * 5, game_data))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, game_data);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		dist = fixed_dist(player->pos.x, player->pos.y, ray_x, ray_y,
				game_data);
		height = (BLOCK_SIZE / dist) * (WIDTH / 2);
		start_y = (HEIGHT - height) / 2;
		end = start_y + height;
		while (start_y < end)
			put_pixel(i, start_y++, 255, game_data);
	}
}

void	draw_UI(t_game_data *game_data)
{
	char		buffer[32];
	static int	fps;

	fps = get_fps();
	sprintf(buffer, "FPS: %d", fps);
	printf("fps: %d\n", fps);
	mlx_string_put(game_data->mlx, game_data->win, 10, 10, 0xFFFFFF, buffer);
}

int	draw_loop(t_game_data *game_data)
{
	t_player	*player;

	// float		fraction;
	// float		start_x;
	// int			i;
	player = game_data->player;
	// printf("Direction angle in loop: %f, %f\n", game_data->player->dir.x,
	// 	game_data->player->dir.y);
	move_player(game_data);
	clear_image(game_data);
	// print_fps();
	draw_circle(player->pos.x, player->pos.y, 0.25, 0x00FF00, game_data);
	// draw_square(player->pos.x * SCALE_FACTOR, player->pos.y * SCALE_FACTOR, 1
	// 	* SCALE_FACTOR, 0x00FF00, game_data);
	draw_map(game_data);
	cast_ray(game_data);
	// if (DEBUG)
	// {
	// 	draw_square(player->pos.x, player->pos.y, 10, 0x00FF00, game_data);
	// 	draw_map(game_data);
	// }
	// else
	// 	draw_floor_ceiling(game_data);
	// fraction = PI / 3 / WIDTH;
	// start_x = player->angle - PI / 6;
	// i = 0;
	// while (i < WIDTH)
	// {
	// 	draw_line(player, game_data, start_x, i);
	// 	start_x += fraction;
	// 	i++;
	// }
	mlx_put_image_to_window(game_data->mlx, game_data->win, game_data->img, 0,
		0);
	// draw_UI(game_data);
	return (0);
}

void	fill_texture_pixels(t_texture *tex)
{
	tex->pixels = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
}

t_ErrorCode	load_textures(t_game_data *game_data)
{
	t_texture	no_texture;
	t_texture	so_texture;
	t_texture	we_texture;
	t_texture	ea_texture;

	no_texture.img = mlx_xpm_file_to_image(game_data->mlx,
			game_data->no_texture_path, &no_texture.width, &no_texture.height);
	if (!no_texture.img)
		return (ERR_INVALID_PATH);
	fill_texture_pixels(&no_texture);
	game_data->textures[TEX_NORTH] = no_texture;
	so_texture.img = mlx_xpm_file_to_image(game_data->mlx,
			game_data->so_texture_path, &so_texture.width, &so_texture.height);
	if (!so_texture.img)
		return (ERR_INVALID_PATH);
	fill_texture_pixels(&so_texture);
	game_data->textures[TEX_SOUTH] = so_texture;
	we_texture.img = mlx_xpm_file_to_image(game_data->mlx,
			game_data->we_texture_path, &we_texture.width, &we_texture.height);
	if (!we_texture.img)
		return (ERR_INVALID_PATH);
	fill_texture_pixels(&we_texture);
	game_data->textures[TEX_WEST] = we_texture;
	ea_texture.img = mlx_xpm_file_to_image(game_data->mlx,
			game_data->ea_texture_path, &ea_texture.width, &ea_texture.height);
	if (!ea_texture.img)
		return (ERR_INVALID_PATH);
	fill_texture_pixels(&ea_texture);
	game_data->textures[TEX_EAST] = ea_texture;
	return (ERR_OK);
}

static t_ErrorCode	parse_cub_file(t_game_data *game_data, int argc,
		char **argv)
{
	t_ErrorCode	err;

	(void)game_data;
	err = check_args(argc, argv);
	if (err != ERR_OK)
		return (err);
	err = parse_cub_data(game_data, argv);
	if (err != ERR_OK)
		return (err);
	err = check_map(game_data);
	if (err != ERR_OK)
		return (err);
	err = store_map(game_data);
	if (err != ERR_OK)
		return (err);
	// printf("Player coords: x=%f, y=%f\n", game_data->player->pos.x,
	// 	game_data->player->pos.y);
	return (ERR_OK);
}

int	main(int argc, char **argv)
{
	t_game_data	*game_data;
	t_ErrorCode	err;

	game_data = malloc(sizeof(t_game_data));
	ft_memset(game_data, 0, sizeof(t_game_data));
	if (!game_data)
		error_exit(game_data, ERR_ALLOC);
	err = init_game_data(game_data);
	if (err != ERR_OK)
		error_exit(game_data, err);
	err = parse_cub_file(game_data, argc, argv);
	if (err != ERR_OK)
		error_exit(game_data, err);
	err = init_mlx(game_data);
	if (err != ERR_OK)
		error_exit(game_data, err);
	err = load_textures(game_data);
	if (err != ERR_OK)
		return (err);
	mlx_loop_hook(game_data->mlx, draw_loop, game_data);
	mlx_loop(game_data->mlx);
	return (0);
}
