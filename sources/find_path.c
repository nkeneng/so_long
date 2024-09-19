/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:35:14 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/19 19:06:44 by stevennke        ###   ########.fr       */
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

void	print_visited_map(char **visited, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (visited[i][j] == 1)
				printf("1 "); // Visited cell
			else
				printf("0 "); // Unvisited cell
		}
		printf("\n");
	}
	printf("\n"); // Print a newline for better readability between steps
}

void	explore_neighbours(t_point current, char **visited, t_queue *queue,
		t_map *map)
{
	int		i;
	t_point	next_point;

	int directions[4][2]; // Declaration
	// Initialization
	directions[0][0] = -1;
	directions[0][1] = 0; // Up
	directions[1][0] = 1;
	directions[1][1] = 0; // Down
	directions[2][0] = 0;
	directions[2][1] = -1; // Left
	directions[3][0] = 0;
	directions[3][1] = 1; // Right
	i = 0;
	int new_x, new_y;
	while (i < 4)
	{
		new_x = current.x + directions[i][0];
		new_y = current.y + directions[i][1];
		if (new_x >= 0 && new_x < map->height && new_y >= 0
			&& new_y < map->width)
		{
			if (map->map[new_x][new_y] != '1' && !visited[new_x][new_y])
			{
				visited[new_x][new_y] = 1;
				next_point.y = new_y;
				next_point.x = new_x;
				enqueue(queue, next_point);
				print_visited_map(visited, map->width, map->height);
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
