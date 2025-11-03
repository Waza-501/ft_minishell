/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_chardup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/29 16:01:32 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/29 16:02:59 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chardup(const char s)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * 2);
	if (!new)
		return (NULL);
	new[0] = s;
	new[1] = '\0';
	return (new);
}
