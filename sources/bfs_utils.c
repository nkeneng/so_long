/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:36:02 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/25 11:36:31 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	**init_bfs_directions(void)
{
	int	**directions;
	int	i;

	i = 0;
	directions = malloc(4 * sizeof(int *));
	while (i < 4)
	{
		directions[i] = malloc(2 * sizeof(int));
		i++;
	}
	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = 0;
	directions[3][1] = 1;
	return (directions);
}

void	free_directions(int ***directions)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free((*directions)[i]);
		i++;
	}
	free(*directions);
}
