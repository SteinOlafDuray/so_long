/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sduray   <sduray@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 11:09:06 by sduray        #+#    #+#                 */
/*   Updated: 2024/04/24 18:12:34 by sduray        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>
# include "./mlx.h"
// # include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include <stdbool.h>

# define TILE_SIZE 32
# define ANIMATION_SPEED 30

typedef enum e_game_state
{
	GAME_PLAYING,
	GAME_WON,
	GAME_LOST,
}	t_game_state;

typedef struct s_map_info
{
	int	*width;
	int	*height;
	int	*collectables;
	int	*game_exit;
	int	*spawn;
}	t_map;

typedef struct s_game
{
	t_game_state	state;
	void			*mlx;
	void			*window;
	int				player_x;
	int				player_y;
	int				prev_x;
	int				prev_y;
	char			**map;
	int				map_width;
	int				map_height;

	void			*img_wall;
	void			*img_floor;
	void			*img_coin[6];

	void			*img_player;
	void			*img_exit;
	int				current_count;
	int				animation_timer;
	int				count;
	int				coins;
	int				spawn_x;
	int				spawn_y;
	int				needs_redraw;
	int				amount_coins;
	int				amount_exits;
}	t_game;

typedef struct fillresult
{
	int collectables; 
	int exits;
}	t_fillresult;

//parse
char	**process_lines_loop(int fd, t_map *map_info);
char	**load_lines_into_map(int fd, t_game *game);
char	**load_map_from_file(char *file_path, t_game *game);
void	find_player_spawn_point(t_game *game);
char	**initialize_map(int *capacity);
void	free_resources(char **map, char *line, int height);
void	invalid_map(char **map, char *line, int height, int fd);
// char	**resize_map_if_needed(char **map, int *capacity, int height);
char	**process_each_line(char **map, char *line, t_map *map_info, int fd);

void	find_player_spawn_point(t_game *game);
void	draw_square(t_game *game, int x, int y, int color);
//draw.c
void	draw_map(t_game *game);
int		erase_old(t_game *param);
int		update_new_frame(void *param);
int		handle_input(int key, void *param);
void	draw_game_lost(t_game *game);
void	draw_game_won(t_game *game);

void	update_animation(t_game *game);
int		close_window(void *game);

//INPUT
int		check_if_move_is_wall(t_game *game, int next_x, int next_y);
void	restart_game(t_game *game);

int		handle_input(int key, void *game);
int		handle_state_changes(int key, t_game *game);
void	process_player_movement(int key, t_game *game);
void	update_next_position(int *next_x, int *next_y, int key);
void	update_game_state_with_movement(t_game *game, int next_x, int next_y);

//INSTALL
int		initiliaze_game(t_game *game, char *map_path);
void	setup_graphics(t_game *game, int win_width, int win_height);
void	setup_hooks(t_game *game);
void	restart_game(t_game *game);
int		close_window(void *game);
void	print_error(int i);

#endif