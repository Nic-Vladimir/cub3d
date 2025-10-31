/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:20:45 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 21:24:58 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// --- Libs ---
# include "../lib/libft/inc/libft.h"
# include "../lib/mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// --- Project headers ---
# include "errors.h"
# include "raycasting.h"
# include "utils.h"
# include "values.h"
# include "vectors.h"

# define DEBUG 0
# define UNASSIGNED -1

# define SCALE_FACTOR 40

# define DRAW_DISTANCE 50
# define FOV 90
# define WIDTH 1280
# define HEIGHT 720
# define PIXEL_SIZE 128
# define BLOCK_SIZE 64
# define PLAYER_SIZE 20

# define W 119
# define A 97
# define S 115
# define D 100
# define TURN_LEFT 65361
# define TURN_RIGHT 65363
# define TURN_SPEED 0.02
# define MOVE_SPEED 0.03

# define PI 3.14159265359f

typedef enum s_texture_id
{
	TEX_NORTH = 0,
	TEX_SOUTH,
	TEX_WEST,
	TEX_EAST,
}							t_texture_id;

typedef struct s_texture_path_info
{
	const char				*prefix;
	char					**target;
}							t_texture_path_info;

typedef struct s_texture
{
	void					*img;
	int						*pixels;
	int						width;
	int						height;
	int						line_len;
	int						bpp;
	int						endian;
}							t_texture;

typedef struct s_radar
{
	int						grid_x;
	int						grid_y;
	int						color;
	float					angle;
	float					radius;
	float					angle_step;
	float					dot_size;
	float					theta;
	float					point_x;
	float					point_y;
	float					fraction_x;
	float					fraction_y;
	float					x;
	float					y;
	float					collision_dist;
	bool					boundry;
}							t_radar;

typedef struct s_player
{
	t_vec2					pos;
	t_vec2					dir;
	t_vec2					camera_plane;
	float					radar;
	float					fov_factor;
	float					move_speed;
	float					turn_speed;
	float					size;
	float					last_x;
	float					last_y;
	bool					pos_set;
	bool					key_up;
	bool					key_down;
	bool					key_left;
	bool					key_right;
	bool					turn_left;
	bool					turn_right;
	bool					move;
}							t_player;

typedef struct s_map
{
	char					**grid;
	int						width;
	int						height;
}							t_map;

typedef struct s_circle
{
	int						color;
	float					radius;
	float					angle;
	float					theta;
	float					point_x;
	float					point_y;
	float					angle_step;
}							t_circle;

typedef struct s_temp_map_node
{
	struct s_temp_map_node	*prev;
	struct s_temp_map_node	*next;
	char					*line;
	int						map_y;
}							t_temp_map_node;

typedef struct s_color
{
	int						r;
	int						g;
	int						b;
}							t_color;

typedef struct s_line
{
	float					cos_angle;
	float					sin_angle;
	float					ray_x;
	float					ray_y;
	float					dist;
	float					height;
	int						start_y;
	int						end;
}							t_line;

typedef struct s_game_data
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*addr;
	t_radar					*radar;
	t_values				*values;
	t_map					*map;
	t_temp_map_node			*tmp_map_lines;
	t_player				*player;
	t_ray					*ray;
	t_circle				*circle;
	char					*no_texture_path;
	char					*so_texture_path;
	char					*we_texture_path;
	char					*ea_texture_path;
	t_texture				textures[4];
	int						bpp;
	int						line_len;
	int						endian;
	int						floor_color;
	int						ceiling_color;
	int						screen_width;
	int						screen_height;
	int						color;
	bool					in_map;
}							t_game_data;

typedef void				(*t_circ_mod)(float *radius, int *color,
					t_game_data *game_data);

//player

void						init_player(t_player *player);

int							key_press_handler(int keycode,
								t_game_data *game_data);
void						move_player(t_game_data *game_data);
void						radar_player(t_game_data *game_data, float new_x,
								float new_y);
void						rotate_player(t_game_data *game_data,
								float rot_speed);
int							key_release_handler(int keycode,
								t_game_data *game_data);

// --- Init ---
void						init_line(t_line *line);
void						init_tex_data(t_game_data *game_data);
void						init_zero_data(t_game_data *game_data);
t_circle					*init_circle(void);
void						init_radar_data(t_game_data *game_data);
void						init_radar_zero(t_radar *radar);
void						init_unasigned_data(t_game_data *game_data);
void						init_null_data(t_game_data *game_data);
t_ErrorCode					init_mlx(t_game_data *game_data);
t_ErrorCode					init_game_data(t_game_data *game_data);
t_ErrorCode					protected_malloc(t_game_data *game_data);

// --- Parsing ---
t_ErrorCode					check_map(t_game_data *game_data);
t_ErrorCode					store_map(t_game_data *game_data);
t_ErrorCode					parse_cub_data(t_game_data *game_data, char **argv);

t_ErrorCode					parse_map_line(t_game_data *game_data, char *line,
								int i);
