/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/24 18:19:08 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map(char *file, t_map *map)
{
	char	*line;
	char	*map_temp;
	int		first_line;
	int		num_exits;
	int		num_starts;
	int		fd;

	if (ft_strncmp(file + ft_strlen(file) - 4, ".ber", 4) != 0)
		free_map("Error\nInvalid file extension\n", map, 1);
	fd = open_map_file(file);
	initialize_map_check_variables(map, &num_exits, &num_starts, &first_line);
	line = get_next_line(fd);
	if (!line)
		free_map("Error\nEmpty file", map, 1);
	(*map).width = ft_strlen(line);
	map_temp = ft_strdup("");
	while (1)
	{
		if (line == NULL)
		{
			free(line);
			break ;
		}
		(*map).height++;
		check_line_validity(line, first_line, map);
		if (!first_line)
			update_map_elements(line, &num_exits, &num_starts, map);
		map_temp = ft_stradd(&map_temp, line);
		free(line);
		line = get_next_line(fd);
		first_line = 0;
	}
	close(fd);
	check_final_conditions(num_exits, num_starts, map);
	(*map).map = ft_split(map_temp, '\n');
	(*map).player.position.x = map->start_pt.x;
	(*map).player.position.y = map->start_pt.y;
	free(map_temp);
	(*map).width--;
	ft_printf("Start point: x-> %d, y -> %d\n", map->start_pt.x,
		map->start_pt.y);
}

int	check_map_navigation(t_map *map)
{
	int		collectibles_found;
	int		exit_reached;
	t_queue	queue;
	t_point	current;
	char	map_el;
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
		map_el = map->map[current.y][current.x];
		process_map_element(map_el, &collectibles_found, &exit_reached);
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
	init_map(&game);
	check_map(argv[1], &game.map);
	if (!check_map_navigation(&game.map))
		free_map("Error\nPath not found\n", &game.map, 1);
	handle_game(&game);
	free_map("", &game.map, 0);
	return (EXIT_SUCCESS);
}
