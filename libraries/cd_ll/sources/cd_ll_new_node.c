/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll_new_node.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 01:30:48 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/25 15:05:54 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"
#include <stdlib.h>

/*cdl_new_node allocates a new t_cd_ll_node and sets its fields to the given
values. It returns the new node, or NULL if allocation fails.*/
t_cd_ll_node	*cdll_new_node(char *str1, char *str2, int id)
{
	t_cd_ll_node	*new;

	new = (t_cd_ll_node *)malloc(sizeof(t_cd_ll_node));
	if (!new)
		return (NULL);
	new->var_1 = str1;
	new->var_2 = str2;
	new->id = id;
	return (new);
}
