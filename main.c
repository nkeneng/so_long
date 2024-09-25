/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/25 11:24:23 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_navigation(t_map *map)
{
	int		collectibles_found;
	int		exit_reached;
	t_queue	queue;
	t_point	current;
	char	**visited;

	collectibles_found = 0;
	exit_reached = 0;
	visited = initialize_visited_map(map);
	initialize_queue(&queue);
	visited[map->start_pt.y][map->start_pt.x] = 1;
	enqueue(&queue, map->start_pt);
	while (!is_queue_empty(&queue))
	{
		current = dequeue(&queue);
		process_map_element(map->map[current.y][current.x], &collectibles_found,
			&exit_reached);
		explore_neighbours(current, visited, &queue, map);
	}
	free_visited_map(visited, map->height);
	if (collectibles_found == map->collectibles && exit_reached)
		return (1);
	else
		return (0);
}

void	init_point(t_point *point)
{
	point->x = -1;
	point->y = -1;
}

void	init_map(t_game *game)
{
	game->moves = 0;
	game->map.player.orientation = FRONT;
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.collectibles = 0;
	init_point(&game->map.exit_pt);
	init_point(&game->map.start_pt);
	game->map.player.collectibles = 0;
	init_point(&game->map.player.position);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 1);
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4) != 0)
		free_map("Error\nInvalid file extension\n", &game.map, 1, 0);
	init_map(&game);
	game.map.fd = open_map_file(argv[1]);
	check_map(&game.map, game.map.fd);
	if (!check_map_navigation(&game.map))
		free_map("Error\nPath not found\n", &game.map, 1, 1);
	handle_game(&game);
	free_map("", &game.map, 0, 1);
	return (EXIT_SUCCESS);
}
