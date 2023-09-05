CC		= cc
NAME		= cub3d
UNAME 		:= $(shell uname)

RED		= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
PURPLE		= \033[0;35m
NC		= \033[0m

SOURCES_DISPLAY		=	draw_back.c		\
						draw_cub.c		\
						draw_stripe.c	\
						draw_wall.c		\
						init_cub.c		\
						init_rot.c		\
						init_textures.c	\
						move.c			\
						rotate.c		\

SOURCES_PARSING 	=	parse.c			\
						parse_params.c	\
						main.c			\

SOURCES_UTILS 		=	lst_utils.c		\
						map_utils.c		\
						map_check.c		\
						mlx_actions.c	\
						mlx_utils.c		\

LIBFT		= libft
MLX			= mlx

CFLAGS		= -Wall -Wextra -Werror -g3

INCLUDE		= include
SRC_DIR		= src
OBJ_DIR		= obj

RM			= rm -f

OBJS_PARSING = $(addprefix $(OBJ_DIR)/parsing/, $(SOURCES_PARSING:.c=.o))
OBJS_UTILS = $(addprefix $(OBJ_DIR)/utils/, $(SOURCES_UTILS:.c=.o))
OBJS_DISPLAY = $(addprefix $(OBJ_DIR)/display/, $(SOURCES_DISPLAY:.c=.o))
OBJS = $(OBJS_PARSING) $(OBJS_UTILS) $(OBJS_DISPLAY)

all: intro lib obj $(NAME)

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

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking objects...$(NC)"
	$(CC) $(OBJS) $(LDFLAGS)
	@echo "$(PURPLE)Compilation successful!$(NC)"

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

clean:
	@echo "$(RED)Cleaning up...$(NC)"
	@make clean -C $(LIBFT)
	@$(RM) -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Full cleaning...$(NC)"
	@$(RM) -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all intro clean fclean re lib obj
