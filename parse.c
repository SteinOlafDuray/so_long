/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sduray   <sduray@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 11:09:06 by sduray        #+#    #+#                 */
/*   Updated: 2024/04/24 18:26:46 by sduray        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

char	**initialize_map(int *capacity)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * (*capacity));
	// if (!map)
	// 	print_error(capacity);
	return (map);
}

void	free_resources(char **map, char *line, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
	free(line);
}

void	invalid_map(char **map, char *line, int height, int fd)
{
	print_error(height);
	free_resources(map, line, height);
	close(fd);
	exit(1);
}

// char	**resize_map_if_needed(char **map, int *capacity, int height)
// {
// 	int		i;
// 	char	**newmap;

// 	*capacity *= 2;
// 	i = 0;
// 	newmap = (char **)malloc(sizeof(char *) * (*capacity));
// 	if (!newmap)
// 	{
// 		print_error(i);
// 		free_resources(map, NULL, height);
// 		return (NULL);
// 	}
// 	while (i < height)
// 	{
// 		newmap[i] = map[i];
// 		i++;
// 	}
// 	return (free(map), newmap);
// }


