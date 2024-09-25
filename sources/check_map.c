/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:50:01 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/25 11:50:02 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	process_line(char *line, t_map *map, t_map_check *check)
{
	map->height++;
	check_line_validity(line, map);
	if (map->height > 1)
		update_map_elements(line, &check->num_exits, &check->num_starts, map);
	check->map_temp = ft_stradd(&check->map_temp, line);
}

static void	read_map_lines(t_map *map, int fd, t_map_check *check)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		process_line(line, map, check);
		free(line);
	}
}

void	check_map(t_map *map, int fd)
{
	char		*line;
	t_map_check	check;

	check = (t_map_check){0, 0, ft_strdup("")};
	line = get_next_line(fd);
	if (!line)
		free_map("Error\nEmpty file", map, 1, 1);
	map->width = ft_strlen(line);
	process_line(line, map, &check);
	free(line);
	read_map_lines(map, fd, &check);
	check_final_conditions(check.num_exits, check.num_starts, map,
		check.map_temp);
	free(check.map_temp);
}
