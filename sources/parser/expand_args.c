/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/26 09:06:38 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/31 12:39:17 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg_var(t_lexer *node, int idx)
{
	int				size;
	char			*var_copy;

	//size = (find_var_size(&node->string[idx + 1]) + 1);
	size = (find_var_size(&node->string[idx + 1]));
	var_copy = (char *)malloc(sizeof(char) * (size + 1));
	if (!var_copy)
		return (malloc_error(NULL, true));
	ft_strlcpy(var_copy, &node->string[idx + 1], size);
	return (var_copy);
}

int	replace_var(t_cdllist *list, t_lexer *node, char *arg_var)
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
	{
		ft_free(&start);
		ft_free(&end);
		return (malloc_error(NULL, true), 1);
	}
	if (reform_string(node, start, end, var->var_2) == false)
	{
		ft_free(&start);
		ft_free(&end);
		return (1);
	}
	ft_free(&start);
	ft_free(&end);
	return (0);
}

int	empty_space_dollar(char *start, int idx, int size, t_lexer *node)
{
	char	*end;

	end = ft_substr(node->string, (idx + size),
			ft_strlen(&node->string[(idx + size)]));
	if (!end)
		return (malloc_error(NULL, true), 1);
	if (reform_string(node, start, end, "") == false)
	{
		ft_free(&end);
		return (1);
	}
	ft_free(&end);
	return (0);
}

/*redo documentation*/
int	find_replace_type(t_data *data, t_lexer *node, char *arg_var)
{
	int				idx;
	int				size;
	char			*start;

	idx = find_var_in_string(node->string, arg_var);
	size = ft_strlen(arg_var);
	if (size == 1 || !ft_strncmp(&node->string[idx], "$?", 2))
		return (0);
	start = ft_substr(node->string, 0, idx);
	if (!start)
		malloc_error(data, true);
	if (ft_isdigit(node->string[idx + 1]) || node->string[idx + 1] == '$')
	{
		if (empty_space_dollar(start, idx, 2, node))
			malloc_error(data, false);
	}
	else
		if (empty_space_dollar(start, idx, ft_strlen(arg_var) + 1, node))
			malloc_error(data, false);
	ft_free(&start);
	return (0);
}

/*redo documentation*/
int	scan_expand(t_data *data, t_lexer *node)
{
	size_t	idx;
	char	*arg_var;

	idx = 0;
	arg_var = NULL;
	while (node->string[idx])
	{
		idx += find_dollar_sign(&node->string[idx]);
		if (idx == ft_strlen(node->string))
			return (0);
		arg_var = get_arg_var(node, idx);
		if (!arg_var)
			malloc_error(data, false);
		if (!cdll_get_node(data->envp_copy, false, arg_var))
		{
			if (find_replace_type(data, node, arg_var) == 1)
				return (ft_free(&arg_var), 1);
		}
		else
			if (replace_var(data->envp_copy, node, arg_var) == 1)
				return (ft_free(&arg_var), 1);
		ft_free(&arg_var);
		idx++;
	}
	return (0);
}

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
