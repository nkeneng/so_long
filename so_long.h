/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:42:37 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/16 18:44:25 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/lib_ft/libft.h"
# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_map
{
	char	**map;
	int		width;
	int		start_pt;
	int		exit_pt;
}			t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*textures[5];
	t_map	*map;
}			t_data;

#endif
