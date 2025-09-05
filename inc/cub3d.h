/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:20:45 by vnicoles          #+#    #+#             */
/*   Updated: 2025/09/05 11:43:43 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


#define DEBUG 0

#define WIDTH 1280
#define HEIGHT 720
#define PIXEL_SIZE 128
#define BLOCK_SIZE 64
#define PLAYER_SIZE 20

#define W 119
#define A 97
#define S 115
#define D 100
#define TURN_LEFT 65361
#define TURN_RIGHT 65363
#define TURN_SPEED 0.02
#define MOVE_SPEED 0.3

#define PI 3.14159265359

typedef struct s_texture_id
{
	const char	*prefix;
	char 		**target;
}	t_texture_id;

typedef struct s_vector {
	double	x;
	double	y;
} t_vector;

typedef struct s_player {
	float		x;
	float		y;
	float		angle;

	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		turn_left;
	bool		turn_right;
	float		move_speed;
	float		turn_speed;
	float		size;
} t_player;

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
} t_map;

typedef struct s_texture {
	void	*img;
	int		width;
	int		height;
	char	*data;
} t_texture;

typedef struct s_game_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;

	t_map		map;
	t_player	player;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	bool		floor_color_assigned;
	bool		ceiling_color_assigned;
	int			screen_width;
	int			screen_height;
} t_game_data;

void	init_player(t_player *player);
int		key_press_handler(int keycode, t_game_data *game_data);
int		key_release_handler(int keycode, t_game_data *game_data);
void	move_player(t_game_data *game_data);
void	print_fps(void);
int		get_fps(void);
void	exit_err(char *err, int exit_code);

#endif
