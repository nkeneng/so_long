/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/09 20:46:12 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	main(int argc, char *argv[])
{
	ft_printf("Number of arguments: %d\n", argc);
	for (int i = 0; i < argc; i++)
	{
		ft_printf("Argument %d: %s\n", i, argv[i]);
	}
	return (EXIT_SUCCESS);
}
