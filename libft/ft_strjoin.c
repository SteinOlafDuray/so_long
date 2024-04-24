/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 13:01:38 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/04/12 15:04:16 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ccs;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ccs = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ccs)
		return (NULL);
	ft_strlcpy(ccs, s1, ft_strlen(s1) + 1);
	ft_strlcpy(ccs + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (ccs);
}
