/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll_update_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 15:09:01 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/11 12:50:55 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"
#include <stdio.h>
#include <stdlib.h>

int	cdll_update_list(t_cdllist *list, char **input)
{
	t_cd_ll_node	*copy;
	int				old;

	copy = cdll_get_node(list, false, input[0]);
	old = list->size;
	if (copy != NULL)
	{
		free(copy->var_2);
		copy->var_2 = input[1];
		return (0);
	}
	cdll_add_back(list, cdll_new_node(input[0], input[1], 0));
	if (list->size == old)
	{
		printf("failed to add new variable\n");
		return (1);
	}
	return (0);
}
