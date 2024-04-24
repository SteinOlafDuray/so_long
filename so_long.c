/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sduray   <sduray@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 11:09:06 by sduray        #+#    #+#                 */
/*   Updated: 2024/04/24 18:34:08 by sduray        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	print_error(int i)
{
	write(1, "Something wrong with your map buddy boy!\n", 42);
	i = 0;
}

int	update_new_frame(void *param)
{
	t_game	*game;
	int		x;
	int		y;

	game = (t_game *)param;
	x = game->player_x;
	y = game->player_y + TILE_SIZE;
	if (game->needs_redraw == 1)
	{
		draw_map(game);
		game->needs_redraw = 0;
	}
	update_animation(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img_player, x, y);
	if (game->state == GAME_WON)
		draw_game_won(game);
	else if (game->state == GAME_LOST)
		draw_game_lost(game);
	game->prev_x = game->player_x;
	game->prev_y = game->player_y;
	return (0);
}

int	check_if_move_is_wall(t_game *game, int next_x, int next_y)
{
	int	tile_x;
	int	tile_y;

	tile_y = next_y / TILE_SIZE;
	tile_x = next_x / TILE_SIZE;
	if (tile_x >= 0 && tile_x < game->map_width && tile_y >= 0
		&& tile_y < game->map_height)
	{
		if (game->map[tile_y][tile_x] == '1')
			return (1);
		if (game->map[tile_y][tile_x] == 'E')
			return (game->state = GAME_WON, 0);
	}
	return (0);
}


void	update_animation(t_game *game)
{
	game->animation_timer++;
	if (game->animation_timer >= 6)
		game->animation_timer = 0;
}

int	main(void)
{
	t_game	game;
	char	*map_path;
	int		win_width;
	int		win_height;
	
	map_path = "./map.ber";
	if (initiliaze_game(&game, map_path) == 1)
		return (EXIT_FAILURE);
	win_width = game.map_width * TILE_SIZE;
	win_height = game.map_height * TILE_SIZE + TILE_SIZE;
	setup_graphics(&game, win_width, win_height);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
