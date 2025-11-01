# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 18:29:20 by vnicoles          #+#    #+#              #
#    Updated: 2025/11/01 21:59:27 by vnicoles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Colors ---
PURPLE	= \033[38;5;141m
GREEN	= \033[38;5;46m
RED		= \033[0;31m
GREY	= \033[38;5;240m
RESET	= \033[0m
BOLD	= \033[1m
YELLOW	= \033[33m
CLEAR	= \r\033[K

# --- Vars ---
NAME		= cub3D
NAME_B		= cub3D_bonus
CC			= cc -std=gnu11 -g
CFLAGS		= -Wall -Wextra -Werror -MMD -MP

# --- Paths ---
MLX_REPO	= https://github.com/gamagamagama/minilibx-linux.git
MLX_DIR		= $(LIB_DIR)/mlx

SRC_DIR		= src
LIB_DIR		= lib
LIBFT_DIR	= $(LIB_DIR)/libft
OBJ_DIR		= obj
BOBJ_DIR	= obj_bonus
INC_DIR		= inc
HEADERS		= $(shell find $(INC_DIR) -name "*.h")
DEPS		= $(OBJ:.o=.d)
BDEPS		= $(BOBJ:.o=.d)

INC			= -I inc/ -I lib/libft/inc/ -I lib/mlx/

# --- Source Files ---
SRC			= src/main.c \
			  src/base/funcs.c \
			  src/init.c \
			  src/init/init_data0.c\
			  src/init/init_radar_data.c\
			  src/utils.c \
			  src/draw/shapes.c \
			  src/radar/radar_utils.c \
			  src/radar/radar_mod.c \
			  src/radar/radar_col_side.c \
			  src/radar/radar_col_diag.c \
			  src/radar/radar_col_proc.c \
			  src/parsing/cub_data.c \
			  src/parsing/colors.c \
			  src/parsing/textures.c \
			  src/parsing/map_line.c \
			  src/parsing/utils.c \
			  src/parsing/map_validation/map.c \
			  src/parsing/map_validation/player_direct.c \
			  src/parsing/map_validation/map_line.c \
			  src/parsing/map_validation/map_store.c \
			  src/raycasting/ray_init.c \
			  src/raycasting/cast_ray.c \
			  src/render/draw_shade.c \
			  src/render/draw_column.c \
			  src/render/helpers.c \
			  src/player.c \
			  src/player_utils.c \
			  src/utils/fps_counter.c \
			  src/utils/vectors.c \
			  src/exit/free.c \
			  src/exit/exit.c

BSRC		= src/main.c \
			  src/bonus/funcs_bonus.c \
			  src/bonus/minimap_utils.c \
			  src/init.c \
			  src/init/init_data0.c\
			  src/init/init_radar_data.c\
			  src/utils.c \
			  src/draw/shapes.c \
			  src/radar/radar_utils.c \
			  src/radar/radar_mod.c \
			  src/radar/radar_col_side.c \
			  src/radar/radar_col_diag.c \
			  src/radar/radar_col_proc.c \
			  src/parsing/cub_data.c \
			  src/parsing/colors.c \
			  src/parsing/textures.c \
			  src/parsing/map_line.c \
			  src/parsing/utils.c \
			  src/parsing/map_validation/map.c \
			  src/parsing/map_validation/player_direct.c \
			  src/parsing/map_validation/map_line.c \
			  src/parsing/map_validation/map_store.c \
			  src/raycasting/ray_init.c \
			  src/raycasting/cast_ray.c \
			  src/render/draw_shade.c \
			  src/render/draw_column.c \
			  src/render/helpers.c \
			  src/player.c \
			  src/player_utils.c \
			  src/utils/fps_counter.c \
			  src/utils/vectors.c \
			  src/exit/free.c \
			  src/exit/exit.c

OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BOBJ		= $(addprefix $(BOBJ_DIR)/, $(BSRC:.c=.o))

# Alternative approaches (commented out):
# SRC := $(shell find $(SRC_DIR) -name "*.c")
# OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
# SRC := $(wildcard $(SRC_DIR)/**/*.c)
# OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# --- Libs ---
LIBFT		= $(LIB_DIR)/libft/libft.a
MLX			= $(LIB_DIR)/mlx/libmlx_Linux.a
LIBS		= $(LIBFT) $(MLX) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# --- Progress bar ---
TOTAL_FILES     = $(words $(SRC))
TOTAL_BFILES    = $(words $(BSRC))
CURR_FILE       = 0

define update_progress
	@$(eval CURR_FILE := $(shell echo "$(CURR_FILE) + 1" | bc))
	@$(eval PERCENT := $(shell echo "scale=0; $(CURR_FILE) * 100 / $1" | bc))
	@$(eval FILLED := $(shell echo "scale=0; $(PERCENT) * 20 / 100" | bc))
	@$(eval EMPTY := $(shell echo "scale=0; 20 - $(FILLED)" | bc))
	@printf "\r\033[K"
	@printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)$(NAME)$(RESET)]: \tCompiling... ["
	@if [ $(FILLED) -gt 0 ]; then printf "%*s" $(FILLED) "" | tr ' ' '='; fi
	@if [ $(EMPTY) -gt 0 ]; then printf "%*s" $(EMPTY) "" | tr ' ' '.'; fi
	@printf "] %3d%%" $(PERCENT)
	@printf " %s" $(notdir $<)
endef

# --- Rules ---
all: clone $(NAME)

bonus: clone $(NAME_B)

clone:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)MLX$(RESET)]: \t$(GREEN)Cloning MLX into $(MLX_DIR)...$(RESET)\n"; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	else \
		printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)MLX$(RESET)]: \t$(YELLOW)MLX already cloned.$(RESET)\n"; \
	fi


$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@printf "\n$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)$(NAME)$(RESET)]: \tLinking...\n"
	@$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME) $(LIBS)
	@printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)$(NAME)$(RESET)]: \t$(GREEN)Build complete!$(RESET)\n"

$(NAME_B): $(LIBFT) $(MLX) $(BOBJ)
	@printf "\n$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)$(NAME_B)$(RESET)]: \tLinking...\n"
	@$(CC) $(CFLAGS) $(BOBJ) $(INC) -o $(NAME_B) $(LIBS)
	@printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)$(NAME_B)$(RESET)]: \t$(GREEN)Bonus build complete!$(RESET)\n"