t_ErrorCode					check_map_line(t_game_data *game_data,
								t_temp_map_node *node);
t_ErrorCode					parse_texture_line(t_game_data *game_data,
								const char *line, int id_index, int data_index);
t_ErrorCode					parse_color_line(t_game_data *game_data,
								const char *line, int id_index, int data_index);
void						set_player_dir_ns(t_player *player, char dir);
void						set_player_dir_ew(t_player *player, char dir);
void						set_color(t_color *color, char **parts);
t_ErrorCode					pre_check(char **parts);

// --- Parsing utils ---
bool						all_textures_and_colors_assigned(t_game_data *game_data);
bool						is_number(const char *s);
bool						is_data_identifier(const char c);
t_ErrorCode					check_args(int argc, char **argv);

// --- Drawing ---
void						dda_mod(float *radius, int *color,
								t_game_data *game_data);
void						player_mod(float *radius, int *color,
								t_game_data *game_data);
void						radar_mod(float *radius, int *color,
								t_game_data *game_data);

void						draw_circle(float cx, float cy, t_circ_mod mod,
								t_game_data *game_data);

void						put_pixel(int x, int y, int color,
								t_game_data *game_data);
void						draw_column(t_ray *ray, t_game_data *game_data,
								int screen_x);
void						draw_shade(t_game_data *game_data, int screen_x,
								float posZ);
void						draw_end(t_game_data *game_data, int screen_x);
void						draw_start(t_game_data *game_data, int screen_x,
								float posZ);
void						first_computation(t_ray *ray,
								t_game_data *game_data);
float						calculate_shading(float dist);
int							shade_color(int color, float shading_factor);
t_texture_id				get_wall_texture(t_ray *ray);
int							get_texture_x(t_ray *ray, t_game_data *game_data,
								int tex_id);
t_values					*init_values(t_values *values);

int							draw_loop(t_game_data *game_data);
void						draw_line(t_player *player, t_game_data *game_data,
								float start_x, int i);
void						draw_map(t_game_data *game_data);
void						draw_square(int x, int y, int size,
								t_game_data *game_data);

// Raycasting
void						cast_ray(t_game_data *game_data);
void						init_ray_tonull(t_ray *ray);
void						compute_perp_dist(t_ray *ray);

// --- Utils ---
int							rgb_to_int(int rgb[3]);
float						fov_to_plane_factor(float fov_deg);
float						distance(float x, float y);
bool						touch_wall(float px, float py,
								t_game_data *game_data);
void						clear_image(t_game_data *game_data);

// ---wtf_utils --
void						fill_texture_pixels(t_texture *tex);
float	fixed_dist(float x1, float y1, float x2, float y2,
					t_game_data *game_data); // TOO MANY ARGS
float						distance(float x, float y);
bool						touch_wall(float px, float py,
								t_game_data *game_data);
void						clear_image(t_game_data *game_data);

// --- Radar ---
void						diag_cell_col_br(t_radar *radar,
								t_game_data *game_data);
void						diag_cell_col_bl(t_radar *radar,
								t_game_data *game_data);
void						diag_cell_col_tr(t_radar *radar,
								t_game_data *game_data);
void						diag_cell_col_tl(t_radar *radar,
								t_game_data *game_data);
void						radar_loop(t_game_data *game_data);
bool						process_radar_point(t_radar *radar,
								t_game_data *game_data, bool player_move);
bool						validate_radar_data(t_game_data *game_data);
void						collision_wrapper(t_radar *radar,
								t_game_data *game_data);
void						diag_cell_col(t_radar *radar,
								t_game_data *game_data);
void						top_cell_col(t_radar *radar,
								t_game_data *game_data);
void						bottom_cell_col(t_radar *radar,
								t_game_data *game_data);
void						left_cell_col(t_radar *radar,
								t_game_data *game_data);
void						right_cell_col(t_radar *radar,
								t_game_data *game_data);
void						calc_radar_point(t_radar *radar,
								t_game_data *game_data);
float						convrad(float ang);

// --- Clean ---
void						free_image_tex(t_game_data *game_data);
void						free_other_structs(t_game_data *game_data);
void						free_resources(t_game_data *game_data);
int							clean_exit(t_game_data *game_data);
void						error_exit(t_game_data *game_data, t_ErrorCode err);
void						free_map_data(t_game_data *game_data);

//=========================[DONT KNOW]==========================================

// --- Vec2 Utils ---utils/vectors.c
t_vec2						vec2_add(t_vec2 a, t_vec2 b);
t_vec2						vec2_sub(t_vec2 a, t_vec2 b);
t_vec2						vec2_scale(t_vec2 v, float scale);
float						vec2_dot(t_vec2 a, t_vec2 b);
//------------------------------------------

//--- fps --- utils/fps_counter.c
int							get_fps(void);
void						print_fps(void);
//------------------------------------------

//--- exit --- utils/exit_err.c
void						exit_err(char *err, int exit_code);

//==============================================================================

#endif
