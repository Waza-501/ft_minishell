/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll_get_node.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/18 22:11:26 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/25 15:10:59 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"

/*Moves through the list until a specific node is found, then returns the node*/
t_cd_ll_node	*cdll_get_node(t_cdllist *list, int num, char *name)
{
	t_cd_ll_node	*copy;

	if (!list || !list->head)
		return (NULL);
	copy = list->head;
	if (!name)
	{
		while (num != 0)
		{
			copy = copy->next;
			num--;
		}
	}
	else
	{
		while (copy && !cdll_strncmp(copy->var_1, name, cdll_strlen(name)))
			copy = copy->next;
	}
	return (copy);
}
