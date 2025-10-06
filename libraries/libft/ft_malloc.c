/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_malloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 10:50:25 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/06 10:50:53 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Created by haile <haile@student.codam.nl>*/
void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		ft_putstr_fd("A malloc error occured, existing the program \n", 2);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
