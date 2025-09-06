/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:48:57 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/06 20:20:36 by vnicoles         ###   ########.fr       */
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
	init_player(&game_data->player);
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
	angle = atan2(delta_y, delta_x) - game_data->player.angle;
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

	player = &game_data->player;
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

static t_ErrorCode	check_args(int argc, char **argv)
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

bool	all_textures_and_color_assigned(t_game_data *game_data)
{
	if (game_data->no_texture != NULL && game_data->so_texture != NULL
		&& game_data->ea_texture != NULL && game_data->we_texture != NULL
		&& game_data->floor_color_assigned && game_data->ceiling_color_assigned)
		return (true);
	return (false);
}

// TODO: add whitespace skipping
t_ErrorCode	parse_texture_line(t_game_data *game_data, const char *line,
		int id_index, int data_index)
{
	int				j;
	t_texture_id	map[5];

	map[0] = (t_texture_id){"NO ", &game_data->no_texture};
	map[1] = (t_texture_id){"SO ", &game_data->so_texture};
	map[2] = (t_texture_id){"WE ", &game_data->we_texture};
	map[3] = (t_texture_id){"EA ", &game_data->ea_texture};
	map[4] = (t_texture_id){NULL, NULL};
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

t_ErrorCode	assign_color(t_game_data *game_data, int r, int g, int b, char c)
{
	if (c == 'F')
	{
		game_data->floor_color[0] = r;
		game_data->floor_color[1] = g;
		game_data->floor_color[2] = b;
		game_data->floor_color_assigned = true;
	}
	else if (c == 'C')
	{
		game_data->floor_color[0] = r;
		game_data->floor_color[1] = g;
		game_data->floor_color[2] = b;
		game_data->ceiling_color_assigned = true;
	}
	else
		return (ERR_INVALID_COLORS);
	return (ERR_OK);
}

t_ErrorCode	parse_color_line(t_game_data *game_data, const char *line,
		int id_index, int data_index)
{
	char	*values;
	char	**parts;

	int r, g, b;
	values = (char *)(line + data_index);
	parts = ft_split(values, ',');
	if (!parts)
		return (ERR_ALLOC);
	// ft_printf("parts[0]=%s, parts[1]=%s, parts[2]=%s, parts[3]=%s\n",
	// parts[0],
	// parts[1], parts[2], parts[3]);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3] || !is_number(parts[0])
		|| !is_number(parts[1]) || !is_number(parts[2]))
		return (ERR_INVALID_COLORS);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	ft_free_split(parts);
	// ft_printf("r = %d, g = %d, b = %d\n", r, g, b);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ERR_INVALID_COLORS);
	if (ft_strncmp(line + id_index, "F ", 2) == 0
		&& game_data->floor_color_assigned == false)
		return (assign_color(game_data, r, g, b, 'F'));
	else if (ft_strncmp(line + id_index, "C ", 2) == 0
		&& game_data->ceiling_color_assigned == false)
		return (assign_color(game_data, r, g, b, 'C'));
	return (ERR_DUP_COLOR);
}

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

bool	is_data_identifier(const char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F' || c == 'C')
		return (true);
	return (false);
}

t_ErrorCode	store_tmp_line(t_game_data *game_data, const char *line)
{
	t_temp_map_node	*new_node;
	t_temp_map_node	*prev_node;

	new_node = malloc(sizeof(t_temp_map_node));
	if (!new_node)
		return (ERR_ALLOC);
	new_node->line = ft_strdup(line);
	if (!new_node->line)
		return (ERR_ALLOC);
	new_node->next = NULL;
	if (!game_data->tmp_map_lines)
	{
		game_data->tmp_map_lines = new_node;
		game_data->tmp_map_lines->prev = NULL;
	}
	else
	{
		prev_node = game_data->tmp_map_lines;
		while (prev_node->next)
			prev_node = prev_node->next;
		prev_node->next = new_node;
		new_node->prev = prev_node;
	}
	return (ERR_OK);
}

t_ErrorCode	parse_map_line(t_game_data *game_data, const char *line, int i)
{
	t_ErrorCode	err;

	(void)i;
	if (game_data->in_map == false)
		game_data->in_map = true;
	err = store_tmp_line(game_data, line);
	if (err != ERR_OK)
		return (err);
	game_data->map->height++;
	return (ERR_OK);
}

t_ErrorCode	parse_cub_line(t_game_data *game_data, const char *line)
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
	else if (all_textures_and_color_assigned(game_data))
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
	static int	i = 0;

	path = argv[1];
	fd = open(path, O_RDONLY);
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		ft_printf("row: %d\n", i++);
		err = parse_cub_line(game_data, line);
		free(line);
		if (err != ERR_OK)
		{
			close(fd);
			return (err);
		}
	}
	close(fd);
	return (ERR_OK);
}

t_ErrorCode	check_map(void)
{
	// TODO: check map format
	return (ERR_OK);
}

// TODO: finish cub file parsing
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
	err = check_map();
	if (err != ERR_OK)
		return (err);
	return (ERR_OK);
}

void	init_data(t_game_data *game_data)
{
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
	game_data->map->height = 0;
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
