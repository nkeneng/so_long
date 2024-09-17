/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/17 14:25:43 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/get_next_line/get_next_line.h"
#include "libft/lib_ft/libft.h"
#include "so_long.h"
#include <sys/fcntl.h>

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
	int i = 0;

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

void	check_map(int fd)
{
	char	*line;
	char	*prev_line;
	size_t	map_line_length;
	int		first_line;

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
			{
				ft_putstr_fd("Error\nMap is not rectangular\n", 2);
				free(line);
				exit(EXIT_FAILURE);
			}
			if (!line_only_contains_ones(prev_line))
			{
				ft_putstr_fd("Error\nMap is not closed\n", 2);
				free(line);
				exit(EXIT_FAILURE);
			}
			break ;
		}
		if (!first_line)
		{
			if (line[0] != '1' || line[ft_strlen(line) - 2] != '1')
			{
				ft_putstr_fd("Error\nMap is not closed middle lines\n", 2);
				free(line);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (!line_only_contains_ones(line))
			{
				ft_putstr_fd("Error\nMap is not closed start or end\n", 2);
				free(line);
				exit(EXIT_FAILURE);
			}
		}
		free(prev_line);
		prev_line = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		first_line = 0;
	}
}

int	main(int argc, char *argv[])
{
	// t_map	map;
	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	check_map(open_map_file(argv[1]));
	return (EXIT_SUCCESS);
}
