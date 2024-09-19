/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:59:12 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/19 18:03:53 by stevennke        ###   ########.fr       */
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
