/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:00:38 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/22 11:27:50 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_xpm	create_xpm(char *path, t_game *game)
{
	t_xpm	asset;

	ft_printf("path = %s\n", path);
	asset.ptr = mlx_xpm_file_to_image(game->mlx, path, &(asset.position.x),
			&(asset.position.y));
	if (asset.ptr == NULL)
		free_and_exit("Error\nCouldn't find the image", &(game->map));
	return (asset);
}
