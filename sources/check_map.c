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

static void	process_line(t_map *map, t_map_check *check)
{
	map->height++;
	if(check_line_validity(check->line, map) > 0)
	{
		free(check->map_temp);
		free(check->line);
		free_map("", map, 1 , 1);
	}
	if (map->height > 1)
	{
		if(update_map_elements(check->line, &check->num_exits, &check->num_starts, map) > 0)
		{
			free(check->map_temp);
			free(check->line);
			free_map("", map, 1 , 1);
		}
	}
	check->map_temp = ft_stradd(&check->map_temp, check->line);
}

static void	read_map_lines(t_map *map, int fd, t_map_check *check)
{
	while (1)
	{
		check->line = get_next_line(fd);
		if (check->line == NULL)
			break ;
		process_line(map, check);
		free(check->line);
	}
}

void	check_map(t_map *map, int fd)
{
	t_map_check	check;

	check = (t_map_check){0, 0, ft_strdup(""), NULL};
	check.line = get_next_line(fd);
	if (!check.line)
		free_map("Error\nEmpty file", map, 1, 1);
	map->width = ft_strlen(check.line);
	process_line(map, &check);
	free(check.line);
	read_map_lines(map, fd, &check);
	if (check_final_conditions(check.num_exits, check.num_starts, map,
		check.map_temp) > 0)
	{
	free(check.map_temp);
		free_map("",map , 1 , 1);
	}
	free(check.map_temp);
}
