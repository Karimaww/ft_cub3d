CC			= cc

NAME		= cub3d

SOURCES_DISPLAY		=	draw_cub.c		\
						draw_line.c		\
						hooks.c			\
						init_cub.c		\

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

OBJS_PARSING = $(addprefix $(OBJ_DIR)/parsing/,$(SOURCES_PARSING:.c=.o))
OBJS_UTILS = $(addprefix $(OBJ_DIR)/utils/,$(SOURCES_UTILS:.c=.o))
OBJS_DISPLAY = $(addprefix $(OBJ_DIR)/display/,$(SOURCES_DISPLAY:.c=.o))
OBJS = $(OBJS_PARSING) $(OBJS_UTILS) $(OBJS_DISPLAY)

all: lib obj $(NAME)

lib:
	@make -C $(MLX)
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L $(LIBFT) -L $(MLX) -lmlx -lft -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)
#$(CC) $(OBJS) -L $(LIBFT) -lft -lncurses -o $(NAME)

#$(CC) $(OBJS) -L $(LIBFT) -L $(MLX) -lmlx -lft -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

obj:
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/parsing $(OBJ_DIR)/utils $(OBJ_DIR)/display

$(OBJ_DIR)/parsing/%.o: $(SRC_DIR)/parsing/%.c $(INCLUDE)/cub3d.h Makefile
	$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

$(OBJ_DIR)/utils/%.o: $(SRC_DIR)/utils/%.c $(INCLUDE)/cub3d.h Makefile
	$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

$(OBJ_DIR)/display/%.o: $(SRC_DIR)/display/%.c $(INCLUDE)/cub3d.h Makefile
	$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

bonus: $(NAME)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re