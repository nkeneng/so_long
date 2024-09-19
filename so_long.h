/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:42:37 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/19 17:44:33 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/lib_ft/libft.h"
# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_player
{
	int					collectibles;
	t_point				position;
}						t_player;

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

typedef struct s_map
{
	char				**map;
	int					width;
	int					height;
	t_point				start_pt;
	t_point				exit_pt;
	int					collectibles;
}						t_map;

/*typedef struct s_data*/
/*{*/
/*	void			*mlx_ptr;*/
/*	void			*win_ptr;*/
/*	void			*textures[5];*/
/*	t_map			*map;*/
/*}					t_data;*/

char					**initialize_visited_map(t_map *map);
void					initialize_queue(t_queue *queue);
void					process_map_element(char map_el,
							int *collectibles_found, int *exit_reached);
void					explore_neighbours(t_point current, char **visited,
							t_queue *queue, t_map *map);
void					free_visited_map(char **visited, int rows);
void					enqueue(t_queue *queue, t_point point);
int						is_queue_empty(t_queue *queue);
t_point					dequeue(t_queue *queue);
#endif
