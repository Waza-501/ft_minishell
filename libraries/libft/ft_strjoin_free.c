/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 10:37:58 by haianhle      #+#    #+#                 */
/*   Updated: 2025/11/10 14:50:59 by owhearn       ########   odam.nl         */
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

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	size_t	len;
	char	*join;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc((len + 1) * sizeof(char));
	if (!join)
		return (0);
	ft_strlcpy(join, s1, len + 1);
	ft_strlcat(join, s2, len + 1);
	free(s2);
	return (join);
}
