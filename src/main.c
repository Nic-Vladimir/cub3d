/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:48:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/09 16:05:02 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>
#include <unistd.h>

// void	check_arguments(int argc, char **argv)
//{
//	char	*ext;
//	int		len;
//
//	len = 0;
//	ext = NULL;
//	if (argc != 2)
//		error_exit("Error\nUsage: ./cub3d <map->cub>", NULL);
//	len = ft_strlen(argv[1]);
//	ext = argv[1] + len - 4;
//	if (len < 4 || ft_strncmp(ext, ".cub", 4) != 0)
//		error_exit("Error\nMap file must have .cub extension", NULL);
//}

static int	rbg_to_color(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	put_pixel(int x, int y, int color, t_game_data *game_data)
{
	int	offset;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	offset = (game_data->size_line * y) + (x * (game_data->bpp / 8));
	*((unsigned int *)(offset + game_data->data)) = color;
}

static void	draw_floor_ceiling(t_game_data *game_data)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = rbg_to_color(game_data->ceiling_color);
	floor_color = rbg_to_color(game_data->floor_color);
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, ceiling_color, game_data);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, floor_color, game_data);
			x++;
		}
		y++;
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

char	**get_map(void)
{
	char	**grid;

	grid = malloc(sizeof(char *) * 11);
	grid[0] = "111111111111";
	grid[1] = "100000000001";
	grid[2] = "100000000001";
	grid[3] = "100100000001";
	grid[4] = "100001000001";
	grid[5] = "100000000001";
	grid[6] = "100000000001";
	grid[7] = "100010000001";
	grid[8] = "100010000001";
	grid[9] = "111111111111";
	grid[10] = NULL;
	return (grid);
}

void	init_game_data(t_game_data *game_data)
{
	init_player(game_data->player);
	game_data->mlx = mlx_init();
	game_data->win = mlx_new_window(game_data->mlx, WIDTH, HEIGHT, "cub3d");
	game_data->img = mlx_new_image(game_data->mlx, WIDTH, HEIGHT);
	game_data->data = mlx_get_data_addr(game_data->img, &game_data->bpp,
			&game_data->size_line, &game_data->endian);
	game_data->map->grid = get_map();
	game_data->floor_color[0] = 50;    // R
	game_data->floor_color[1] = 50;    // G
	game_data->floor_color[2] = 50;    // B (gray)
	game_data->ceiling_color[0] = 20;  // R
	game_data->ceiling_color[1] = 20;  // G
	game_data->ceiling_color[2] = 100; // B (blue)
	mlx_put_image_to_window(game_data->mlx, game_data->win, game_data->img, 0,
		0);
}

void	draw_map(t_game_data *game_data)
{
	char	**grid;
	int		color;

	grid = game_data->map->grid;
	color = 0x0000FF;
	for (int y = 0; grid[y]; y++)
		for (int x = 0; grid[y][x]; x++)
			if (grid[y][x] == '1')
				draw_square(x * 16, y * 16, 16, color, game_data);
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
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fixed_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game_data->player->angle;
	fixed_dist = distance(delta_x, delta_y) * cos(angle);
	return (fixed_dist);
}

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
	ray_x = player->x;
	ray_y = player->y;
	while (!touch_wall(ray_x + cos_angle * 5, ray_y + sin_angle * 5, game_data))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, game_data);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game_data);
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
	float		fraction;
	float		start_x;
	int			i;

	player = game_data->player;
	move_player(game_data);
	clear_image(game_data);
	print_fps();
	if (DEBUG)
	{
		draw_square(player->x, player->y, 10, 0x00FF00, game_data);
		draw_map(game_data);
	}
	else
		draw_floor_ceiling(game_data);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game_data, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game_data->mlx, game_data->win, game_data->img, 0,
		0);
	// draw_UI(game_data);
	return (0);
}

static t_ErrorCode	parse_cub_file(int argc, char **argv,
		t_game_data *game_data)
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
	printf("Player coords: x=%f, y=%f\n", game_data->player->x,
		game_data->player->y);
	return (ERR_OK);
}

void	init_data(t_game_data *game_data)
{
	game_data->map = malloc(sizeof(t_map));
	game_data->player = malloc(sizeof(t_player));
	game_data->player->pos_set = false;
	game_data->tmp_map_lines = NULL;
	game_data->mlx = NULL;
	game_data->win = NULL;
	game_data->img = NULL;
	game_data->map->grid = NULL;
	game_data->no_texture = NULL;
	game_data->so_texture = NULL;
	game_data->we_texture = NULL;
	game_data->ea_texture = NULL;
	game_data->floor_color_assigned = false;
	game_data->ceiling_color_assigned = false;
	game_data->in_map = false;
	game_data->map->height = -1;
	game_data->map->width = 0;
}

int	main(int argc, char **argv)
{
	t_game_data	game_data;
	t_ErrorCode	err;

	init_data(&game_data);
	err = parse_cub_file(argc, argv, &game_data);
	if (err != ERR_OK)
		error_exit(&game_data, err);
	init_game_data(&game_data);
	mlx_hook(game_data.win, KeyPress, KeyPressMask, key_press_handler,
		&game_data);
	mlx_hook(game_data.win, KeyRelease, KeyReleaseMask, key_release_handler,
		&game_data);
	mlx_loop_hook(game_data.mlx, draw_loop, &game_data);
	mlx_loop(game_data.mlx);
	return (0);
}
