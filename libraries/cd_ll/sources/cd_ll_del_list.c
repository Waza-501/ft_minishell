/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll_del_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/19 11:05:18 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/22 11:53:16 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"
#include <stdlib.h>

void	cdll_del_list(t_cdllist *list)
{
	if (!list)
		return ;
	while (list->head != NULL)
		cdll_del_node(list, 0, NULL);
	free(list);
	list = NULL;
}
