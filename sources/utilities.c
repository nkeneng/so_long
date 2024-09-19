/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:59:12 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/19 18:59:31 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_and_exit(char *str)
{
	ft_putstr_fd(str, 2);
	// freeeeee
	exit(EXIT_FAILURE);
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
