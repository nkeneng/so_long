/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:59:12 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/25 10:56:10 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	free_map(char *str, t_map *map, int quit, int closefd)
{
	int	i;

	i = 0;
	while (map->map && i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	if (ft_strncmp(str, "", 1) != 0)
		ft_putstr_fd(str, 1);
	if (closefd)
		close(map->fd);
	if (quit)
		exit(EXIT_FAILURE);
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

int	line_only_contains_ones(char *line)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (line[i] && i < (int)len - 1)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	only_valid_characters(char *line)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (line[i] && i < (int)len - 1)
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'P' && line[i] != 'E'
			&& line[i] != 'C')
			return (0);
		i++;
	}
	return (1);
}

int	open_map_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCan't open file\n", 1);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
