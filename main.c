/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/20 17:43:45 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free(line);
			break ;
		}
		count++;
		free(line);
	}
	return (count);
}

int	open_map_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCan't open file\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	check_map(int fd, t_map *map)
{
	char	*line;
	char	*prev_line;
	int		first_line;
	int		num_exits;
	int		num_starts;
	int		map_index;

	initialize_map_check_variables(map, &num_exits, &num_starts, &first_line,
		&map_index);
	line = get_next_line(fd);
	prev_line = NULL;
	if (!line)
		free_and_exit("Error\nEmpty file", map);
	(*map).width = ft_strlen(line);
	while (1)
	{
		check_line_validity(line, prev_line, first_line, map);
		if (line == NULL)
			break ;
		(*map).map[map_index] = ft_strdup(line);
		if (!first_line)
			update_map_elements(line, &num_exits, &num_starts, map, map_index);
		map_index++;
		free(prev_line);
		prev_line = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		first_line = 0;
	}
	free(line);
	free(prev_line);
	check_final_conditions(num_exits, num_starts, map);
	ft_printf("Start point: x-> %d, y -> %d\n", map->start_pt.x, map->start_pt.y);
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
	visited[map->start_pt.x][map->start_pt.y] = 1;
	enqueue(&queue, map->start_pt);
	while (!is_queue_empty(&queue))
	{
		current = dequeue(&queue);
		map_el = map->map[current.x][current.y];
		process_map_element(map_el, &collectibles_found, &exit_reached);
		explore_neighbours(current, visited, &queue, map);
	}
	free_visited_map(visited, map->height);
	if (collectibles_found == map->collectibles && exit_reached)
		return (1);
	else
		return (0);
}

void init_map(t_map *map)
{
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->exit_pt.x = -1;
	map->exit_pt.y = -1;
	map->start_pt.x = -1;
	map->start_pt.y = -1;
	map->player.collectibles = 0;
}

int	main(int argc, char *argv[])
{
	t_map		map;
	int			fd;
	int			map_lines;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	map_lines = 0;
	init_map(&map);
	fd = open_map_file(argv[1]);
	map_lines = count_lines(fd);
	if (!map_lines)
		free_and_exit("File Empty", &map);
	(map.map) = malloc(map_lines * sizeof(char *));
	map.height = map_lines;
	ft_printf("Map height: %d\n", map.height);
	close(fd);
	fd = open_map_file(argv[1]);
	check_map(fd, &map);
	close(fd);
	if (check_map_navigation(&map))
		ft_printf("Found %d collectibles\n", map.collectibles);
	else
		free_and_exit("Error\nPath not found\n", &map);
	return (free_and_exit("", &map));
}
