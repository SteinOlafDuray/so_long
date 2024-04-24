/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sduray   <sduray@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 11:09:06 by sduray        #+#    #+#                 */
/*   Updated: 2024/04/24 18:19:23 by sduray        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int check(t_map *map_info, char *first, char *last)
{
	int i;
	
	i = 0;
	if (first || last)
	{
		while (first[i] || last[i])
		{
			if (first[i] != '1' || last[i] != '1')	
			{
				fprintf(stderr, "Invalid map : first or last line doenst exist completly out of walls\n");
				return (1);
			}
			i++;
		}
	}
	if ((*(map_info->collectables)) == 0 || (*(map_info->spawn)) != 1 || (*(map_info->game_exit)) < 1)
	{
		fprintf(stderr, "Invalid map : the map doesn't contain 1 of the following collectable, exit, spawn\n");
		return (1);
	}
	return (0);
}

char	**process_lines_loop(int fd, t_map *map_info)
{
	char	**map;
	char	*line;
	char	*first;
	char	*last;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	first = line;
	*(map_info->width) = ft_strlen(line) - 1;
	map = initialize_map(map_info->width);
	if (!map)
	{
		free(line);
		close(fd);
		return (NULL);
	}
	while (line != NULL)
	{
		map = process_each_line(map, line, map_info, fd);
		if (!map)
			return (NULL);
		last = line;
		line = get_next_line(fd);
	}
	if (check(map_info, first, last) == 1)
		return(free(line), close(fd), NULL);
	close(fd);
	return (free(line), map);
}

int check_the_letters(t_map *map_info, char *line)
{
	int len;
	char ch;

	len = 0;
	while (line[len])
	{
		ch = line[len];
		if(ch == 'C')
			(*(map_info->collectables))++;
		else if (ch == 'P')
			(*(map_info->spawn))++;
		else if (ch == 'E')
			(*(map_info->game_exit))++;
		if (ch != '1' && ch != '0' && ch != 'C' && ch != 'E' && ch != 'P')
			return (1);
		len++;	
	}
	return (0);
}


char	**process_each_line(char **map, char *line, t_map *map_info, int fd)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	if (*(map_info->width) == 0)
		*(map_info->width) = len;
	else if (len != *(map_info->width) || line[0] != '1' || line[len - 1] != '1')
		return (invalid_map(map, line, *(map_info->height), fd), NULL);
	else if (check_the_letters(map_info, line) == 1)
		return (invalid_map(map, line, *(map_info->height), fd), NULL);
	map[*(map_info->height)] = line;
	(*(map_info->height))++;
	return (map);
}

char	**load_lines_into_map(int fd, t_game *game)
{
	t_map	map_info;
	char	**map;
	int		width;
	int		height;
	int		collectables;
	int		spawn;
	int		game_exit;
	game->amount_coins = 0;
	game->amount_exits = 0;

	collectables = 0;
	width = 0;
	height = 0;
	game_exit = 0;
	spawn = 0;
	map_info.spawn = &spawn;
	map_info.game_exit = &game_exit;
	map_info.width = &width;
	map_info.height = &height;
	map_info.collectables = &collectables;
	
	map = process_lines_loop(fd, &map_info);
	if (map != NULL)
	{
		game->map_width = width;
		game->map_height = height;
		game->map = map;
	}
	game->amount_coins = (*(map_info.collectables));
	game->amount_exits = (*(map_info.game_exit));
	return (map);
}

char	**load_map_from_file(char *file_path, t_game *game)
{
	
	int		fd;
	char	**map;
	int		width;
	int		height;

	width = 0;
	height = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = load_lines_into_map(fd, game);
	close(fd);
	return (map);
}

void	find_player_spawn_point(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->spawn_x = x;
				game->spawn_y = y;
				game->player_x = x * TILE_SIZE;
				game->player_y = y * TILE_SIZE;
				return ;
			}
			x++;
		}
		y++;
	}
}
