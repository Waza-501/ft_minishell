/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/26 09:06:38 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/29 16:36:58 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg_var(t_token *node, int idx)
{
	int				size;
	char			*var_copy;

	size = (find_var_size(&node->string[idx + 1]) + 1);
	var_copy = (char *)malloc(sizeof(char) * (size + 1));
	if (!var_copy)
		return (NULL);
	ft_strlcpy(var_copy, &node->string[idx + 1], size);
	if (!var_copy)
		return (NULL);
	return (var_copy);
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

bool	reform_string(t_token *node, char *start, char *end, char *middle)
{
	char	*temp;

	temp = ft_strjoin(start, middle);
	if (!temp)
		return (false);
	free(node->string);
	node->string = ft_strjoin(temp, end);
	if (!node->string)
		return (free(temp), false);
	free(temp);
	return (true);
}

int	replace_var(t_cdllist *list, t_token *node, char *arg_var)
{
	t_cd_ll_node	*var;
	int				idx;
	char			*start;
	char			*end;

	var = cdll_get_node(list, 0, arg_var);
	idx = find_var_in_string(node->string, arg_var);
	start = ft_substr(node->string, 0, idx);
	end = ft_substr(node->string, (idx + ft_strlen(arg_var) + 1),
			ft_strlen(&node->string[(idx + ft_strlen(arg_var) + 1)]));
	if (!start || !end)
		return (1);
	reform_string(node, start, end, var->var_2);
	free(start);
	free(end);
	return (0);
}

int	find_replace_type(t_token *node, char *arg_var)
{
	int				idx;
	int				size;
	char			*start;
	char			*end;

	idx = find_var_in_string(node->string, arg_var);
	start = ft_substr(node->string, 0, idx);
	size = ft_strlen(arg_var);
	if (size == 1)
		return (0);
	if (!ft_strncmp(&node->string[idx], "$?", 2))
		return (0);
	if (ft_isdigit(node->string[idx + 1]))
	{
		handle_dollar_digit(start,)
		// size = 2;
		// end = ft_substr(node->string, (idx + size), ft_strlen(&node->string[(idx + size)]));
		// reform_string(node, start, end, "");
	}
	free(start);
	free(end);
	return (0);
}

bool	scan_expand(t_data *data, t_token *node)
{
	size_t	idx;
	char	*arg_var;

	idx = 0;
	arg_var = NULL;
	while (node->string[idx])
	{
		idx += find_dollar_sign(&node->string[idx]);
		if (idx == ft_strlen(node->string))
			return (true);
		arg_var = get_arg_var(node, idx);
		if (!arg_var)
			return (false);
		if (!cdll_get_node(data->envp_copy, false, arg_var))
			if (find_replace_type(node, arg_var) == 1)
				return (free(arg_var), false);
		else
			if (replace_var(data->envp_copy, node, arg_var) == 1)
				return (free(arg_var), false);
		free(arg_var);
		idx++;
	}
	return (true);
}

bool	expand_args(t_data *data)
{
	t_token	*copy;

	copy = data->lexer;
	while (copy)
	{
		if (copy->type == NOEXPAND)
			copy = copy->next;
		else
		{
			if (scan_expand(data, copy) == false)
				return (false);
			copy = copy->next;
		}
	}
	return (true);
}
