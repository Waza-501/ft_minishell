/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/22 11:05:07 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 17:40:19 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"
#include <stdio.h>

size_t	cdll_strlen(const char *s)
{
	size_t	tally;

	tally = 0;
	if (!s)
		return (tally);
	while (*s && s[tally])
		tally++;
	return (tally);
}

int	cdll_strncmp(const char *s1, const char *s2, size_t n)
{
	printf("s1 = %s length %zu-----s2 = %s length %zu -----n %zu\n", s1, cdll_strlen(s1), s2, cdll_strlen(s2), n);
	if (cdll_strlen(s1) != n)
		return (printf("size difference\n"), 1);
	while ((*s1 || *s2) && n > 0)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
