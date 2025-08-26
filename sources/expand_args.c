/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/26 09:06:38 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/26 09:56:11 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_var(t_cdllist *list, char *var_name)
{
	
	t_cd_ll_node	*var;

	var = cdll_get_node();
}

bool	expand_args(t_data *data)
{
	t_token	*copy;

	copy = data->lexer;
	while (copy)
	{
		
	}
}
