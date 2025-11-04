/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_core.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 13:32:49 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 13:38:36 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

bool	expand_args(t_data *data)
{
	t_lexer	*copy;

	copy = data->lexer;
	while (copy)
	{
		if (copy->type == NOEXPAND)
			copy = copy->next;
		else
		{
			if (scan_expand(data, copy))
				return (false);
			copy = copy->next;
		}
	}
	return (true);
}
