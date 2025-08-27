/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll_get_node.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/18 22:11:26 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/27 14:57:30 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"

/*Moves through the list until a specific node is found, then returns the node*/
t_cd_ll_node	*cdll_get_node(t_cdllist *list, bool clear, char *name)
{
	t_cd_ll_node	*copy;
	int				i;

	if (!list || !list->head)
		return (NULL);
	i = 0;
	copy = list->head;
	if (clear == true)
		return (copy);
	else
	{
		while (list->size >= i && cdll_strncmp(copy->var_1, name, cdll_strlen(name)))
		{
			copy = copy->next;
			i++;
		}
	}
	if (i > list->size)
		return (NULL);
	return (copy);
}
