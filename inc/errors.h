/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:08:48 by vnicoles          #+#    #+#             */
/*   Updated: 2025/10/31 21:01:46 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// --- Colors ---
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

typedef enum e_error_code
{
	ERR_OK = 0,
	ERR_USAGE,
	ERR_INVALID_FILENAME,
	ERR_INVALID_PATH,
	ERR_INVALID_ORDER,
	ERR_DUP_TEXTURE,
	ERR_UNKNOWN_TEXTURE_ID,
	ERR_INVALID_COLORS,
	ERR_DUP_COLOR,
	ERR_ALLOC,
	ERR_INVALID_DATA_FORMAT,
	ERR_INVALID_MAP_CHARACTER,
	ERR_INVALID_MAP_FORMAT,
	ERR_DUP_PLAYER_POS,
	ERR_COUNT
}							t_ErrorCode;

typedef struct s_game_data	t_game_data;

void						error_exit(t_game_data *game_data,
								t_ErrorCode code);
int							clean_exit(t_game_data *game_data);

#endif
