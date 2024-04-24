/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilize.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sduray   <sduray@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 11:09:06 by sduray        #+#    #+#                 */
/*   Updated: 2024/04/24 19:06:28 by sduray        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	restart_game(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	load_map_from_file("./map.ber", game);
	game->current_count = 0;
	game->coins = 0;
	game->animation_timer = 0;
	game->player_x = game->spawn_x * TILE_SIZE;
	game->player_y = game->spawn_y * TILE_SIZE;
	draw_map(game);
	update_new_frame(game);
	game->state = GAME_PLAYING;
}

int	close_window(void *game)
{
	exit(0);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->window, 17, 0, close_window, NULL);
	mlx_key_hook(game->window, handle_input, game);
	mlx_loop_hook(game->mlx, update_new_frame, game);
}

void	setup_graphics(t_game *game, int win_width, int win_height)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, win_width, win_height, "So_Long");
}


void flood_fill_util(t_game *game, int x, int y, t_fillresult *result, char **testmap)
{
    if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
        return;

    char current = testmap[y][x];
    if (current == '1' || current == 'F')
        return;
	
	if (current == 'E')
		result->exits += 1;
	if (current == 'C')
		result->collectables += 1;
    
    testmap[y][x] = 'F';

    flood_fill_util(game, x + 1, y, result, testmap);
    flood_fill_util(game, x - 1, y, result, testmap);
    flood_fill_util(game, x, y + 1, result, testmap);
    flood_fill_util(game, x, y - 1, result, testmap);
}


char **copy_map(t_game *game) {
    char **copy = malloc(game->map_height * sizeof(char *));
    for (int i = 0; i < game->map_height; i++) {
        copy[i] = malloc((game->map_width + 1) * sizeof(char));
        strcpy(copy[i], game->map[i]);
    }
    return copy;
}

t_fillresult flood_fill(t_game *game) {
    char **testmap;
    int		i;
	
    testmap = copy_map(game);
    t_fillresult result = {0, 0};
    flood_fill_util(game, game->spawn_x, game->spawn_y, &result, testmap);

	i = 0;
    while (i < game->map_height)
	{
        free(testmap[i]);
		i++;
    }
    free(testmap);

    return result;
}

int	initiliaze_game(t_game *game, char *map_path)
{
	t_fillresult result;
	game->map = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->current_count = 0;
	game->animation_timer = 0;
	game->coins = 0;
	game->state = GAME_PLAYING;
	game->prev_x = game->player_x;
	game->prev_y = game->player_y;
	game->needs_redraw = 1;
	load_map_from_file(map_path, game);
	find_player_spawn_point(game);
	result = flood_fill(game);
	if (result.collectables != game->amount_coins || result.exits != game->amount_exits)
	{
		fprintf(stderr, "Not all collectables or exits are reachable");
		return (1);
	}
	return (0);	
}
