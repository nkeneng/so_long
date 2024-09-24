/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:32:53 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/24 15:21:40 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	delete_images(t_game *game)
{
	mlx_destroy_image(game->mlx, game->wall.ptr);
	mlx_destroy_image(game->mlx, game->floor.ptr);
	mlx_destroy_image(game->mlx, game->fruit.ptr);
	mlx_destroy_image(game->mlx, game->player_front.ptr);
	mlx_destroy_image(game->mlx, game->player_left.ptr);
	mlx_destroy_image(game->mlx, game->player_right.ptr);
	mlx_destroy_image(game->mlx, game->player_back.ptr);
	mlx_destroy_image(game->mlx, game->exit1.ptr);
	mlx_destroy_image(game->mlx, game->exit2.ptr);
}

int	delete_game(t_game *game)
{
	delete_images(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free_map("", &(game->map));
	free(game->mlx);
	exit(0);
}
