/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 09:57:19 by owen          #+#    #+#                 */
/*   Updated: 2025/03/13 17:01:00 by owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		tally;

	copy = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!copy)
		return (NULL);
	tally = 0;
	while (s1[tally] != '\0')
	{
		copy[tally] = s1[tally];
		++tally;
	}
	copy[tally] = '\0';
	return (copy);
}*/

int	nl_checker(const char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}
/*
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*new;
	size_t	check;
	size_t	i;

	if (nmemb != 0 && size != 0)
	{
		check = nmemb * size;
		if (nmemb != check / size)
			return (NULL);
	}
	new = (char *)malloc(nmemb * size);
	if (!new)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}*/
