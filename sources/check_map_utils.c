/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:56:10 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/25 11:24:48 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	initialize_map_check_variables(t_map *map, int *num_exits,
		int *num_starts)
{
	*num_exits = 0;
	*num_starts = 0;
	(*map).collectibles = 0;
}

void	check_line_validity(char *line, t_map *map)
{
	if (ft_strlen(line) != (size_t)(*map).width)
		free_map("Error\nMap is not rectangular\n", map, 1, 1);
	if (map->height > 1)
	{
		if (!only_valid_characters(line))
			free_map("Error\nMap has invalid characters\n", map, 1, 1);
		if (line[0] != '1' || line[ft_strlen(line) - 2] != '1')
			free_map("Error\nMap is not closed middle lines\n", map, 1, 1);
	}
	else
	{
		if (!line_only_contains_ones(line))
			free_map("Error\nMap is not closed start or end\n", map, 1, 1);
	}
}

void	update_map_elements(char *line, int *num_exits, int *num_starts,
		t_map *map)
{
	counts_occurences(line, num_exits, 'E', &(*map).exit_pt.x);
	counts_occurences(line, num_starts, 'P', &(*map).start_pt.x);
	counts_occurences(line, &(*map).collectibles, 'C', 0);
	if (*num_exits > 1 || *num_starts > 1)
		free_map("Error\nMap has more than one exit or start\n", map, 1, 1);
	if ((*map).exit_pt.x != -1 && (*map).exit_pt.y == -1)
		(*map).exit_pt.y = (*map).height - 1;
	if ((*map).start_pt.x != -1 && (*map).start_pt.y == -1)
		(*map).start_pt.y = (*map).height - 1;
}

void	check_final_conditions(int num_exits, int num_starts, t_map *map,
		char *map_temp)
{
	if (num_exits == 0 || num_starts == 0 || (*map).collectibles == 0)
		free_map("Error\nMap has no exit or start or no collectibles\n", map, 1,
			1);
	(*map).map = ft_split(map_temp, '\n');
	if (!map->map)
		free_map("Error\nMalloc failed\n", map, 1, 1);
	if (!line_only_contains_ones(map->map[map->height - 1]))
		free_map("Error\nMap is not closed start or end\n", map, 1, 1);
	(*map).player.position.x = map->start_pt.x;
	(*map).player.position.y = map->start_pt.y;
	(*map).width--;
}
