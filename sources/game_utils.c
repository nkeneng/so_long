/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:26:31 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/24 16:28:52 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_xpm	get_player_by_position(t_game *game)
{
	int	position;

	position = game->map.player.orientation;
	if (position == FRONT)
		return (game->player_front);
	if (position == BACK)
		return (game->player_back);
	if (position == RIGHT)
		return (game->player_right);
	return (game->player_left);
}

int	is_valid_position(t_game *game, int new_y, int new_x)
{
	return (!(new_y < 0 || new_x < 0 || new_y >= game->map.height
			|| new_x >= game->map.width));
}

void	update_game_values(t_game *game, int new_x, int new_y, int orientation)
{
	game->map.player.position.x = new_x;
	game->map.player.position.y = new_y;
	game->map.map[new_y][new_x] = 'P';
	game->moves++;
	game->map.player.orientation = orientation;
}

void	draw_xpm(t_xpm xpm, int y, int x, t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, xpm.ptr, x * XPM_SIZE, y
		* XPM_SIZE);
}
