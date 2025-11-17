/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_core.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 13:32:49 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/17 15:12:28 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

int	expand_args(t_data *data)
{
	t_lexer	*copy;
	int		ret;

	copy = data->lexer;
	while (copy)
	{
		if (copy->type == NOEXPAND)
			copy = copy->next;
		else
		{
			ret = scan_expand(data, copy);
			if (ret != 0)
				return (ret);
			copy = copy->next;
		}
	}
	return (0);
}
