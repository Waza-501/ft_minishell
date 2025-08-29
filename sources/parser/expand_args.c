/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/26 09:06:38 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/29 09:53:40 by owhearn       ########   odam.nl         */
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
		/*implement malloc protection at a later date*/
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

// bool	rebuild_string(t_token *node, char *var, t_cd_ll_node *env_node)
// {
// 	int		idx;
// 	char	*start;
// 	char	*end;

// 	//printf("string is %s\n", node->string);
// 	idx = find_var_in_string(node->string, var);
// 	start = ft_substr(node->string, 0, idx);
// 	end = ft_substr(node->string, (idx + ft_strlen(var) + 1), ft_strlen(&node->string[(idx + ft_strlen(var) + 1)]));
// 	reform_string(node, start, end, env_node->var_2);
// 	free(start);
// 	free(end);
// 	return (true);
// }

int	replace_var(t_cdllist *list, t_token *node, char *arg_var)
{
	// int				size;
	t_cd_ll_node	*var;
	// char			*var_copy;
	int		idx;
	char	*start;
	char	*end;

	// size = (find_var_size(&node->string[idx + 1]) + 1);
	// var_copy = (char *)malloc(sizeof(char) * (size + 1));
	// if (!var_copy)
	// 	/*implement malloc protection at a later date*/
	// 	return (1);
	// ft_strlcpy(var_copy, &node->string[idx + 1], size);
	// printf("%s\n", var_copy);
	var = cdll_get_node(list, 0, arg_var);
	//rebuild_string(node, arg_var, var);
	//printf("string is %s\n", node->string);
	idx = find_var_in_string(node->string, arg_var);
	start = ft_substr(node->string, 0, idx);
	end = ft_substr(node->string, (idx + ft_strlen(arg_var) + 1), ft_strlen(&node->string[(idx + ft_strlen(arg_var) + 1)]));
	reform_string(node, start, end, var->var_2);
	free(start);
	free(end);
	return (0);
}

void	scan_expand(t_data *data, t_token *node)
{
	size_t	idx;
	char	*arg_var;

	idx = 0;
	arg_var = NULL;
	//printf("%s\n", node->string);
	while (node->string[idx])
	{
		idx += find_dollar_sign(&node->string[idx]);
		if (idx == ft_strlen(node->string))
			return ;
		arg_var = get_arg_var(node, idx);
		if (!arg_var)
			exit(1);
		if (!cdll_get_node(data->envp_copy, false, arg_var))
			/*do thing*/
			printf("not a valid, existing env variable\n");
		else
			replace_var(data->envp_copy, node, arg_var);
		free(arg_var);
		idx++;
	}
	return ;
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
			scan_expand(data, copy);
			copy = copy->next;
		}
	}
	return (true);
}
