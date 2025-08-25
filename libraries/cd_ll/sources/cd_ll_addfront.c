/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll_addfront.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 09:05:59 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/25 17:22:52 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"

void	cdll_add_front(t_cdllist *list, t_cd_ll_node *node)
{
	if (!list || !node)
		return ;
	if (!list->head)
	{
		list->head = node;
		list->current = node;
		node->next = node;
		node->prev = node;
	}
	else
	{
		node->prev = list->head->prev;
		node->next = list->head;
		list->head->prev->next = node;
		list->head->prev = node;
		list->head = node;
	}
	list->size++;
}
