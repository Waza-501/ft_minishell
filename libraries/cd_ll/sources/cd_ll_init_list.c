/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll_init_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 01:24:43 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/15 09:08:45 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"
#include <stdlib.h>

/*cdl_init_list allocates a new t_cdllist, sets its pointers to NULL, and
its size to zero. It returns the new list or NULL if allocation fails.*/
t_cdllist	*cdll_init_list(void)
{
	t_cdllist	*new;

	new = (t_cdllist *)malloc(sizeof(t_cdllist));
	if (!new)
		return (NULL);
	new->head = NULL;
	new->current = NULL;
	new->size = 0;
	return (new);
}
