/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/19 17:48:56 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/get_next_line/get_next_line.h"
#include "libft/lib_ft/libft.h"
#include "so_long.h"
#include <sys/fcntl.h>

void	free_and_exit(char *str)
{
	ft_putstr_fd(str, 2);
	// freeeeee
	exit(EXIT_FAILURE);
}

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

int	line_only_contains_ones(char *line)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_strlen(line));
	ft_strlcpy(str, line, ft_strlen(line) - 1);
	while (str[i])
	{
		if (*str != '1')
			return (0);
		i++;
	}
	if (str)
		free(str);
	return (1);
}

void	counts_occurences(char *line, int *num_exits, char c, int *x)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			if (x)
				*x = i;
			*num_exits += 1;
		}
		i++;
	}
}

void	check_map(int fd, t_map *map)
{
	char	*line;
	char	*prev_line;
	size_t	map_line_length;
	int		first_line;
	int		num_exits;
	int		num_starts;
	int		map_index;

	map_index = 0;
	num_exits = 0;
	num_starts = 0;
	first_line = 1;
	line = get_next_line(fd);
	prev_line = NULL;
	if (!line)
	{
		ft_putstr_fd("Error\nEmpty file\n", 2);
		exit(EXIT_FAILURE);
	}
	map_line_length = ft_strlen(line);
	while (1)
	{
		if (line == NULL)
		{
			if (ft_strlen(prev_line) != map_line_length)
				free_and_exit("Error\nMap is not rectangular\n");
			if (!line_only_contains_ones(prev_line))
				free_and_exit("Error\nMap is not closed\n");
			break ;
		}
		(*map).map[map_index] = ft_strdup(line);
		map_index++;
		if (!first_line)
		{
			if (line[0] != '1' || line[ft_strlen(line) - 2] != '1')
				free_and_exit("Error\nMap is not closed middle lines\n");
			counts_occurences(line, &num_exits, 'E', &(*map).exit_pt.x);
			counts_occurences(line, &num_starts, 'P', &(*map).start_pt.x);
			counts_occurences(line, &(*map).collectibles, 'C', 0);
			if (num_exits > 1 || num_starts > 1)
				free_and_exit("Error\nMap has more than one exit or start\n");
			if ((*map).exit_pt.x != -1 && (*map).exit_pt.y == -1)
				(*map).exit_pt.y = map_index;
			if ((*map).start_pt.x != -1 && (*map).start_pt.y == -1)
				(*map).start_pt.y = map_index;
		}
		else
		{
			if (!line_only_contains_ones(line))
				free_and_exit("Error\nMap is not closed start or end\n");
		}
		free(prev_line);
		prev_line = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		first_line = 0;
	} // end while
	if (num_exits == 0 || num_starts == 0 || (*map).collectibles == 0)
		free_and_exit("Error\nMap has no exit or start or no collectibles\n");
	(*map).width = map_line_length;
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

int	main(int argc, char *argv[])
{
	t_map		map;
	t_player	player;
	int			fd;
	int			map_lines;

	map_lines = 0;
	map.collectibles = 0;
	map.exit_pt.x = -1;
	map.exit_pt.y = -1;
	map.start_pt.x = -1;
	map.start_pt.y = -1;
	player.collectibles = 0;
	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	fd = open_map_file(argv[1]);
	map_lines = count_lines(fd);
	if (!map_lines)
		free_and_exit("File Empty");
	(map.map) = malloc(map_lines * sizeof(char *));
	map.height = map_lines;
	close(fd);
	fd = open_map_file(argv[1]);
	check_map(fd, &map);
	if (check_map_navigation(&map))
	{
		ft_printf("Found %d collectibles\n", map.collectibles);
	}
	else
	{
		ft_putstr_fd("Error\nNo path found\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
