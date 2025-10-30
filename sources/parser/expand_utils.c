/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 16:59:53 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/30 17:14:23 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_env_char(char c)
{
	printf("am I used?\n");
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


int	find_var_in_string(char *str, char *var)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		while (str[idx] != '$')
			idx++;
		if (str[idx] == '$')
		{
			if (!ft_strncmp(&str[idx + 1], var, ft_strlen(var)))
				return (idx);
			idx++;
		}
	}
	return (idx);
}

/*rewrite this, mayhaps?*/
bool	reform_string(t_lexer *node, char *start, char *end, char *middle)
{
	char	*temp;

	temp = ft_strjoin(start, middle);
	if (!temp)
		return (malloc_error(NULL, true), false);
	ft_free(&node->string);
	node->string = ft_strjoin(temp, end);
	ft_free(&temp);
	if (!node->string)
		return (malloc_error(NULL, true), false);
	return (true);
}
