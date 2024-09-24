/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:42:37 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/24 16:41:11 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// DEFINES

# define WALL_IMG "assets/xpm/wall.xpm"
# define P_FRONT "assets/xpm/player/front.xpm"
# define P_BACK "assets/xpm/player/front.xpm"
# define P_LEFT "assets/xpm/player/front.xpm"
# define P_RIGHT "assets/xpm/player/front.xpm"
# define FLOOR_IMG "assets/xpm/floor.xpm"
# define FRUIT_IMG "assets/xpm/fruit.xpm"
# define EXIT1_IMG "assets/xpm/exit/flag1.xpm"
# define EXIT2_IMG "assets/xpm/exit/flag2.xpm"

# define XPM_SIZE 64

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_Q 113
# define KEY_ESC 65307

# define FRONT 0
# define BACK 1
# define LEFT 2
# define RIGHT 3

# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/lib_ft/libft.h"
# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/fcntl.h>

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_player
{
	int					collectibles;
	t_point				position;
	int					orientation;
}						t_player;

typedef struct s_map
{
	char				**map;
	int					width;
	int					height;
	t_point				start_pt;
	t_point				exit_pt;
	int					collectibles;
	t_player			player;
}						t_map;

typedef struct t_xpm
{
	t_point				position;
	void				*ptr;
}						t_xpm;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	t_map				map;
	t_xpm				wall;
	t_xpm				floor;
	t_xpm				fruit;
	t_xpm				exit1;
	t_xpm				exit2;
	t_xpm				player_left;
	t_xpm				player_right;
	t_xpm				player_front;
	t_xpm				player_back;
	int					moves;
}						t_game;

// Only used for BFS

typedef struct s_queue_node
{
	t_point				point;
	struct s_queue_node	*next;
}						t_queue_node;

typedef struct s_queue
{
	t_queue_node		*front;
	t_queue_node		*rear;
}						t_queue;

char					**initialize_visited_map(t_map *map);
void					initialize_queue(t_queue *queue);
void					process_map_element(char map_el,
							int *collectibles_found, int *exit_reached);
void					explore_neighbours(t_point current, char **visited,
							t_queue *queue, t_map *map);
void					free_visited_map(char **visited, int rows);

// sources/queue.c

void					enqueue(t_queue *queue, t_point point);
int						is_queue_empty(t_queue *queue);
t_point					dequeue(t_queue *queue);

// sources/check_map.c
void					initialize_map_check_variables(t_map *map,
							int *num_exits, int *num_starts, int *first_line);
void					check_line_validity(char *line, int first_line,
							t_map *map);
void					update_map_elements(char *line, int *num_exits,
							int *num_starts, t_map *map);
void					check_final_conditions(int num_exits, int num_starts,
							t_map *map);

// sources/utilities.c
int						free_map(char *str, t_map *map, int exit);
void					counts_occurences(char *line, int *num_exits, char c,
							int *x);
int						line_only_contains_ones(char *line);
int						only_valid_characters(char *line);
int						open_map_file(char *file);

// sources/xpm.c
t_xpm					create_xpm(char *path, t_game *game);

// sources/game.c
void					handle_game(t_game *game);

// sources/game_utils.c

void					draw_xpm(t_xpm xpm, int y, int x, t_game *game);
void					update_game_values(t_game *game, int new_x, int new_y,
							int orientation);
int						is_valid_position(t_game *game, int new_y, int new_x);
t_xpm					get_player_by_position(t_game *game);

// sources/free.c
void					delete_images(t_game *game);
int						delete_game(t_game *game);

#endif
