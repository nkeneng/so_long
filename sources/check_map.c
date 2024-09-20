/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:56:10 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/20 17:20:32 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	initialize_map_check_variables(t_map *map, int *num_exits,
		int *num_starts, int *first_line, int *map_index)
{
	*map_index = 0;
	*num_exits = 0;
	*num_starts = 0;
	*first_line = 1;
	(*map).collectibles = 0;
}

void	check_line_validity(char *line, char *prev_line, int first_line,
		t_map *map)
{
	if (line == NULL)
	{
		if (ft_strlen(prev_line) != (size_t)(*map).width)
			free_and_exit("Error\nMap is not rectangular\n", map);
		if (!line_only_contains_ones(prev_line))
			free_and_exit("Error\nMap is not closed\n", map);
	}
	else
	{
		if (ft_strlen(line) != (size_t)(*map).width)
			free_and_exit("Error\nMap is not rectangular\n", map);
		if (!first_line)
		{
			if (!only_valid_characters(line))
				free_and_exit("Error\nMap has invalid characters\n", map);
			if (line[0] != '1' || line[ft_strlen(line) - 2] != '1')
				free_and_exit("Error\nMap is not closed middle lines\n", map);
		}
		else
		{
			if (!line_only_contains_ones(line))
				free_and_exit("Error\nMap is not closed start or end\n", map);
		}
	}
}

void	update_map_elements(char *line, int *num_exits, int *num_starts,
		t_map *map, int map_index)
{
	counts_occurences(line, num_exits, 'E', &(*map).exit_pt.y);
	counts_occurences(line, num_starts, 'P', &(*map).start_pt.y);
	counts_occurences(line, &(*map).collectibles, 'C', 0);
	if (*num_exits > 1 || *num_starts > 1)
		free_and_exit("Error\nMap has more than one exit or start\n", map);
	if ((*map).exit_pt.y != -1 && (*map).exit_pt.x == -1)
		(*map).exit_pt.x = map_index;
	if ((*map).start_pt.y != -1 && (*map).start_pt.x == -1)
		(*map).start_pt.x = map_index;
}

void	check_final_conditions(int num_exits, int num_starts, t_map *map)
{
	if (num_exits == 0 || num_starts == 0 || (*map).collectibles == 0)
		free_and_exit("Error\nMap has no exit or start or no collectibles\n",
			map);
}
