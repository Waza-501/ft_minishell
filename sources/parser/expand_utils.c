/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 16:59:53 by owhearn       #+#    #+#                 */
/*   Updated: 2025/09/08 11:43:29 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_env_char(char c)
{
	if (ft_isalpha(c))
		return (true);
	else if (ft_isdigit(c))
		return (true);
	else if (c == '_')
		return (true);
	else if (c == '$')
		return (true);
	else if (c == '?')
		return (true);
	return (false);
}

int	find_dollar_sign(char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] && str[idx] != '$')
		idx++;
	return (idx);
}

int	find_var_size(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (check_env_char(str[idx]) == false)
			return (idx);
		idx++;
	}
	return (idx);
}