$(LIBFT):
	@printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)libft$(RESET)]: \tBuilding libft...\n"
	@make -C $(LIBFT_DIR)

$(MLX): clone
	@printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)MLX$(RESET)]: \tBuilding MLX...\n"
	@make -C $(MLX_DIR)

# ---- Normal comp ----
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	$(call update_progress,$(TOTAL_FILES))

# ---- Bonus comp ----
$(BOBJ_DIR):
	@mkdir -p $(BOBJ_DIR)
	@mkdir -p $(BOBJ_DIR)/$(SRC_DIR)

$(BOBJ_DIR)/%.o: %.c | $(BOBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	$(call update_progress,$(TOTAL_BFILES))

-include $(DEPS)
-include $(BDEPS)

clean:
	@rm -rf $(OBJ_DIR) $(BOBJ_DIR)
	@make clean -C $(LIBFT_DIR) 2>/dev/null || true
	@make clean -C $(MLX_DIR) 2>/dev/null || true
	@printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)$(NAME)$(RESET)]: \tCleaned object files\n"

fclean: clean
	@rm -f $(NAME) $(NAME_B)
	@make fclean -C $(LIBFT_DIR) 2>/dev/null || true
	@if [ -d "$(MLX_DIR)" ]; then \
		printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)MLX$(RESET)]: \t$(YELLOW)Removing cloned MLX repo...$(RESET)\n"; \
		rm -rf $(MLX_DIR); \
	else \
		printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)MLX$(RESET)]: \t$(GREEN)MLX not cloned.$(RESET)\n"; \
	fi
	@printf "$(GREEN)»$(RESET) [$(PURPLE)$(BOLD)$(NAME)$(RESET)]: \t$(GREEN)Full clean$(RESET)\n"


re: fclean all

.PHONY: all bonus clean fclean re
