/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   p_draw.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sduray   <sduray@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 11:09:06 by sduray        #+#    #+#                 */
/*   Updated: 2024/04/23 19:07:41 by sduray        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	tile_size;
	int	j;

	tile_size = TILE_SIZE;
	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			mlx_pixel_put(game->mlx, game->window, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	load_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->img_wall = mlx_xpm_file_to_image(game->mlx, "maps/wall.xpm",
			&img_width, &img_height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "maps/exit.xpm",
			&img_width, &img_height);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "maps/floor.xpm",
			&img_width, &img_height);
	game->img_player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&img_width, &img_height);
	game->img_coin[0] = mlx_xpm_file_to_image(game->mlx, "textures/coin1.xpm",
			&img_width, &img_height);
	game->img_coin[1] = mlx_xpm_file_to_image(game->mlx, "textures/coin2.xpm",
			&img_width, &img_height);
	game->img_coin[2] = mlx_xpm_file_to_image(game->mlx, "textures/coin3.xpm",
			&img_width, &img_height);
	game->img_coin[3] = mlx_xpm_file_to_image(game->mlx, "textures/coin4.xpm",
			&img_width, &img_height);
	game->img_coin[4] = mlx_xpm_file_to_image(game->mlx, "textures/coin5.xpm",
			&img_width, &img_height);
	game->img_coin[5] = mlx_xpm_file_to_image(game->mlx, "textures/coin6.xpm",
			&img_width, &img_height);
}


void	draw_top_bar(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->map_width)
	{
		draw_square(game, x * TILE_SIZE, 0, 0xDDDDDD);
		x++;
	}
}

static unsigned int	ft_number_size(int number)
{
	unsigned int	length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		length += 1;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

void	draw_stats(t_game *game, int text_x, int text_y)
{
	char	moves_str[42];
	char	coins_str[42];
	char	*coins = ft_itoa(game->coins);
	char	*moves = ft_itoa(game->current_count);
	char    *moves_text = "Moves: ";
	char    *coins_text = "Coins: ";

	mlx_string_put(game->mlx, game->window,
		text_x, text_y, 0x000000, coins_text);
	mlx_string_put(game->mlx, game->window, text_x + (TILE_SIZE * 1.5),
		text_y, 0x000000, coins);
	mlx_string_put(game->mlx, game->window,
		text_x, text_y + 14, 0x000000, moves_text);
	mlx_string_put(game->mlx, game->window, text_x + (TILE_SIZE * 1.5),
		text_y + 14, 0x000000, moves);
}

void	tile_to_image(char tile, int pixel_x, int pixel_y, t_game *game)
{
	if (tile == '1')
	{
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_wall, pixel_x, pixel_y);
	}
	if (tile == 'C')
	{
		mlx_put_image_to_window(game->mlx, game->window, game->img_floor,
			pixel_x, pixel_y);
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_coin[game->animation_timer % 6], pixel_x, pixel_y);
	}
	if (tile == '0' || tile == 'P')
	{
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_floor, pixel_x, pixel_y);
	}
	if (tile == 'E')
	{
		draw_square(game, pixel_x, pixel_y, 0xFF00FF);
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_exit, pixel_x, pixel_y);
	}
}

void draw_tile(t_game *game, int x, int y, int pixel_y_offset)
{
	int		pixel_x;
	int		pixel_y;
	char	tile;

	pixel_x = x * TILE_SIZE;
	pixel_y = (y * TILE_SIZE) + pixel_y_offset;
	tile = game->map[y][x];
	draw_square(game, pixel_x, pixel_y, 0xDDDDDD);
	tile_to_image(tile, pixel_x, pixel_y, game);
}

void	draw_map_tiles(t_game *game, int pixel_y_offset)
{
	int	y;
	int	x;

	load_images(game);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			draw_tile(game, x, y, pixel_y_offset);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game)
{
	draw_top_bar(game);
	draw_stats(game, TILE_SIZE + 2, TILE_SIZE / 2);
	draw_map_tiles(game, TILE_SIZE);
}

void	draw_game_won(t_game *game)
{
	mlx_string_put(game->mlx, game->window,
		100, 100, 0xFFFFFF, "You WON! Press R to restart.");
}

void	draw_game_lost(t_game *game)
{
	mlx_string_put(game->mlx, game->window,
		100, 100, 0xFFFFFF, "Ahhh you LOST! Press R to restart.");
}
