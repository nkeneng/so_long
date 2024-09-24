NAME = so_long

# Contains the X11 and MLX header files
ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
else
	INCLUDES = -I/opt/X11/include -Imlx
endif

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

SRCS_DIR		= ./sources/
SRCS = main.c $(addprefix $(SRCS_DIR), \
	   queue.c find_path.c utilities.c check_map.c \
	   xpm.c game.c free.c game_utils.c)

LIBFT = -Llibft -lft

OBJS = $(SRCS:.c=.o)

all: submodules libft $(MLX_LIB) $(NAME)

run: all
	./$(NAME) map.ber

debug: all
	lldb $(NAME) map.ber

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) map.ber

submodules:
	@if [ ! -d "libft" ]; then \
		mkdir libft; \
	fi
	@if [ -z "$(shell ls -A libft)" ]; then \
		echo "libft submodule not initialized, initializing..."; \
		git submodule init && git submodule update --recursive; \
	fi
	@if [ -z "$(shell ls -A libft/ft_printf)" -o -z "$(shell ls -A libft/get_next_line)" ]; then \
		echo "libft submodule not initialized, initializing..."; \
		cd libft && git submodule init && git submodule update --recursive; \
	fi

libft:
	$(MAKE) -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR) > /dev/null

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

clean:
	rm -f $(OBJS)
	rm -f $(TEST_SRCS:.c=.o) $(TEST_OBJS)
	$(MAKE) -C libft clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f test.out
	rm -f $(MLX_LIB)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re submodules libft test debug
