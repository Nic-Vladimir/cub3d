/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:48:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 15:00:23 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/cub3d.h"
#include "../inc/utils.h"
#include <stdlib.h>
#include <unistd.h>

void dda_mod(float *radius, int *color, t_game_data *game_data)
{
	(void)game_data;
	*radius = 0.1f;
	*color = 0x00FF00;
}

void radar_mod(float *radius, int *color, t_game_data *game_data)
{
	*radius = game_data->radar->dot_size;
	*color = game_data->radar->color;
}

void player_mod(float *radius, int *color, t_game_data *game_data)
{
	(void)game_data;
	*radius = 0.25f;
	*color = 0xFF0000;
}
void	draw_circle(float cx, float cy, t_circ_mod mod,
		t_game_data *game_data)
{
	t_circle	*circle;

	circle = init_circle();
	if(mod)
		mod(&circle->radius, &circle->color, game_data);
	circle->angle_step = 10.0f;
	while (circle->angle < 360.0f)
	{
		circle->theta = convrad(circle->angle);
		circle->point_x = cx + circle->radius * cos(circle->theta);
		circle->point_y = cy + circle->radius * sin(circle->theta);
		put_pixel(circle->point_x * SCALE_FACTOR, circle->point_y
			* SCALE_FACTOR, circle->color, game_data);
		circle->angle += circle->angle_step;
	}
	free(circle);
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

	player = game_data->player;
	move_player(game_data);
	clear_image(game_data);
	draw_circle(player->pos.x, player->pos.y, player_mod, game_data);
	draw_map(game_data);
	cast_ray(game_data);
	radar_loop(game_data);
	mlx_put_image_to_window(game_data->mlx, game_data->win, game_data->img, 0,
		0);
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

	// Validate texture paths
	if (!game_data->no_texture_path || !game_data->so_texture_path
		|| !game_data->we_texture_path || !game_data->ea_texture_path)
		return (ERR_INVALID_PATH);
	// Initialize texture data
	ft_memset(&no_texture, 0, sizeof(t_texture));
	ft_memset(&so_texture, 0, sizeof(t_texture));
	ft_memset(&we_texture, 0, sizeof(t_texture));
	ft_memset(&ea_texture, 0, sizeof(t_texture));
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
	return (ERR_OK);
}

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
	game_data->ray = NULL;
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
void	init_radar_zero(t_radar *radar)
{
	if (!radar)
		return ;
	ft_memset(radar, 0, sizeof(t_radar));
}

void	init_radar_data(t_game_data *game_data)
{
	if (!game_data)
		return ;
	init_radar_zero(game_data->radar);
	game_data->radar->color = 0xFF0000;
	game_data->radar->angle_step = 15;
	game_data->radar->radius = 0.15;
	game_data->radar->dot_size = 0.02;
	game_data->radar->collision_dist = 0.2;
}
t_ErrorCode	protected_malloc(t_game_data *game_data)
{
	if (!game_data)
		return (ERR_ALLOC);
	game_data->map = malloc(sizeof(t_map));
	if (game_data->map == NULL)
		return (ERR_ALLOC);
	ft_memset(game_data->map, 0, sizeof(t_map));
	game_data->player = malloc(sizeof(t_player));
	if (game_data->player == NULL)
		return (ERR_ALLOC);
	ft_memset(game_data->player, 0, sizeof(t_player));
	game_data->radar = malloc(sizeof(t_radar));
	if (game_data->radar == NULL)
		return (ERR_ALLOC);
	ft_memset(game_data->radar, 0, sizeof(t_radar));
	if (game_data->ray == NULL)
		return (ERR_ALLOC);
	ft_memset(game_data->ray, 0, sizeof(t_ray));
	return (ERR_OK);
}
t_circle	*init_circle(void)
{
	t_circle	*circle;

	circle = malloc(sizeof(t_circle));
	if (!circle)
		return (NULL);
	ft_memset(circle, 0, sizeof(t_circle));
	return (circle);
}

t_ErrorCode	init_game_data(t_game_data *game_data)
{
	if (!game_data)
		return (ERR_ALLOC);
	protected_malloc(game_data);
	game_data->values = init_values(game_data->values);
	init_radar_data(game_data);
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

t_ErrorCode	init_mlx(t_game_data *game_data)
{
	game_data->mlx = mlx_init();
	game_data->win = mlx_new_window(game_data->mlx, WIDTH, HEIGHT, "Cub3D");
	game_data->img = mlx_new_image(game_data->mlx, WIDTH, HEIGHT);
	game_data->addr = mlx_get_data_addr(game_data->img, &game_data->bpp,
			&game_data->line_len, &game_data->endian);
	mlx_hook(game_data->win, KeyPress, KeyPressMask, key_press_handler,
		game_data);
	mlx_hook(game_data->win, KeyRelease, KeyReleaseMask, key_release_handler,
		game_data);
	mlx_hook(game_data->win, 17, 0, clean_exit, NULL);
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
