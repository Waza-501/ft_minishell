/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll_del_node.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/18 22:08:37 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/27 14:56:32 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"
#include <stdlib.h>
/*
static void	configure_links(t_cdllist *list, t_cd_ll_node *copy)
{
	copy->prev->next = copy->next;
	copy->next->prev = copy->prev;
	if (copy == list->head)
	{
		if (copy == copy->next)
			list->head = NULL;
		else
			list->head = copy->next;		
	}
}*/

void	cdll_del_node(t_cdllist *list, bool clear, char *name)
{
	t_cd_ll_node	*copy;

	if (!list || !list->head)
		return ;
	copy = cdll_get_node(list, clear, name);
	if (!copy)
		return ;
	copy->prev->next = copy->next;
	copy->next->prev = copy->prev;
	if (copy == list->head)
	{
		if (copy == copy->next)
			list->head = NULL;
		else
			list->head = copy->next;
	}
	free(copy->var_1);
	free(copy->var_2);
	copy->prev = NULL;
	copy->next = NULL;
	free(copy);
	list->size--;
}
