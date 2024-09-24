/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:56:59 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/24 16:28:58 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	place_xpms(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.map[y][x] == '1')
				draw_xpm(game->wall, y, x, game);
			if (game->map.map[y][x] == 'P')
				draw_xpm(get_player_by_position(game), y, x, game);
			if (game->map.map[y][x] == '0')
				draw_xpm(game->floor, y, x, game);
			if (game->map.map[y][x] == 'C')
				draw_xpm(game->fruit, y, x, game);
			if (game->map.map[y][x] == 'E')
				draw_xpm(game->exit2, y, x, game);
			x++;
		}
		y++;
	}
	ft_printf("moves: %d\n", game->moves);
}

void	open_window(t_game *game)
{
	t_point	s;

	s.x = game->map.width * XPM_SIZE;
	s.y = game->map.height * XPM_SIZE;
	game->win = mlx_new_window(game->mlx, s.x, s.y, "SO LONG");
	game->wall = create_xpm(WALL_IMG, game);
	game->fruit = create_xpm(FRUIT_IMG, game);
	game->floor = create_xpm(FLOOR_IMG, game);
	game->player_left = create_xpm(P_LEFT, game);
	game->player_right = create_xpm(P_RIGHT, game);
	game->player_back = create_xpm(P_BACK, game);
	game->player_front = create_xpm(P_FRONT, game);
	game->exit1 = create_xpm(EXIT1_IMG, game);
	game->exit2 = create_xpm(EXIT2_IMG, game);
	place_xpms(game);
}

void	move_player(t_game *game, int new_y, int new_x, int orientation)
{
	char	new_position;
	int		x;
	int		y;

	if (!is_valid_position(game, new_y, new_x))
		return ;
	new_position = game->map.map[new_y][new_x];
	if (new_position == 'E'
		&& game->map.collectibles == game->map.player.collectibles)
	{
		ft_printf("You win!\n");
		delete_game(game);
	}
	else if (new_position == '0' || new_position == 'C')
	{
		x = game->map.player.position.x;
		y = game->map.player.position.y;
		game->map.map[y][x] = '0';
		if (new_position == 'C')
			game->map.player.collectibles++;
		update_game_values(game, new_x, new_y, orientation);
		place_xpms(game);
	}
}

int	user_input(int keysym, t_game *game)
{
	if (keysym == KEY_UP || keysym == KEY_W)
		move_player(game, (*game).map.player.position.y - 1,
			game->map.player.position.x, BACK);
	if (keysym == KEY_LEFT || keysym == KEY_A)
		move_player(game, (*game).map.player.position.y,
			(*game).map.player.position.x - 1, LEFT);
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		move_player(game, (*game).map.player.position.y,
			(*game).map.player.position.x + 1, RIGHT);
	if (keysym == KEY_DOWN || keysym == KEY_S)
		move_player(game, (*game).map.player.position.y + 1,
			(*game).map.player.position.x, FRONT);
	if (keysym == KEY_Q || keysym == KEY_ESC)
	{
		ft_printf("Exiting\n");
		delete_game(game);
	}
	return (0);
}

void	handle_game(t_game *game)
{
	game->mlx = mlx_init();
	open_window(game);
	mlx_hook(game->win, 2, 1L << 0, user_input, game);
	mlx_hook(game->win, 17, 1L << 2, delete_game, game);
	mlx_loop(game->mlx);
	delete_game(game);
}
