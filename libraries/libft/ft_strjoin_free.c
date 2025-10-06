/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haianhle <haianhle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 10:37:58 by haianhle      #+#    #+#                 */
/*   Updated: 2025/10/06 10:51:24 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Created by haile <haile@student.codam.nl>*/
char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	len;
	char	*join;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc((len + 1) * sizeof(char));
	if (!join)
		return (0);
	ft_strlcpy(join, s1, len + 1);
	ft_strlcat(join, s2, len + 1);
	free(s1);
	return (join);
}
