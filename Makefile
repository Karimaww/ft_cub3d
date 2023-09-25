CC			= cc
NAME		= cub3D
NAME_BONUS	= cub3D_bonus
UNAME 		:= $(shell uname)

RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
PURPLE		= \033[0;35m
NC			= \033[0m

SOURCES_DISPLAY		=	draw_back.c		\
						draw_cub.c		\
						draw_stripe.c	\
						draw_wall.c		\
						init_cub.c		\
						init_rot.c		\
						init_textures.c	\
						move.c			\
						rotate.c		\
						handle.c		\
						game_loop.c		\

SOURCES_PARSING 	=	parse.c			\
						parse_params.c	\
						main.c			\

SOURCES_UTILS 		=	lst_utils.c		\
						map_utils.c		\
						map_check.c		\
						map_check2.c	\
						mlx_actions.c	\
						mlx_utils.c		\


SOURCES_DISPLAY_BONUS 	= 	draw_back_bonus.c		\
							draw_cub_bonus.c		\
							draw_line_bonus.c		\
							draw_sprite_bonus.c	\
							draw_stripe_bonus.c	\
							draw_wall_bonus.c		\
							init_cub_bonus.c		\
							init_rot_bonus.c		\
							init_sprite_bonus.c 	\
							init_textures_bonus.c	\
							move_bonus.c			\
							pos_sprite_bonus.c	\
							rotate_bonus.c		\
							handle_bonus.c		\
							draw_map_bonus.c		\
							game_loop_bonus.c		\
							
SOURCES_PARSING_BONUS 	= 	parse_bonus.c			\
							parse_params_bonus.c	\
							main_bonus.c			\

SOURCES_UTILS_BONUS		= 	lst_utils_bonus.c		\
							map_utils_bonus.c		\
							map_check_bonus.c		\
							map_check2_bonus.c	\
							mlx_actions_bonus.c	\
							mlx_utils_bonus.c		\

LIBFT		= libft
MLX			= mlx

CFLAGS		= -Wall -Wextra -Werror -g3

ifeq ($(debug), true)
	CFLAGS += -fsanitize=address,undefined
endif

INCLUDE			= include
SRC_DIR			= src
SRC_DIR_BONUS 	= src_bonus
OBJ_DIR			= obj
OBJ_DIR_BONUS 	= obj_bonus

RM			= rm -f

OBJS_PARSING = $(addprefix $(OBJ_DIR)/parsing/, $(SOURCES_PARSING:.c=.o))
OBJS_UTILS = $(addprefix $(OBJ_DIR)/utils/, $(SOURCES_UTILS:.c=.o))
OBJS_DISPLAY = $(addprefix $(OBJ_DIR)/display/, $(SOURCES_DISPLAY:.c=.o))
OBJS = $(OBJS_PARSING) $(OBJS_UTILS) $(OBJS_DISPLAY)

OBJS_PARSING_BONUS = $(addprefix $(OBJ_DIR_BONUS)/parsing/, $(SOURCES_PARSING_BONUS:.c=.o))
OBJS_UTILS_BONUS = $(addprefix $(OBJ_DIR_BONUS)/utils/, $(SOURCES_UTILS_BONUS:.c=.o))
OBJS_DISPLAY_BONUS = $(addprefix $(OBJ_DIR_BONUS)/display/, $(SOURCES_DISPLAY_BONUS:.c=.o))
OBJS_BONUS = $(OBJS_PARSING_BONUS) $(OBJS_UTILS_BONUS) $(OBJS_DISPLAY_BONUS)

all: intro lib obj $(NAME)

bonus: intro lib obj_bonus $(NAME_BONUS)

intro:
	@echo "$(GREEN)Compiling $(NAME)...$(NC)"

lib:
	@echo "$(YELLOW)Compiling libraries...$(NC)"
	@make -C $(MLX)
	@make -C $(LIBFT)

ifeq ($(UNAME), Darwin)
    LDFLAGS := -L $(LIBFT) -lft -L $(MLX) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
else
    LDFLAGS := -L $(LIBFT) -L $(MLX) -lmlx -lft -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)
endif

ifeq ($(UNAME), Darwin)
    LDFLAGS_BONUS := -L $(LIBFT) -lft -L $(MLX) -lmlx -framework OpenGL -framework AppKit -o $(NAME_BONUS)
else
    LDFLAGS_BONUS := -L $(LIBFT) -L $(MLX) -lmlx -lft -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME_BONUS)
endif

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking objects...$(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS)
#$(CC) -fsanitize=address $(OBJS) $(LDFLAGS)
	@echo "$(PURPLE)Compilation successful! ☆(❁‿❁)☆$(NC)"

obj:
	@echo "$(YELLOW)Creating object directories...$(NC)"
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/parsing $(OBJ_DIR)/utils $(OBJ_DIR)/display

$(OBJ_DIR)/parsing/%.o: $(SRC_DIR)/parsing/%.c $(INCLUDE)/cub3d.h Makefile
	@echo "    $(GREEN)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

$(OBJ_DIR)/utils/%.o: $(SRC_DIR)/utils/%.c $(INCLUDE)/cub3d.h Makefile
	@echo "    $(GREEN)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

$(OBJ_DIR)/display/%.o: $(SRC_DIR)/display/%.c $(INCLUDE)/cub3d.h Makefile
	@echo "    $(GREEN)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

$(NAME_BONUS): $(OBJS_BONUS)
	@echo "$(YELLOW)Linking objects bonuses...$(NC)"
	$(CC) $(OBJS_BONUS) $(LDFLAGS_BONUS)
#$(CC) -fsanitize=address $(OBJS) $(LDFLAGS)
	@echo "$(PURPLE)Compilation successful! ☆(❁‿❁)☆$(NC)"

obj_bonus:
	@echo "$(YELLOW)Creating object directories bonuses...$(NC)"
	@mkdir -p $(OBJ_DIR_BONUS) $(OBJ_DIR_BONUS)/parsing $(OBJ_DIR_BONUS)/utils $(OBJ_DIR_BONUS)/display

$(OBJ_DIR_BONUS)/parsing/%.o: $(SRC_DIR_BONUS)/parsing/%.c $(INCLUDE)/cub3d_bonus.h Makefile
	@echo "    $(GREEN)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

$(OBJ_DIR_BONUS)/utils/%.o: $(SRC_DIR_BONUS)/utils/%.c $(INCLUDE)/cub3d_bonus.h Makefile
	@echo "    $(GREEN)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

$(OBJ_DIR_BONUS)/display/%.o: $(SRC_DIR_BONUS)/display/%.c $(INCLUDE)/cub3d_bonus.h Makefile
	@echo "    $(GREEN)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

clean:
	@echo "$(RED)Cleaning up...$(NC)"
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)
	@$(RM) -rf $(OBJ_DIR)
	@$(RM) -rf $(OBJ_DIR_BONUS)

fclean: clean
	@echo "$(RED)Full cleaning... (◉◞౪◟◉)$(NC)"
	@$(RM) -f $(NAME)
	@$(RM) -f $(NAME_BONUS)
	@make fclean -C $(LIBFT)
	@make clean -C $(MLX)

re: fclean all

.PHONY: all intro clean fclean re lib obj bonus obj_bonus
