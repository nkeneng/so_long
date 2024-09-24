/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:00:38 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/24 16:42:24 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_xpm	create_xpm(char *path, t_game *game)
{
	t_xpm	asset;

	asset.ptr = mlx_xpm_file_to_image(game->mlx, path, &(asset.position.x),
			&(asset.position.y));
	if (asset.ptr == NULL)
	{
		free_map("Error\nCouldn't find the image", &(game->map), 0);
		delete_game(game);
	}
	return (asset);
}
