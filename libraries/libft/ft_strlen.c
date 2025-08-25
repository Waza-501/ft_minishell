/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 12:26:07 by owhearn       #+#    #+#                 */
/*   Updated: 2025/03/27 13:17:32 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	tally;

	tally = 0;
	if (!s)
		return (tally);
	while (*s && s[tally])
		tally++;
	return (tally);
}
