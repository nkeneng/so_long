/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:35:14 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/24 18:18:47 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	**initialize_visited_map(t_map *map)
{
	int		rows;
	int		cols;
	int		i;
	char	**visited;

	rows = (*map).height;
	cols = (*map).width;
	i = 0;
	visited = malloc(rows * sizeof(char *));
	while (i < rows)
	{
		visited[i] = ft_calloc(cols, sizeof(char));
		i++;
	}
	return (visited);
}

void	initialize_queue(t_queue *queue)
{
	queue->rear = NULL;
	queue->front = NULL;
}

void	process_map_element(char map_el, int *collectibles_found,
		int *exit_reached)
{
	if (map_el == 'C')
		(*collectibles_found)++;
	if (map_el == 'E')
		*exit_reached = 1;
}

void	explore_neighbours(t_point current, char **visited, t_queue *queue,
		t_map *map)
{
	int		i;
	t_point	next_point;
	int		directions[4][2];
	int		new_x;
	int		new_y;

	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = 0;
	directions[3][1] = 1;
	i = 0;
	while (i < 4)
	{
		new_x = current.x + directions[i][0];
		new_y = current.y + directions[i][1];
		if (new_x >= 0 && new_x < map->width && new_y >= 0
			&& new_y < map->height)
		{
			if (map->map[new_y][new_x] != '1' && !visited[new_y][new_x])
			{
				visited[new_y][new_x] = 1;
				next_point.y = new_y;
				next_point.x = new_x;
				enqueue(queue, next_point);
			}
		}
		i++;
	}
}

void	free_visited_map(char **visited, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
