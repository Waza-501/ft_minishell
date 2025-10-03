/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arrdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 10:37:41 by haianhle      #+#    #+#                 */
/*   Updated: 2025/09/08 11:49:02 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup(char **array)
{
	char	**new_array;
	int		i;

	i = 0;
	while (array[i])
		i++;
	new_array = ft_malloc((i + 1) * sizeof(char *));
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
