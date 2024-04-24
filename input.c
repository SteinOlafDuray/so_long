/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sduray   <sduray@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 11:09:06 by sduray        #+#    #+#                 */
/*   Updated: 2024/04/14 17:39:54 by sduray        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	handle_input(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (handle_state_changes(key, game))
		return (0);
	return (0);
}

int	handle_state_changes(int key, t_game *game)
{
	if (key == 65307)
		return (close_window(game), 1);
	if (game->state == GAME_WON && key == 114)
		return (restart_game(game), 1);
	process_player_movement(key, game);
	return (0);
}

void	process_player_movement(int key, t_game *game)
{
	int	next_x;
	int	next_y;

	next_x = game->player_x;
	next_y = game->player_y;
	update_next_position(&next_x, &next_y, key);
	if (!check_if_move_is_wall(game, next_x, next_y))
	{
		update_game_state_with_movement(game, next_x, next_y);
		game->needs_redraw = 1;
	}
}

void	update_next_position(int *next_x, int *next_y, int key)
{
	if (key == 119)
		*next_y -= TILE_SIZE;
	if (key == 115)
		*next_y += TILE_SIZE;
	if (key == 97)
		*next_x -= TILE_SIZE;
	if (key == 100)
		*next_x += TILE_SIZE;
}

void	update_game_state_with_movement(t_game *game, int next_x, int next_y)
{
	int	map_x;
	int	map_y;

	map_x = next_x / TILE_SIZE;
	map_y = next_y / TILE_SIZE;
	if (game->player_x != next_x || game->player_y != next_y
		|| game->map[map_y][map_x] == 'C')
		game->needs_redraw = 1;
	game->player_x = next_x;
	game->player_y = next_y;
	game->current_count++;
	if (game->map[map_y][map_x] == 'C')
	{
		game->map[map_y][map_x] = '0';
		game->coins++;
	}
	else if (game->map[map_y][map_x] == 'E')
	{
		game->state = GAME_WON;
		game->player_x = game->spawn_x * TILE_SIZE;
		game->player_y = game->spawn_y * TILE_SIZE;
	}
}
