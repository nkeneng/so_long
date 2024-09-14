NAME = so_long

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

SRCS = main.c
TEST_SRCS = $(filter-out main.c, $(SRCS))
TESTS_FILES = $(shell find ./test -name "*_test.c")

LIBFT = -Llibft -lft

OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TESTS_FILES:.c=.o)

all: submodules libft $(NAME)

run: all
	./$(NAME)

submodules:
	if [ ! -d "libft" ]; then \
		mkdir libft; \
	fi
	if [ -z "$(shell ls -A libft)" ]; then \
		echo "libft submodule not initialized, initializing..."; \
		git submodule init && git submodule update --recursive; \
	fi
	if [ -z "$(shell ls -A libft/ft_printf)" -o -z "$(shell ls -A libft/get_next_line)" ]; then \
		echo "libft submodule not initialized, initializing..."; \
		cd libft && git submodule init && git submodule update --recursive; \
	fi

libft:
	$(MAKE) -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

test: $(TEST_SRCS:.c=.o) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_SRCS:.c=.o) $(TEST_OBJS) $(LIBFT) -lcriterion -o test.out && ./test.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(TEST_SRCS:.c=.o) $(TEST_OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f test.out
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re submodules libft test
