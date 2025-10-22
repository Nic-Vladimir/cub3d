/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavornik <mgavornik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:20:45 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/10 12:06:50 by mgavornik        ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CUB3D_H
#define CUB3D_H

// --- Libs ---
#include "../lib/libft/inc/libft.h"
#include "../lib/mlx/mlx.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <fcntl.h>

// --- Project headers ---
#include "errors.h"
#include "raycasting.h"
#include "vectors.h"

#define DEBUG 0
#define UNASSIGNED -1

#define SCALE_FACTOR 40

#define DRAW_DISTANCE 50
#define FOV 90
#define WIDTH 1280
#define HEIGHT 720
#define PIXEL_SIZE 128
#define BLOCK_SIZE 64
#define PLAYER_SIZE 0.25

#define W 119
#define A 97
#define S 115
#define D 100
#define TURN_LEFT 65361
#define TURN_RIGHT 65363
#define TURN_SPEED 0.02
#define MOVE_SPEED 0.03

#define PI 3.14159265359f

typedef enum s_texture_id {
	TEX_NORTH = 0,
	TEX_SOUTH,
	TEX_WEST,
	TEX_EAST,
} t_texture_id;

typedef struct s_texture_path_info
{
	const char	*prefix; 
	char 		**target;
}	t_texture_path_info;

typedef struct s_texture {
    void    *img;       // MLX image handle
    int     *pixels;    // raw pixel data
    int     width;
    int     height;
	int		line_len;
	int     bpp;
	int		endian;
} t_texture;

typedef struct s_player {
	t_vec2		pos;
	t_vec2		dir;
	t_vec2		camera_plane;
	float		fov_factor;
	float		move_speed;
	float		turn_speed;
	float		size;
	bool		pos_set;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		turn_left;
	bool		turn_right;
} t_player;

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
} t_map;

typedef struct s_temp_map_node {
	struct s_temp_map_node	*prev;
	struct s_temp_map_node	*next;
	char					*line;
	int						map_y;
} t_temp_map_node;

typedef struct s_values
{
    int     line_height;
    int		draw_start;
	int		draw_end;
	int		screen_y;
	int		color;
	int		ceiling_color;
	int		floor_color;
	int		tex_id;
	int		tex_x;
	int		tex_y;
	float	shading_factor;
	float	floor_ceiling_shading_factor;
	float	dist;
	float	p;
	float	tex_step;
	float	tex_pos;
} t_values;

typedef struct s_game_data {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	t_values		*values;
	t_map			*map;
	t_temp_map_node	*tmp_map_lines;
	t_player		*player;
	char			*no_texture_path;
	char			*so_texture_path;
	char			*we_texture_path;
	char			*ea_texture_path;
	t_texture		textures[4];
	int				bpp;
	int				line_len;
	int				endian;
	int				floor_color;
	int				ceiling_color;
	int				screen_width;
	int				screen_height;
	bool			in_map;
} t_game_data;

// --- OLD ---  TODO: remove
void	init_player(t_player *player);
int		key_press_handler(int keycode, t_game_data *game_data);
int		key_release_handler(int keycode, t_game_data *game_data);
void	move_player(t_game_data *game_data);
void	print_fps(void);
int		get_fps(void);
void	exit_err(char *err, int exit_code);

// --- Parsing ---
t_ErrorCode		check_map(t_game_data *game_data);
t_ErrorCode		store_map(t_game_data *game_data);
t_ErrorCode		parse_cub_data(t_game_data *game_data, char **argv);

t_ErrorCode		parse_map_line(t_game_data *game_data, char *line, int i);
t_ErrorCode		check_map_line(t_game_data *game_data, t_temp_map_node *node);
t_ErrorCode		parse_texture_line(t_game_data *game_data, const char *line,
		int id_index, int data_index);
t_ErrorCode		parse_color_line(t_game_data *game_data, const char *line,
		int id_index, int data_index);

// --- Parsing utils ---
bool			all_textures_and_colors_assigned(t_game_data *game_data);
bool			is_number(const char *s);
bool			is_data_identifier(const char c);
t_ErrorCode		check_args(int argc, char **argv);

// --- Drawing ---
void	draw_circle(float cx, float cy, float radius, int color,
		t_game_data *game_data);
void	put_pixel(int x, int y, int color, t_game_data *game_data);
void	draw_column(t_ray *ray, t_game_data *game_data, int screen_x);

// Raycasting
void	cast_ray(t_game_data *game_data);

// --- Inits ---
t_ErrorCode		init_mlx(t_game_data *game_data);
t_ErrorCode		init_game_data(t_game_data *game_data);

// --- Utils ---
int			rgb_to_int(int rgb[3]);
float		fov_to_plane_factor(float fov_deg);
t_values	*init_values(t_values *values);
t_ErrorCode	protected_malloc(t_game_data *game_data);

#endif
