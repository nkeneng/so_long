/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/22 12:04:12 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lib_ft/libft.h"
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

void	check_map(char *file, t_map *map)
{
	char	*line;
	char	*map_temp;
	int		first_line;
	int		num_exits;
	int		num_starts;
	int		fd;

	map_temp = ft_strdup("");
	fd = open_map_file(file);
	initialize_map_check_variables(map, &num_exits, &num_starts, &first_line);
	line = get_next_line(fd);
	if (!line)
		free_and_exit("Error\nEmpty file", map);
	(*map).width = ft_strlen(line);
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

void	init_point(t_point *point)
{
	point->x = -1;
	point->y = -1;
}

void	init_map(t_game *game)
{
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.collectibles = 0;
	init_point(&game->map.exit_pt);
	init_point(&game->map.start_pt);
	game->map.player.collectibles = 0;
}

void	draw_xpm(t_xpm xpm, int x, int y, t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, xpm.ptr, y * XPM_SIZE, x * XPM_SIZE);
}

void	open_window(t_game *game)
{
	t_point	s;
	int		x;
	int		y;

	s.x = game->map.width * XPM_SIZE;
	s.y = game->map.height * XPM_SIZE;
	game->win = mlx_new_window(game->mlx, s.x, s.y, "SO LONG");
	game->wall = create_xpm(WALL_IMG, game);
	x = 0;
	while (x < game->map.height)
	{
		y = 0;
		while (y < game->map.width)
		{
			if (game->map.map[x][y] == '1')
				draw_xpm(game->wall, x, y, game);
			y++;
		}
		x++;
	}
	mlx_hook(game->win, 17, 0, NULL, game);
}

void	handle_game(t_game *game)
{
	game->mlx = mlx_init();
	open_window(game);
	mlx_loop(game->mlx);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	init_map(&game);
	check_map(argv[1], &game.map);
	if (check_map_navigation(&game.map))
		ft_printf("Found %d collectibles\n", game.map.collectibles);
	else
		free_and_exit("Error\nPath not found\n", &game.map);
	handle_game(&game);
	return (free_and_exit("", &game.map));
}
